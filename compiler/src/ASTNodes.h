#ifndef AST_NODES_H
#define AST_NODES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum operator_t
{
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
} operator_t;

typedef enum primitive_t
{
    PRIMITIVE_CHAR,
    PRIMITIVE_SHORT,
    PRIMITIVE_INT,
    PRIMITIVE_LONG,
} primitive_t;

typedef struct statement_t
{
    union {
        struct if_statement_t* if_statement;
        struct for_statement_t* for_statement;
        struct expression_t* return_expression;
        struct block_item_t* block;
    };

    enum {
        STATEMENT_RETURN,
        STATEMENT_IF,
        STATEMENT_FOR,
        STATEMENT_BLOCK,
    } statementType;
} statement_t;

typedef struct variable_declaration_t
{
    bool static_var;
    bool mutable_var;
    char* name;
    struct type_t* type;
    struct expression_t* initializer;
} variable_declaration_t;

typedef struct function_definition_t
{
    char* function_name;
    struct parameter_list_t* parameters;
    struct statement_t* statement;
    struct type_t* return_type;
} function_definition_t;

typedef struct argument_list_t
{
    struct expression_t* expression;
    struct argument_list_t* next;
} argument_list_t;

typedef struct function_call_t
{
    char* function_name;
    struct argument_list_t* args;
} function_call_t;

typedef struct expression_t
{
    union {
        struct { 
            struct expression_t* left; 
            operator_t op; 
            struct expression_t* right; 
        } compound_expression;
        struct {
            char* identifier;
            struct expression_t* value;
        } assignment_expression;
        struct function_call_t* function_call;
        struct literal_t* literal;
        char* identifier;
        struct lamda_t* lamda;
    };

    enum 
    {
        EXPRESSION_COMPOUND,
        EXPRESSION_LITERAL,
        EXPRESSION_IDENTIFIER,
        EXPRESSION_LAMDA,
        EXPRESSION_ASSIGNMENT,
        EXPRESSION_FUNCTION_CALL,
    } expression_type;
} expression_t;

typedef struct type_definition_t
{
    char* identifier;
    struct type_t* type;
} type_definition_t;

typedef struct block_item_t
{
    union {
        struct statement_t* statement;
        struct variable_declaration_t* variable_declaration;
        struct function_definition_t* function_definition;
        struct type_definition_t* type_definition;
        struct expression_t* expression;
    };

    enum {
        BLOCK_ITEM_STATEMENT,
        BLOCK_ITEM_VARIABLE_DECLARATION,
        BLOCK_ITEM_FUNCTION_DEFINITION,
        BLOCK_ITEM_TYPE_DEFINITION,
        BLOCK_ITEM_EXPRESSION,
    } blockItemType;

    struct block_item_t* next;
} block_item_t;

typedef struct lamda_t
{
    struct parameter_list_t* parameter_list;
    struct type_t* return_type;
    struct statement_t* statement;
    char* name;
} lamda_t;

typedef struct literal_t
{
    union {
        long value_int;
        double value_float;
        char* value_string;
        char value_char;
    };

    enum {
        LITERAL_INT,
        LITERAL_FLOAT,
        LITERAL_STRING,
        LITERAL_CHAR,
    } literalType;
} literal_t;

typedef struct type_t
{
    union {
        char* identifier;
        primitive_t primitive;
        struct lamda_type_t* lamda;
        struct struct_member_t* struct_member;
        struct enum_member_t* enum_member;
        struct union_member_t* union_member;
    };

    enum {
        TYPE_PRIMITIVE,
        TYPE_LAMDA,
        TYPE_IDENTIFIER,
        TYPE_STRUCT,
        TYPE_ENUM,
        TYPE_UNION,
    } typeType;
} type_t;

typedef struct lamda_type_t
{
    struct parameter_list_t* parameter_list;
    struct type_t* return_type;
} lamda_type_t;

typedef struct parameter_list_t
{
    struct type_t* type;
    char* name;
    struct parameter_list_t* next;
} parameter_list_t;

typedef struct struct_member_t
{
    char* name;
    struct type_t* type;
    struct struct_member_t* next;
} struct_member_t;

typedef struct union_member_t
{
    char* name;
    struct type_t* type;
    struct union_member_t* next;
} union_member_t;

typedef struct enum_member_t
{
    char* name;
    struct enum_member_t* next;
} enum_member_t;

typedef struct if_statement_t
{
    struct expression_t* expression;
    struct statement_t* statement;
} if_statement_t;

typedef struct for_statement_t
{
    // TODO update this
    struct statement_t* initialize;
    struct expression_t* condition;
    struct statement_t* loop;
} for_statement_t;


struct block_item_t* create_block_expression(expression_t* expression);
struct block_item_t* create_block_type_definition(type_definition_t* type_definition);
struct block_item_t* create_block_function_definition(function_definition_t* function_definition);
struct block_item_t* create_block_variable_declaration(variable_declaration_t* variable_declaration);
struct block_item_t* create_block_statement(statement_t* statement);

struct literal_t* create_literal_char(char value_char);
struct literal_t* create_literal_string(char* value_string);
struct literal_t* create_literal_float(double value_float);
struct literal_t* create_literal_int(long value_int);

struct expression_t* create_expression_literal(literal_t* literal);
struct expression_t* create_expression_compound(expression_t* left, operator_t op, expression_t* right);
struct expression_t* create_expression_identifier(char* identifier);
struct expression_t* create_expression_lamda(struct lamda_t* lamda);
struct expression_t* create_expression_assignment(char* identifier, expression_t* value);
struct expression_t* create_expression_function_call(struct function_call_t* function_call);

struct statement_t *create_statement_block(struct block_item_t* block);
struct statement_t* create_statement_return(struct expression_t* expression);
struct statement_t* create_statement_if(struct if_statement_t* if_statement);
struct statement_t* create_statement_for(struct for_statement_t* for_statement);

struct type_t* create_identifier_type(char* identifier);
struct type_t* create_lamda_type(struct lamda_type_t* lamda);
struct type_t* create_primitive_type(primitive_t primitive_t);
struct type_t* create_struct_type(struct struct_member_t* struct_type);
struct type_t* create_union_type(struct union_member_t* uion_type);
struct type_t* create_enum_type(struct enum_member_t* enum_member);

struct function_definition_t* create_function_definition(char* function_name, struct parameter_list_t* parameters, struct statement_t* statement, struct type_t* return_type);

struct parameter_list_t* create_parameter(char* identifier, type_t* type, struct parameter_list_t* next);

struct lamda_type_t* create_type_lamda(struct parameter_list_t* parameter_list, struct type_t* return_type);

struct lamda_t* create_lamda(struct parameter_list_t* parameter_list, struct type_t* return_type, struct statement_t* statement);

struct variable_declaration_t* create_variable_declaration(bool static_var, bool mutable_var, char* name, struct type_t* type, struct expression_t* initializer);

struct type_definition_t* create_type_definition(char* identifier, struct type_t* type);

struct struct_member_t* create_struct_member(char* name, struct type_t* type, struct struct_member_t* next);

struct union_member_t* create_union_member(char* name, struct type_t* type, struct union_member_t* next);

struct enum_member_t* create_enum_member(char* name, struct enum_member_t* next);

struct if_statement_t* create_if_statement(struct expression_t* expression, struct statement_t* statement);

struct for_statement_t* create_for_statement(struct statement_t* initializer, struct expression_t* condition, struct statement_t* loop);

struct function_call_t* create_function_call(char* name, struct argument_list_t* args);

struct argument_list_t* create_argument_list(struct expression_t* expression);

typedef struct function_t
{
    union {
        lamda_t* lamda;
        function_definition_t* function_definition;
    };

    enum {
        FUNCTION_DEFINITION,
        FUNCTION_LAMDA,
    } functionType;
    struct function_t* next;
} function_t;

#endif