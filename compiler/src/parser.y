%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ASTNodes.h"

void yyerror(const char *s);
int yylex(void);

block_item_t *ast_root = NULL;

static int indent_level = 0;
void indent() {
    for (int i=0; i < indent_level; i++)
        fprintf(stderr, "  ");
}
%}

%union {
    int int_val;
    char *str_val;
    struct statement_t* statement;
    struct expression_t* expression;
    struct literal_t* literal;
    struct function_definition_t* function_definition;
    int primitive;
    struct type_t* type;
    struct parameter_list_t* parameters;
    struct lamda_type_t* lamda_type;
    struct lamda_t* lamda;
    struct variable_declaration_t* variable_declaration;
    struct type_definition_t* type_definition;
    struct struct_member_t* struct_member;
    struct enum_member_t* enum_member;
    struct union_member_t* union_member;
    struct if_statement_t* if_statement;
    struct for_statement_t* for_statement;
    struct block_item_t* block_item;
    struct argument_list_t* arg;
    struct function_call_t* function_call;
}

%token FUNCTION CHAR SHORT INT LONG STATIC MUT IMMUT RETURN TYPE STRUCT ENUM UNION IF FOR
%token EQ NEQ ARROW

%token <int_val> INTEGER_LITERAL
%token <str_val> IDENTIFIER

%type <block_item> input block_item_list block_item
%type <statement> statement
%type <expression> expression numeric_expression initializer
%type <function_definition> function_definition
%type <primitive> primitive static_var mutable_var
%type <type> type
%type <parameters> parameter parameter_list
%type <lamda_type> lamda_type
%type <lamda> lamda
%type <variable_declaration> variable_declaration
%type <type_definition> type_definition
%type <struct_member> struct_member struct_members struct_type
%type <union_member> union_member union_members union_type
%type <enum_member> enum_type enum_members enum_member
%type <if_statement> if_statement
%type <for_statement> for_statement
%type <arg> arg_list arg
%type <function_call> function_call

%left '+' '-'
%left '*' '/'

%start input

%%

input:
    block_item_list {
        ast_root = $1;
    }
    ;

block_item_list:
    { $$ = NULL; }  // Empty case
    | block_item_list block_item {  // Proper recursion (supports 1, 2, 3, ... items
        if ($1 == NULL) {
            $$ = $2;  // First item in the list
        } else {
            // Append $2 to the end of the list
            struct block_item_t *last = $1;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = $2;
            $$ = $1;
        }
      }
    ;

block_item:
    ';' { $$ = NULL; }
    | statement { $$ = create_block_statement($1); }
    | expression ';' { $$ = create_block_expression($1); }
    | function_definition { $$ = create_block_function_definition($1); }
    | variable_declaration ';' { $$ = create_block_variable_declaration($1); }
    | type_definition ';' { $$ = create_block_type_definition($1); }
    ;

function_call:
    IDENTIFIER '(' arg_list ')' { $$ = create_function_call($1, $3); }
    ;

arg_list:
    { $$ = NULL; }  // Empty case
    | arg { $$ = $1; }
    | arg_list ',' arg {  // Proper recursion (supports 1, 2, 3, ... items
        if ($1 == NULL) {
            $$ = $3;  // First item in the list
        } else {
            // Append $2 to the end of the list
            struct argument_list_t *last = $1;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = $3;
            $$ = $1;
        }
      }
    ;

arg:
    expression { $$ = create_argument_list($1); }
    ;

statement:
    RETURN expression ';' { $$ = create_statement_return($2); }
    | if_statement { $$ = create_statement_if($1); }
    | for_statement { $$ = create_statement_for($1); }
    | '{' block_item_list '}' { $$ = create_statement_block($2); }
    ;

if_statement:
    IF '(' numeric_expression ')' statement { $$ = create_if_statement($3, $5); }
    ;

for_statement:
    FOR { $$ = NULL; }
    ;

type_definition:
    TYPE IDENTIFIER '=' type { $$ = create_type_definition($2, $4); }
    ;

variable_declaration:
    static_var mutable_var IDENTIFIER ':' type initializer { $$ = create_variable_declaration($1, $2, $3, $5, $6); }
    ;

initializer:
    { $$ = NULL; }
    | '=' expression { $$ = $2; }
    ;

static_var:
    { $$ = 0; }
    | STATIC { $$ = 1; }
    ;

mutable_var:
    MUT { $$ = 1; }
    | IMMUT { $$ = 0; }
    ;

function_definition:
    FUNCTION IDENTIFIER '(' parameter_list ')' ':' type statement { $$ = create_function_definition($2, $4, $8, $7); }
    ;

primitive:
    CHAR { $$ = PRIMITIVE_CHAR; }
    | SHORT { $$ = PRIMITIVE_SHORT; }
    | INT { $$ = PRIMITIVE_INT; }
    | LONG { $$ = PRIMITIVE_LONG; }
    ;

type:
    primitive { $$ = create_primitive_type($1); }
    | IDENTIFIER { $$ = create_identifier_type($1); }
    | lamda_type { $$ = create_lamda_type($1); }
    | struct_type { $$ = create_struct_type($1); }
    | union_type { $$ = create_union_type($1); }
    | enum_type { $$ = create_enum_type($1); }
    ;

enum_type:
    ENUM '{' enum_members '}' { $$ = $3; }
    ;

enum_members:
    { $$ = NULL; }
    | enum_members ',' enum_member { 
        if ($1 == NULL)
        {
            $$ = $3;
        }
        else
        {
            struct enum_member_t* last = $1;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = $3;
            $$ = $1;
        }
      }
    | enum_member { $$ = $1; }
    | enum_members ',' { $$ = $1; }
    ;

enum_member:
    IDENTIFIER { $$ = create_enum_member($1, NULL); }
    ;
    

struct_type:
    STRUCT '{' struct_members '}' { $$ = $3; } 
    ;

union_type:
    UNION '{' union_members '}' { $$ = $3; } 
    ;

lamda_type:
    '(' parameter_list ')' ARROW type { $$ = create_type_lamda($2, $5); }
    ;

struct_members:
    { $$ = NULL; }
    | struct_member { $$ = $1; }
    | struct_members struct_member { 
        if ($1 == NULL)
        {
            $$ = $2;
        }
        else
        {
            struct struct_member_t* last = $1;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = $2;
            $$ = $1;
        }
     }
    ;

struct_member:
    IDENTIFIER ':' type ';' { $$ = create_struct_member($1, $3, NULL); }
    ;

union_members:
    { $$ = NULL; }
    | union_member { $$ = $1; }
    | union_members union_member { 
        if ($1 == NULL)
        {
            $$ = $2;
        }
        else
        {
            struct union_member_t* last = $1;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = $2;
            $$ = $1;
        }
     }
    ;

union_member:
    IDENTIFIER ':' type ';' { $$ = create_union_member($1, $3, NULL); }
    ;

parameter_list:
    { $$ = NULL; }
    | parameter { $$ = $1; }
    | parameter_list ',' parameter {
        if ($1 == NULL)
        {
            $$ = $3;
        }
        else
        {
            struct parameter_list_t* last = $1;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = $3;
            $$ = $1;
        }
      }
    ;

parameter:
    IDENTIFIER ':' type { $$ = create_parameter($1, $3, NULL); }
    ;

lamda:
    '(' parameter_list ')' ':' type ARROW statement { $$ = create_lamda($2, $5, $7); }
    ;

expression:
    numeric_expression { $$ = $1; }
    | lamda { $$ = create_expression_lamda($1); }
    | '(' expression ')' {
        $$ = $2;  // Just return inner expression
    }
    ;

numeric_expression:
      INTEGER_LITERAL {
        literal_t* lit = create_literal_int($1);
        $$ = create_expression_literal(lit);
    }
    | IDENTIFIER {
        // For now, treat identifiers as strings in literals or extend expression_t to support identifiers properly
        // To fully support identifiers, you'd want a separate AST node type for them
        $$ = create_expression_identifier(strdup($1));
        free($1);
    }
    | function_call { $$ = create_expression_function_call($1);  }
    | numeric_expression '+' numeric_expression {
        $$ = create_expression_compound($1, OPERATOR_PLUS, $3);
    }
    | numeric_expression '-' numeric_expression {
        $$ = create_expression_compound($1, OPERATOR_MINUS, $3);
    }
    | numeric_expression '*' numeric_expression {
        $$ = create_expression_compound($1, OPERATOR_MULTIPLY, $3);
    }
    | numeric_expression '/' numeric_expression {
        $$ = create_expression_compound($1, OPERATOR_DIVIDE, $3);
    }
    | IDENTIFIER '=' expression { $$ = create_expression_assignment($1, $3); }
    | '(' numeric_expression ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
