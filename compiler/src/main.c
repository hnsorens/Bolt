#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cJSON.h"
#include "lexer.h" // You create this to match your lexer.l token structure

extern Token* token_list_head;
extern void free_token_list();
extern void reset_token_list(); // optional: reset token list between scans

extern int yylex(void);
extern struct yy_buffer_state* yy_scan_string(const char* str);
extern void yy_delete_buffer(struct yy_buffer_state*);

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

void send_diagnostics(const char* uri, Token* tokens) {
    cJSON* diagnostics = cJSON_CreateArray();

    for (Token* t = tokens; t; t = t->next) {
        if (t->error) {
            cJSON* diagnostic = cJSON_CreateObject();

            cJSON* range = cJSON_CreateObject();
            cJSON* start = cJSON_CreateObject();
            cJSON* end = cJSON_CreateObject();

            cJSON_AddNumberToObject(start, "line", t->line);
            cJSON_AddNumberToObject(start, "character", t->column);
            cJSON_AddNumberToObject(end, "line", t->line);
            cJSON_AddNumberToObject(end, "character", t->column + (int)strlen(t->value));

            cJSON_AddItemToObject(range, "start", start);
            cJSON_AddItemToObject(range, "end", end);

            cJSON_AddItemToObject(diagnostic, "range", range);
            cJSON_AddStringToObject(diagnostic, "message", t->error);
            cJSON_AddNumberToObject(diagnostic, "severity", 1); // Error

            cJSON_AddItemToArray(diagnostics, diagnostic);
        }
    }

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
                // Run lexer on input string
                struct yy_buffer_state* buf = yy_scan_string(text->valuestring);
                yylex();  // This populates token_list_head
                yy_delete_buffer(buf);

                send_diagnostics(uri->valuestring, token_list_head);
                free_token_list(); // Clear token list between runs
            } else {
                fprintf(stderr, "{\"error\":\"Invalid request structure\"}\n");
            }

            cJSON_Delete(request);
            free(line);
        }
    }
    else {
        const char* text = "7asdasd asd";

        struct yy_buffer_state* buf = yy_scan_string(text);
        yylex();  // This populates token_list_head
        yy_delete_buffer(buf);

        Token* current = token_list_head;
        while(current)
        {
            printf("%s %d %d\n", current->value, current->column, current->line);
            current = current->next;
        }
    }

    return 0;
}
