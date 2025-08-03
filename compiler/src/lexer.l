%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token structure
typedef struct Token {
    const char* type;
    char* value;
    int line;
    int column;
    char* error; // NULL if valid
    struct Token* next;
} Token;

// Head and tail of token list
Token* token_list_head = NULL;
Token* token_list_tail = NULL;

int curr_line = 0;
int curr_col = 0;

// Utility: add token to the list
void add_token(const char* type, const char* value, int line, int col, const char* error) {
    Token* t = (Token*)malloc(sizeof(Token));
    t->type = type;
    t->value = strdup(value);
    t->line = line;
    t->column = col;
    t->error = error ? strdup(error) : NULL;
    t->next = NULL;

    if (!token_list_head) {
        token_list_head = token_list_tail = t;
    } else {
        token_list_tail->next = t;
        token_list_tail = t;
    }
}

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

// You can access the token list from outside via `token_list_head`
// Clean-up function (optional)
void free_token_list() {
    Token* t = token_list_head;
    while (t) {
        Token* next = t->next;
        free(t->value);
        if (t->error) free(t->error);
        free(t);
        t = next;
    }
    token_list_head = token_list_tail = NULL;
}
