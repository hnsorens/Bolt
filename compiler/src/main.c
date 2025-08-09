#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ASTNodes.h"
#include "cJSON.h"

#include "../parser.tab.h"

typedef void* YY_BUFFER_STATE;

extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buf);
extern void print_block_item(int tabs, struct block_item_t* statement);

extern int yyparse();
extern struct block_item_t *ast_root;

extern void generate_code(FILE* file, struct block_item_t* item);

extern function_t* function_head;
extern function_t* function_tail;

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

#define MAX_CHARACTER_EDIT_BUFFER 1024

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--language-server") == 0) {
        char character_edit_buffer[MAX_CHARACTER_EDIT_BUFFER];
        char* line = NULL;
        while ((line = read_line()) != NULL) {
            freopen("stderr.log", "w", stderr);
            fprintf(stderr, "%s\n", line);
            fflush(stderr);
            cJSON* request = cJSON_Parse(line);
            if (!request) {
                fprintf(stderr, "{\"error\":\"Invalid JSON\"}\n");
                free(line);
                continue;
            }

            cJSON* method = cJSON_GetObjectItem(request, "method");
            cJSON* params = cJSON_GetObjectItem(request, "params");
            if (!params)
            {
                fprintf(stderr, "{\"error\":\"Invalid Parameters\"}\n");
                continue;
            }

            cJSON* uri = cJSON_GetObjectItem(params, "uri");
            cJSON* text = cJSON_GetObjectItem(params, "text");
            YY_BUFFER_STATE buf = yy_scan_string(text->valuestring);
            int result = yyparse();
            yy_delete_buffer(buf);

            if (result == 0) {
                fprintf(stderr, "Parse succeeded\n");
            } else {
                fprintf(stderr, "Parse failed\n");
            }

            print_block_item(0, ast_root);

            function_head = NULL;
            function_tail = NULL;

            generate_code(stderr, ast_root);

            fflush(stderr);

        }
    }

    return 0;
}

