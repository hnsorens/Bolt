%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>

// Declare yylval from Bison
extern YYSTYPE yylval;
%}

%x COMMENT

DIGIT       [0-9]
HEX_DIGIT   [0-9a-fA-F]
BIN_DIGIT   [01]
ID_START    [a-zA-Z_]
ID_CONT     [a-zA-Z0-9_]*

%%

"//".*                      ;  // skip single-line comments

"/*"                        { BEGIN(COMMENT); }
<COMMENT>"*/"               { BEGIN(INITIAL); }
<COMMENT>.|\n               ;  // skip comment contents

"function"                  { return FUNCTION; }
"char"                  { return CHAR; }
"short"                  { return SHORT; }
"int"                  { return INT; }
"long"                  { return LONG; }
"=>"                    { return ARROW; }
"mut"                   { return MUT; }
"immut"                 { return IMMUT; }
"static"                { return STATIC; }
"return"                { return RETURN; }
"type"                  { return TYPE; }
"struct"                { return STRUCT; }
"enum"                  { return ENUM; }
"union"                 { return UNION; }
"if"                    { return IF; }
"for"                   { return FOR; }



"=="                        { return EQ; }
"!="                        { return NEQ; }
"+"                         { return '+'; }
"-"                         { return '-'; }
"*"                         { return '*'; }
"/"                         { return '/'; }
"="                         { return '='; }
";"                         { return ';'; }
":"                         { return ':'; }
","                         { return ','; }
"("                         { return '('; }
")"                         { return ')'; }
"{"                         { return '{'; }
"}"                         { return '}'; }

"0x"{HEX_DIGIT}+            {
                              yylval.int_val = (int)strtol(yytext, NULL, 16);
                              return INTEGER_LITERAL;
                            }
"0b"{BIN_DIGIT}+            {
                              yylval.int_val = (int)strtol(yytext+2, NULL, 2);
                              return INTEGER_LITERAL;
                            }
{DIGIT}+                   {
                              yylval.int_val = atoi(yytext);
                              return INTEGER_LITERAL;
                            }

{ID_START}{ID_CONT}        {
                              yylval.str_val = strdup(yytext);
                              return IDENTIFIER;
                            }

[ \t\r\n]+                 ;  // skip whitespace

.                          { fprintf(stderr, "Unknown char: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
