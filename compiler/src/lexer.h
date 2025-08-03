#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
    const char* type;
    char* value;
    int line;
    int column;
    char* error;
    struct Token* next;
} Token;

extern Token* token_list_head;
void free_token_list(void);

#endif