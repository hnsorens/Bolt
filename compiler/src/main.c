#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cJSON.h"
#include "lexer.h" // You create this to match your lexer.l token structure

extern LineNode* lines_root;
extern LineNode* lines_head;
extern LineNode* lines_tail;
extern int curr_line;
extern int curr_col;

extern int yylex(void);
extern struct yy_buffer_state* yy_scan_string(const char* str);
extern void yy_delete_buffer(struct yy_buffer_state*);
void print_avl(Token* root, int depth);
LineNode* find_line_node(LineNode* root, int line_number);

void print_lines_inorder(FILE* file, LineNode* node) {
    if (!node) return;
    print_lines_inorder(file, node->left);

    fprintf(file,"LINE %d:\n", node->line_number);
    Token* tok = node->token_head;
    while (tok) {
        fprintf(file, "\tTOKEN: %s (col %d)", tok->value, tok->column);
        if (tok->error) {
            fprintf(file, " [ERROR: %s]", tok->error);
        }
        fprintf(file, "\n");
        tok = tok->next;
    }

    print_lines_inorder(file, node->right);
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

void clear_diagnostics(const char* uri) {
    cJSON* diagnostics = cJSON_CreateArray(); // empty array

    cJSON* response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "uri", uri);
    cJSON_AddItemToObject(response, "diagnostics", diagnostics);

    char* result_str = cJSON_PrintUnformatted(response);
    printf("%s\n", result_str);
    fflush(stdout);

    free(result_str);
    cJSON_Delete(response);
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

#define MAX_CHARACTER_EDIT_BUFFER 1024

int main(int argc, char* argv[]) {
    freopen("stderr.log", "w", stderr);
    LineNode* root;
    LineNode* head;
    LineNode* tail;
    if (argc > 1 && strcmp(argv[1], "--language-server") == 0) {
        char character_edit_buffer[MAX_CHARACTER_EDIT_BUFFER];
        char* line = NULL;
        while ((line = read_line()) != NULL) {
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

            if (strcmp(method->valuestring, "textDocument/didOpen") == 0)
            {
                cJSON* textDocument = cJSON_GetObjectItem(params, "textDocument");
            if (!textDocument)
            {
                fprintf(stderr, "{\"error\":\"Invalid TextDocument\"}\n");
                continue;
            }
            cJSON* uri = cJSON_GetObjectItem(textDocument, "uri");
            cJSON* text = cJSON_GetObjectItem(textDocument, "text");
                    struct yy_buffer_state* buf = yy_scan_string(text->valuestring);
                    yylex();  // Populates AVL tree: lines_root
                    yy_delete_buffer(buf);

                    root = lines_root;
                    head = lines_head;
                    tail = lines_tail;

                
                print_lines_inorder(stderr, root);
                    fflush(stderr);
                send_diagnostics(uri->valuestring, root);
            }
            else if (strcmp(method->valuestring, "textDocument/didChange") == 0)
            {
                cJSON* textDocument = cJSON_GetObjectItem(params, "textDocument");
                if (!textDocument)
                {
                    fprintf(stderr, "{\"error\":\"Invalid TextDocument\"}\n");
                    continue;
                }
                cJSON* uri = cJSON_GetObjectItem(textDocument, "uri");
                cJSON* contentChanges = cJSON_GetObjectItem(params, "contentChanges");
                if (!contentChanges)
                {
                    fprintf(stderr, "{\"error\":\"Invalid ContentChanges\"}\n");
                    continue;
                }
                if (cJSON_IsArray(contentChanges))
                {
                    int size = cJSON_GetArraySize(contentChanges);
                    for (int i = 0; i < size; i++)
                    {
                        cJSON* change = cJSON_GetArrayItem(contentChanges, i);
                        cJSON* text = cJSON_GetObjectItem(change, "text");
                        cJSON* range = cJSON_GetObjectItem(change, "range");
                        cJSON* start = cJSON_GetObjectItem(range, "start");
                        cJSON* end = cJSON_GetObjectItem(range, "end");
                        int start_line_number = cJSON_GetObjectItem(start, "line")->valueint;
                        int start_char = cJSON_GetObjectItem(start, "character")->valueint;
                        int end_line_number = cJSON_GetObjectItem(end, "line")->valueint;
                        int end_char = cJSON_GetObjectItem(end, "character")->valueint;
        
                        LineNode* start_line = find_line_node(root, start_line_number);
                        LineNode* end_line = find_line_node(root, end_line_number);

                        fprintf(stderr, "root: %d %d start %d %d end %d %d\n", root->line_number, root, start_line->line_number, start_line, end_line->line_number, end_line);
        
                        Token* token_start = start_line->token_head;
                        Token* token_end = end_line->token_tail;
        
                        Token* token_before = NULL;
                        Token* token_after = NULL;
                        // Locate token_before and token_start
                        for (Token* t = start_line->token_head; t; t = t->next) {
                            int token_start_col = t->column;
                            int token_end_col = token_start_col + strlen(t->value);
        
                            if (start_char < token_start_col) {
                                // Starts before the first token on the line
                                token_start = NULL;
                                token_before = NULL;
                                break;
                            }
        
                            if (start_char <= token_end_col) {
                                // Inside this token
                                token_start = t;
                                token_before = t->prev;
                                break;
                            }
        
                            token_before = t;
                            token_start = NULL;
                        }
                        
                        // Locate token_after and token_end
                        for (Token* t = end_line->token_tail; t; t = t->prev) {
                            int token_start_col = t->column;
                            int token_end_col = token_start_col + strlen(t->value);
        
                            if (end_char > token_end_col) {
                                // Ends after the last token
                                token_end = NULL;
                                token_after = NULL;
                                break;
                            }
        
                            if (end_char >= token_start_col) {
                                // Inside this token
                                token_end = t;
                                token_after = t->next;
                                break;
                            }
        
                            token_after = t;
                            token_end = NULL;
                        }
                        int token_start_length = (token_start ? start_char - token_start->column : 0);
                        int token_end_length = (token_end ? token_end->column + token_end->length - end_char : 0);
                        int text_length = strlen(text->valuestring);
                        int tokenize_length = token_start_length + token_end_length + text_length;
        
                        char* characters = tokenize_length+1 > MAX_CHARACTER_EDIT_BUFFER ? (char*)malloc(tokenize_length+1) : character_edit_buffer;
        
                        if (token_start_length > 0) memcpy(characters, token_start->value, token_start_length);
                        fprintf(stderr, "TEXT: '%s'\n", characters);
                        if (token_end_length > 0) memcpy(characters + token_start_length + text_length, token_end->value + strlen(token_end->value) - token_end_length, token_end_length);
                        fprintf(stderr, "TEXT: '%s'\n", characters);
                        memcpy(characters + token_start_length, text->valuestring, text_length);
                        fprintf(stderr, "TEXT: '%s'\n", characters);
                        characters[tokenize_length] = 0;
                        fprintf(stderr, "TEXT: '%s'\n", characters);
                        

                        if (strlen(characters) == 0)
                        {
                            if (start_line == end_line)
                            {
                                if (!token_after && !token_before)
                                {
                                    start_line->token_head = NULL;
                                    start_line->token_tail = NULL;
                                }
                                if (token_after && token_before)
                                {
                                    token_before->next = token_after;
                                    token_after->prev = token_before;
                                }
                                if (token_after && !token_before)
                                {
                                    token_after->prev = NULL;
                                    start_line->token_head = token_after;
                                }
                                if (!token_after && token_before)
                                {
                                    token_before->next = NULL;
                                    start_line->token_tail = token_before;
                                }
                            }
                        }
                        else 
                        {
                            lines_root = NULL;
                            lines_head = NULL;
                            lines_tail = NULL;
                            curr_line = start_line_number;
                            curr_col = token_start ? token_start->column : start_char;
            
                            struct yy_buffer_state* buf = yy_scan_string(characters);
                            yylex();  // Populates AVL tree: lines_root
                            yy_delete_buffer(buf);
            
                            if (characters != character_edit_buffer)
                            {
                                free(characters);
                            }
            
                            Token* new_first_token = lines_head->token_head;
                            Token* new_last_token = lines_tail->token_tail;
                            if (start_line == end_line)
                            {
                                if (token_before)
                                {
                                    token_before->next = lines_head->token_head;
                                    lines_head->token_head->prev = token_before;
                                }
                                else 
                                {
                                    start_line->token_head = lines_head->token_head;
                                }
    
                                if (token_after)
                                {
                                    token_after->prev = lines_tail->token_tail;
                                    lines_tail->token_tail->next = token_after;
                                }
                                else 
                                {
                                    end_line->token_tail = lines_tail->token_tail;
                                }
                                fprintf(stderr, "head: %s tail: %s\n", start_line->token_head->value, start_line->token_tail->value);
                                fprintf(stderr, "head: %s tail: %s\n", lines_head->token_head->value, lines_tail->token_tail->value);
                                fprintf(stderr, "root: %d, start: %d\n", root, start_line);
                            }
                            else 
                            {
                                if (token_before) {
                                    // Connect token_before to the first new token
                                    token_before->next = lines_head->token_head;
                                    lines_head->token_head->prev = token_before;
                                    lines_head->token_tail->next = NULL;
                                    start_line->token_tail = lines_head->token_tail;
                                } else {
                                    // If no token_before, the new tokens start the line token list
                                    lines_head->token_head->prev = NULL;
                                    lines_head->token_tail->next = NULL;
                                    start_line->token_head = lines_head->token_head;
                                    start_line->token_tail = lines_head->token_tail;
                                }
                
                                if (token_after) {
                                    // Connect token_after to the last new token
                                    token_after->prev = lines_tail->token_tail;
                                    lines_tail->token_tail->next = token_after;
                                    lines_tail->token_head->prev = NULL;
                                    end_line->token_head = lines_tail->token_head;
                                } else {
                                    // If no token_after, the new tokens end the line token list
                                    lines_tail->token_head->prev = NULL;
                                    lines_tail->token_tail->next = NULL;
                                    end_line->token_head = lines_tail->token_head;
                                    end_line->token_tail = lines_tail->token_tail;
                                }
                            }
                        }
        
        
        
                        

                        fprintf(stderr, "before: %s, start: %s, end: %s, after: %s\n", token_before ? token_before->value : "", token_start ? token_start->value : "", token_end ? token_end->value : "", token_after ? token_after->value : "");
        
                        if (end_line_number - start_line_number > 1)
                        {
        
                        }
                        // clear_diagnostics(uri->valuestring);
                        send_diagnostics(uri->valuestring, root);
                        print_lines_inorder(stderr, root);
                        fflush(stderr);
                    }
                }


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
        print_lines_inorder(stdout, lines_root);
    }

    return 0;
}

