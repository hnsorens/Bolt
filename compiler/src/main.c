#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cJSON.h"
#include "lexer.h" // You create this to match your lexer.l token structure

extern LineNode* lines_root;

extern int yylex(void);
extern struct yy_buffer_state* yy_scan_string(const char* str);
extern void yy_delete_buffer(struct yy_buffer_state*);
void print_avl(Token* root, int depth);

void print_lines_inorder(LineNode* node) {
    if (!node) return;
    print_lines_inorder(node->left);

    printf("LINE %d:\n", node->line_number);
    Token* tok = node->token_head;
    while (tok) {
        printf("\tTOKEN: %s (col %d)", tok->value, tok->column);
        if (tok->error) {
            printf(" [ERROR: %s]", tok->error);
        }
        printf("\n");
        tok = tok->next;
    }

    print_lines_inorder(node->right);
}


char* read_line() {
    size_t size = 1024;
    char* buffer = malloc(size);
    if (!buffer) return NULL;

    int c;
    size_t len = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            buffer = realloc(buffer, size);
            if (!buffer) return NULL;
        }
        buffer[len++] = c;
    }

    if (c == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

void send_diagnostics_from_node(cJSON* diagnostics, LineNode* node) {
    if (!node) return;
    send_diagnostics_from_node(diagnostics, node->left);

    Token* tok = node->token_head;
    while (tok) {
        if (tok->error) {
            cJSON* diagnostic = cJSON_CreateObject();

            cJSON* range = cJSON_CreateObject();
            cJSON* start = cJSON_CreateObject();
            cJSON* end = cJSON_CreateObject();

            cJSON_AddNumberToObject(start, "line", node->line_number);
            cJSON_AddNumberToObject(start, "character", tok->column);
            cJSON_AddNumberToObject(end, "line", node->line_number);
            cJSON_AddNumberToObject(end, "character", tok->column + (int)strlen(tok->value));

            cJSON_AddItemToObject(range, "start", start);
            cJSON_AddItemToObject(range, "end", end);

            cJSON_AddItemToObject(diagnostic, "range", range);
            cJSON_AddStringToObject(diagnostic, "message", tok->error);
            cJSON_AddNumberToObject(diagnostic, "severity", 1); // Error

            cJSON_AddItemToArray(diagnostics, diagnostic);
        }
        tok = tok->next;
    }

    send_diagnostics_from_node(diagnostics, node->right);
}

void send_diagnostics(const char* uri, LineNode* root) {
    cJSON* diagnostics = cJSON_CreateArray();

    send_diagnostics_from_node(diagnostics, root);

    cJSON* response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "uri", uri);
    cJSON_AddItemToObject(response, "diagnostics", diagnostics);

    char* result_str = cJSON_PrintUnformatted(response);
    printf("%s\n", result_str);
    fflush(stdout);

    free(result_str);
    cJSON_Delete(response);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--language-server") == 0) {
        char* line = NULL;
        while ((line = read_line()) != NULL) {
            cJSON* request = cJSON_Parse(line);
            if (!request) {
                fprintf(stderr, "{\"error\":\"Invalid JSON\"}\n");
                free(line);
                continue;
            }

            cJSON* command = cJSON_GetObjectItem(request, "command");
            cJSON* text = cJSON_GetObjectItem(request, "text");
            cJSON* uri = cJSON_GetObjectItem(request, "uri");

            if (command && text && uri && strcmp(command->valuestring, "validate") == 0) {
                struct yy_buffer_state* buf = yy_scan_string(text->valuestring);
                yylex();  // Populates AVL tree: lines_root
                yy_delete_buffer(buf);

                send_diagnostics(uri->valuestring, lines_root);
            } else {
                fprintf(stderr, "{\"error\":\"Invalid request structure\"}\n");
            }

            cJSON_Delete(request);
            free(line);
        }
    } else {
        const char* text = "int a = 0;\nfloat b = 1.0;\nchar c = 'x';";

        struct yy_buffer_state* buf = yy_scan_string(text);
        yylex();  // Populates AVL tree: lines_root
        yy_delete_buffer(buf);

        // Print all lines and tokens
        print_lines_inorder(lines_root);
    }

    return 0;
}

