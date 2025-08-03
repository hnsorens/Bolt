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
    int line_number;

    Token* token_head;
    Token* token_tail;

    struct LineNode* left;
    struct LineNode* right;

    struct LineNode* prev;  // doubly linked list of lines
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

// AVL rotations
LineNode* rotate_right(LineNode* y) {
    LineNode* x = y->left;
    LineNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    update_height_and_size(y);
    update_height_and_size(x);
    return x;
}

LineNode* rotate_left(LineNode* x) {
    LineNode* y = x->right;
    LineNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    update_height_and_size(x);
    update_height_and_size(y);
    return y;
}

int get_balance(LineNode* n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
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

// Helper: create a new line node
LineNode* create_line_node(int line_number) {
    LineNode* node = (LineNode*)malloc(sizeof(LineNode));
    node->line_number = line_number;
    node->token_head = NULL;
    node->token_tail = NULL;
    node->left = node->right = NULL;
    node->prev = node->next = NULL;
    node->height = 1;
    node->subtree_size = 1;
    return node;
}

// Insert new_line into linked list before 'next_line'
// If next_line is NULL, insert at tail
void insert_line_into_list(LineNode* new_line, LineNode* next_line) {
    if (!lines_head) {
        // First node ever
        lines_head = lines_tail = new_line;
        new_line->prev = new_line->next = NULL;
    } else if (!next_line) {
        // Insert at tail
        new_line->prev = lines_tail;
        new_line->next = NULL;
        lines_tail->next = new_line;
        lines_tail = new_line;
    } else {
        // Insert before next_line
        new_line->next = next_line;
        new_line->prev = next_line->prev;
        if (next_line->prev)
            next_line->prev->next = new_line;
        else
            lines_head = new_line;
        next_line->prev = new_line;
    }
}

// Insert a line node with given line_number into AVL tree rooted at root
// Return new root after insertion
LineNode* insert_line_node(LineNode* root, LineNode* new_line) {
    if (!root) {
        // Insert into linked list in correct position:
        // since this is the only node here, just insert normally
        insert_line_into_list(new_line, NULL);
        return new_line;
    }

    if (new_line->line_number < root->line_number) {
        root->left = insert_line_node(root->left, new_line);
    } else if (new_line->line_number > root->line_number) {
        root->right = insert_line_node(root->right, new_line);
    } else {
        // Line number already exists — free new_line and return root
        free(new_line);
        return root;
    }

    // Balance AVL tree
    root = balance_node(root);
    return root;
}

// Search line node by line_number in AVL tree
LineNode* find_line_node(LineNode* root, int line_number) {
    if (!root) return NULL;
    if (line_number == root->line_number)
        return root;
    else if (line_number < root->line_number)
        return find_line_node(root->left, line_number);
    else
        return find_line_node(root->right, line_number);
}

// Get or create line node for given line_index
LineNode* get_or_create_line(int line_index) {
    LineNode* node = find_line_node(lines_root, line_index);
    if (node) return node;

    // Not found, create new
    LineNode* new_line = create_line_node(line_index);

    // Insert into AVL tree (this will also insert into linked list)
    lines_root = insert_line_node(lines_root, new_line);

    return new_line;
}

// Add token to line
void add_token(const char* type, const char* value, int line_idx, int col, const char* error) {
    Token* t = (Token*)malloc(sizeof(Token));
    t->type = type;
    t->value = strdup(value);
    t->column = col;
    t->length = (int)strlen(value);
    t->error = error ? strdup(error) : NULL;
    t->next = NULL;
    t->prev = NULL;

    LineNode* line_obj = get_or_create_line(line_idx);
    t->line = line_obj;

    if (!line_obj->token_head) {
        line_obj->token_head = line_obj->token_tail = t;
    } else {
        line_obj->token_tail->next = t;
        t->prev = line_obj->token_tail;
        line_obj->token_tail = t;
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
    .|\n   { /* skip comment content */ }
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