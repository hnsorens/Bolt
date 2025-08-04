#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

// Token struct (with doubly linked list)
typedef struct Token {
    const char* type;
    char* value;
    int column;
    int length;
    char* error;
    struct Token* next;
    struct Token* prev;
    struct LineNode* line;  // backpointer
} Token;

typedef struct LineNode {
    Token* token_head;
    Token* token_tail;

    struct LineNode* left;
    struct LineNode* right;
    struct LineNode* parent;

    struct LineNode* prev;
    struct LineNode* next;

    int height;
    int subtree_size;
} LineNode;

#endif