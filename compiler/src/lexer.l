%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

LineNode* lines_root = NULL;
LineNode* lines_head = NULL;
LineNode* lines_tail = NULL;

int max(int a, int b) { return a > b ? a : b; }
int height(LineNode* n) { return n ? n->height : 0; }
int size(LineNode* n) { return n ? n->subtree_size : 0; }

void update_height_and_size(LineNode* n) {
    if (!n) return;
    n->height = 1 + max(height(n->left), height(n->right));
    n->subtree_size = 1 + size(n->left) + size(n->right);
}

LineNode* rotate_right(LineNode* y) {
    LineNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->right = y;
    x->parent = y->parent;
    y->parent = x;
    update_height_and_size(y);
    update_height_and_size(x);
    return x;
}

LineNode* rotate_left(LineNode* x) {
    LineNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->left = x;
    y->parent = x->parent;
    x->parent = y;
    update_height_and_size(x);
    update_height_and_size(y);
    return y;
}

int get_balance(LineNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

LineNode* balance_node(LineNode* node) {
    update_height_and_size(node);
    int balance = get_balance(node);

    if (balance > 1) {
        if (get_balance(node->left) < 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1) {
        if (get_balance(node->right) > 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

LineNode* create_line_node() {
    LineNode* node = malloc(sizeof(LineNode));
    memset(node, 0, sizeof(LineNode));
    node->height = 1;
    node->subtree_size = 1;
    return node;
}

void insert_into_linked_list(LineNode* new_line, LineNode* next_line) {
    if (!lines_head) {
        lines_head = lines_tail = new_line;
    } else if (!next_line) {
        new_line->prev = lines_tail;
        lines_tail->next = new_line;
        lines_tail = new_line;
    } else {
        new_line->next = next_line;
        new_line->prev = next_line->prev;
        if (next_line->prev) next_line->prev->next = new_line;
        else lines_head = new_line;
        next_line->prev = new_line;
    }
}

LineNode* insert_line_by_index(LineNode* root, LineNode* new_node, int index, int* inserted_index) {
    int left_size = root ? size(root->left) : 0;
    if (!root) {
        insert_into_linked_list(new_node, NULL);
        if (inserted_index) *inserted_index = 0;
        return new_node;
    } else if (index <= left_size) {
        root->left = insert_line_by_index(root->left, new_node, index, inserted_index);
        if (root->left) root->left->parent = root;
        if (inserted_index && *inserted_index == left_size)
            insert_into_linked_list(new_node, root);
    } else {
        root->right = insert_line_by_index(root->right, new_node, index - left_size - 1, inserted_index);
        if (root->right) root->right->parent = root;
        if (inserted_index && *inserted_index == left_size + 1)
            insert_into_linked_list(new_node, root->next);
    }
    return balance_node(root);
}

LineNode* get_line_by_index(LineNode* root, int index) {
    if (!root) return NULL;
    int left_size = size(root->left);
    if (index < left_size) return get_line_by_index(root->left, index);
    if (index == left_size) return root;
    return get_line_by_index(root->right, index - left_size - 1);
}

LineNode* min_node(LineNode* node) {
    while (node->left) node = node->left;
    return node;
}

LineNode* remove_line_by_index(LineNode* root, int index) {
    if (!root) return NULL;
    int left_size = size(root->left);

    if (index < left_size) {
        root->left = remove_line_by_index(root->left, index);
    } else if (index > left_size) {
        root->right = remove_line_by_index(root->right, index - left_size - 1);
    } else {
        if (root->prev) root->prev->next = root->next;
        else lines_head = root->next;
        if (root->next) root->next->prev = root->prev;
        else lines_tail = root->prev;
        Token* tok = root->token_head;
        while (tok) {
            Token* next = tok->next;
            free(tok->value);
            if (tok->error) free(tok->error);
            free(tok);
            tok = next;
        }
        if (!root->left || !root->right) {
            LineNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            LineNode* min = min_node(root->right);
            root->token_head = min->token_head;
            root->token_tail = min->token_tail;
            root->right = remove_line_by_index(root->right, 0);
        }
    }
    return balance_node(root);
}

void add_token(const char* type, const char* value, int line_index, int col, const char* error) {
    Token* t = malloc(sizeof(Token));
    t->type = type;
    t->value = strdup(value);
    t->column = col;
    t->length = strlen(value);
    t->error = error ? strdup(error) : NULL;
    t->next = NULL;
    t->prev = NULL;

    LineNode* line = get_line_by_index(lines_root, line_index);
    if (!line) {
        line = create_line_node();
        int inserted_index = line_index;
        lines_root = insert_line_by_index(lines_root, line, line_index, &inserted_index);
    }
    t->line = line;

    if (!line->token_head) {
        line->token_head = line->token_tail = t;
    } else {
        line->token_tail->next = t;
        t->prev = line->token_tail;
        line->token_tail = t;
    }
}

int curr_line = 0;
int curr_col = 0;

#define ADD_TOKEN(TYPE) \
    add_token(TYPE, yytext, curr_line, curr_col, NULL); \
    curr_col += yyleng;

#define ADD_ERROR_TOKEN(MSG) \
    add_token("ERROR", yytext, curr_line, curr_col, MSG); \
    curr_col += yyleng;
%}

%option noyywrap

%x COMMENT

%%

" "       { curr_col += yyleng; }
"\t"      { curr_col += (8 - ((curr_col - 1) % 8)); }
"\n"      { curr_line++; curr_col = 0; }

"int"     { ADD_TOKEN("KEYWORD_INT"); }
"char"    { ADD_TOKEN("KEYWORD_CHAR"); }
"float"   { ADD_TOKEN("KEYWORD_FLOAT"); }
"return"  { ADD_TOKEN("KEYWORD_RETURN"); }
"if"      { ADD_TOKEN("KEYWORD_IF"); }
"else"    { ADD_TOKEN("KEYWORD_ELSE"); }
"while"   { ADD_TOKEN("KEYWORD_WHILE"); }
"for"     { ADD_TOKEN("KEYWORD_FOR"); }

0[xX][0-9a-fA-F]+      { ADD_TOKEN("HEX_NUMBER"); }
0[bB][01]+             { ADD_TOKEN("BINARY_NUMBER"); }

0[xX][^0-9a-fA-F]+     { ADD_ERROR_TOKEN("Invalid hexadecimal literal"); }
0[bB][^01]+            { ADD_ERROR_TOKEN("Invalid binary literal"); }

[0-9]+\.[0-9]+         { ADD_TOKEN("FLOAT_NUMBER"); }
[0-9]+                 { ADD_TOKEN("DECIMAL_NUMBER"); }

[a-zA-Z_][a-zA-Z0-9_]* { ADD_TOKEN("IDENTIFIER"); }
[0-9]+[a-zA-Z_][a-zA-Z0-9_]* { ADD_ERROR_TOKEN("Identifiers cannot start with a digit"); }

\"([^\\\"\n]|\\.)*\" { ADD_TOKEN("STRING_LITERAL"); }

\'([^\\\'\n]|\\.)\' { ADD_TOKEN("CHAR_LITERAL"); }

"//".*     { ADD_TOKEN("COMMENT"); }
"/*"       { BEGIN(COMMENT); }

<COMMENT>{
    "*/"   { BEGIN(INITIAL); ADD_TOKEN("MULTILINE_COMMENT_END"); }
    .|\n   { }
}

"=="      { ADD_TOKEN("OP_EQ"); }
"!="      { ADD_TOKEN("OP_NEQ"); }
"<="      { ADD_TOKEN("OP_LE"); }
">="      { ADD_TOKEN("OP_GE"); }
"="       { ADD_TOKEN("OP_ASSIGN"); }
"&&"      { ADD_TOKEN("OP_AND"); }
"\|\|"    { ADD_TOKEN("OP_OR"); }
"!"       { ADD_TOKEN("OP_NOT"); }

"[-+*/%]" { ADD_TOKEN("OPERATOR"); }

"("       { ADD_TOKEN("LPAREN"); }
")"       { ADD_TOKEN("RPAREN"); }
"{"       { ADD_TOKEN("LBRACE"); }
"}"       { ADD_TOKEN("RBRACE"); }
";"       { ADD_TOKEN("SEMICOLON"); }
","       { ADD_TOKEN("COMMA"); }

.         { 
    char msg[128];
    snprintf(msg, sizeof(msg), "Unrecognized character '%s'", yytext);
    ADD_ERROR_TOKEN(msg);
}

%%