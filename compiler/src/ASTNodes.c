#include "ASTNodes.h"
#include <stdio.h>

struct block_item_t* create_block_statement(statement_t* statement)
{
    struct block_item_t* block_item = (struct block_item_t*)malloc(sizeof(struct block_item_t));
    block_item->blockItemType = BLOCK_ITEM_STATEMENT;
    block_item->statement = statement;
    block_item->next = NULL;
    return block_item;
}

struct block_item_t* create_block_variable_declaration(variable_declaration_t* variable_declaration)
{
    struct block_item_t* block_item = (struct block_item_t*)malloc(sizeof(struct block_item_t));
    block_item->blockItemType = BLOCK_ITEM_VARIABLE_DECLARATION;
    block_item->variable_declaration = variable_declaration;
    block_item->next = NULL;
    return block_item;
}

struct block_item_t* create_block_function_definition(function_definition_t* function_definition)
{
    struct block_item_t* block_item = (struct block_item_t*)malloc(sizeof(struct block_item_t));
    block_item->blockItemType = BLOCK_ITEM_FUNCTION_DEFINITION;
    block_item->function_definition = function_definition;
    block_item->next = NULL;
    return block_item;
}

struct block_item_t* create_block_type_definition(type_definition_t* type_definition)
{
    struct block_item_t* block_item = (struct block_item_t*)malloc(sizeof(struct block_item_t));
    block_item->blockItemType = BLOCK_ITEM_TYPE_DEFINITION;
    block_item->type_definition = type_definition;
    block_item->next = NULL;
    return block_item;
}

struct block_item_t* create_block_expression(expression_t* expression)
{
    struct block_item_t* block_item = (struct block_item_t*)malloc(sizeof(struct block_item_t));
    block_item->blockItemType = BLOCK_ITEM_EXPRESSION;
    block_item->expression = expression;
    block_item->next = NULL;
    return block_item;
}

struct statement_t* create_statement_return(struct expression_t* expression)
{
    struct statement_t *statement = (struct statement_t *)malloc(sizeof(statement_t));
    statement->statementType = STATEMENT_RETURN;
    statement->return_expression = expression;
    return statement;
}

struct statement_t* create_statement_if(struct if_statement_t* if_statement)
{
    struct statement_t *statement = (struct statement_t *)malloc(sizeof(statement_t));
    statement->statementType = STATEMENT_IF;
    statement->if_statement = if_statement;
    return statement;
}

struct statement_t* create_statement_for(struct for_statement_t* for_statement)
{
    struct statement_t *statement = (struct statement_t *)malloc(sizeof(statement_t));
    statement->statementType = STATEMENT_FOR;
    statement->for_statement = for_statement;
    return statement;
}

struct statement_t* create_statement_block(struct block_item_t* block)
{
    struct statement_t *statement = (struct statement_t *)malloc(sizeof(statement_t));
    statement->statementType = STATEMENT_BLOCK;
    statement->block = block;
    return statement;
}

struct expression_t* create_expression_compound(expression_t* left, operator_t op, expression_t* right)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_COMPOUND;
    expression->compound_expression.left = left;
    expression->compound_expression.op = op;
    expression->compound_expression.right = right;
    return expression;
}

struct expression_t* create_expression_assignment(char* identifier, expression_t* value)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_ASSIGNMENT;
    expression->assignment_expression.identifier = identifier;
    expression->assignment_expression.value = value;
    return expression;
}

struct expression_t* create_expression_literal(literal_t* literal)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_LITERAL;
    expression->literal = literal;
    return expression;
}

struct expression_t* create_expression_lamda(struct lamda_t* lamda)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_LAMDA;
    expression->lamda = lamda;
    return expression;
}

struct expression_t* create_expression_function_call(struct function_call_t* function_call)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_FUNCTION_CALL;
    expression->function_call = function_call;
    return expression;
}

struct expression_t* create_expression_identifier(char* identifier)
{
    struct expression_t* expression = (struct expression_t*)malloc(sizeof(expression_t));
    expression->expression_type = EXPRESSION_IDENTIFIER;
    expression->identifier = identifier;
    return expression;
}

struct function_call_t* create_function_call(char* name, struct argument_list_t* args)
{
    struct function_call_t* function_call = (struct function_call_t*)malloc(sizeof(function_call_t));
    function_call->function_name = name;
    function_call->args = args;
    return function_call;
}

struct argument_list_t* create_argument_list(struct expression_t* expression)
{
    struct argument_list_t* args = (struct argument_list_t*)malloc(sizeof(argument_list_t));
    args->expression = expression;
    args->next = NULL;
    return args;
}

struct literal_t* create_literal_int(long value_int)
{
    literal_t* literal = (struct literal_t*)malloc(sizeof(literal_t));
    literal->literalType = LITERAL_INT;
    literal->value_char = value_int;
    return literal;
}

struct literal_t* create_literal_float(double value_float)
{
    struct literal_t* literal = (struct literal_t*)malloc(sizeof(struct literal_t));
    literal->literalType = LITERAL_FLOAT;
    literal->value_float = value_float;
    return literal;
}

struct literal_t* create_literal_string(char* value_string)
{
    struct literal_t* literal = (struct literal_t*)malloc(sizeof(struct literal_t));
    literal->literalType = LITERAL_STRING;
    literal->value_string = value_string;
    return literal;
}

struct literal_t* create_literal_char(char value_char)
{
    struct literal_t* literal = (struct literal_t*)malloc(sizeof(struct literal_t));
    literal->literalType = LITERAL_CHAR;
    literal->value_char = value_char;
    return literal;
}

struct function_definition_t* create_function_definition(char* function_name, struct parameter_list_t* parameters, struct statement_t* statement, struct type_t* return_type)
{
    struct function_definition_t* function_definition = (struct function_definition_t*)malloc(sizeof(struct function_definition_t));
    function_definition->function_name = function_name;
    function_definition->parameters = parameters;
    function_definition->statement = statement;
    function_definition->return_type = return_type;
    return function_definition;
}

struct type_t* create_primitive_type(primitive_t primitive_t)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_PRIMITIVE;
    type->primitive = primitive_t;
    return type;
}

struct type_t* create_lamda_type(struct lamda_type_t* lamda)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_LAMDA;
    type->lamda = lamda;
    return type;
}

struct type_t* create_identifier_type(char* identifier)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_IDENTIFIER;
    type->identifier = identifier;
    return type;
}

struct type_t* create_struct_type(struct struct_member_t* struct_member)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_STRUCT;
    type->struct_member = struct_member;
    return type;
}

struct type_t* create_union_type(struct union_member_t* union_member)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_UNION;
    type->union_member = union_member;
    return type;
}

struct type_t* create_enum_type(struct enum_member_t* enum_member)
{
    struct type_t* type = (struct type_t*)malloc(sizeof(struct type_t));
    type->typeType = TYPE_ENUM;
    type->enum_member = enum_member;
    return type;
}

struct parameter_list_t* create_parameter(char* identifier, type_t* type, struct parameter_list_t* next)
{
    struct parameter_list_t* parameter = (struct parameter_list_t*)malloc(sizeof(struct parameter_list_t));
    parameter->name = identifier;
    parameter->type = type;
    parameter->next = next;
    return parameter;
}

struct lamda_type_t* create_type_lamda(struct parameter_list_t* parameter_list, struct type_t* return_type)
{
    struct lamda_type_t* lamda_type = (struct lamda_type_t*)malloc(sizeof(struct lamda_type_t));
    lamda_type->return_type = return_type;
    lamda_type->parameter_list = parameter_list;
    return lamda_type;
}

struct lamda_t* create_lamda(struct parameter_list_t* parameter_list, struct type_t* return_type, struct statement_t* statement)
{
    struct lamda_t* lamda = (struct lamda_t*)malloc(sizeof(struct lamda_t));
    lamda->return_type = return_type;
    lamda->parameter_list = parameter_list;
    lamda->statement = statement;
    return lamda;
}

struct variable_declaration_t* create_variable_declaration(bool static_var, bool mutable_var, char* name, struct type_t* type, struct expression_t* initializer)
{
    struct variable_declaration_t* variable_declaration = (struct variable_declaration_t*)malloc(sizeof(variable_declaration_t));
    variable_declaration->static_var = static_var;
    variable_declaration->mutable_var = mutable_var;
    variable_declaration->name = name;
    variable_declaration->type = type;
    variable_declaration->initializer = initializer;
    return variable_declaration;
}

struct type_definition_t* create_type_definition(char* identifier, struct type_t* type)
{
    struct type_definition_t* type_definition = (struct type_definition_t*)malloc(sizeof(struct type_definition_t));
    type_definition->identifier = identifier;
    type_definition->type = type;
    return type_definition;
}

struct struct_member_t* create_struct_member(char* name, struct type_t* type, struct struct_member_t* next)
{
    struct struct_member_t* member = (struct struct_member_t*)malloc(sizeof(struct struct_member_t));
    member->name = name;
    member->type = type;
    member->next = next;
    return member;
}

struct union_member_t* create_union_member(char* name, struct type_t* type, struct union_member_t* next)
{
    struct union_member_t* member = (struct union_member_t*)malloc(sizeof(struct union_member_t));
    member->name = name;
    member->type = type;
    member->next = next;
    return member;
}

struct enum_member_t* create_enum_member(char* name, struct enum_member_t* next)
{
    struct enum_member_t* enum_member = (struct enum_member_t*)malloc(sizeof(struct enum_member_t));
    enum_member->name = name;
    enum_member->next = next;
    return enum_member;
}

struct if_statement_t* create_if_statement(struct expression_t* expression, struct statement_t* statement)
{
    struct if_statement_t* if_statement = (struct if_statement_t*)malloc(sizeof(struct if_statement_t));
    if_statement->expression = expression;
    if_statement->statement = statement;
    return if_statement;
}

struct for_statement_t* create_for_statement(struct statement_t* initializer, struct expression_t* condition, struct statement_t* loop)
{
    struct for_statement_t* for_statement = (struct for_statement_t*)malloc(sizeof(struct for_statement_t));
    for_statement->initialize = initializer;
    for_statement->condition = condition;
    for_statement->loop = loop;
    return for_statement;
}











void print_tabs(int tabs)
{
    for (int i = 0; i < tabs; i++)
    {
        fprintf(stderr, "  ");
    }
}

void print_literal(int tabs, struct literal_t* literal);
void print_expression(int tabs, struct expression_t* expression);
void print_statement(int tabs, struct statement_t* statement);
void print_operator(int tabs, operator_t operator);
void print_function_definition(int tabs, function_definition_t* function_definition);
void print_parameter_list(int tabs, parameter_list_t* parameter_list);
void print_type(int tabs, type_t* type);
void print_primitive(int tabs, primitive_t primitive);
void print_lamda_type(int tabs, lamda_type_t* lamda);
void print_lamda(int tabs, lamda_t* lamda);
void print_variable_declaration(int tabs, variable_declaration_t* variable_declaration);
void print_type_definition(int tabs, type_definition_t* type_definition);
void print_struct_member(int tabs, struct_member_t* member);
void print_enum_member(int tabs, enum_member_t* member);
void print_union_member(int tabs, union_member_t* member);
void print_if_statement(int tabs, if_statement_t* if_statement);
void print_for_statement(int tabs, for_statement_t* for_statement);
void print_block_item(int tabs, struct block_item_t* block);
void print_args(int tabs, argument_list_t* args);


void print_block_item(int tabs, struct block_item_t* block)
{
    if (!block) return;
    print_tabs(tabs);
    fprintf(stderr, "BLOCK_ITEM (");
    switch (block->blockItemType)
    {
        case BLOCK_ITEM_EXPRESSION:
            fprintf(stderr, "expression)\n");
            print_expression(tabs + 1, block->expression);
            break;
        case BLOCK_ITEM_FUNCTION_DEFINITION:
            fprintf(stderr, "function definition)\n");
            print_function_definition(tabs + 1, block->function_definition);
            break;
        case BLOCK_ITEM_TYPE_DEFINITION:
            fprintf(stderr, "type definition)\n");
            print_type_definition(tabs + 1, block->type_definition);            
            break;
        case BLOCK_ITEM_STATEMENT:
            fprintf(stderr, "statement)\n");
            print_statement(tabs + 1, block->statement);
            break;
        case BLOCK_ITEM_VARIABLE_DECLARATION:
            fprintf(stderr, "variable declaration)\n");
            print_variable_declaration(tabs + 1, block->variable_declaration);
            break;
    }
    print_block_item(tabs, block->next);
}

void print_statement(int tabs, struct statement_t* statement)
{
    if (!statement) return;
    print_tabs(tabs);
    fprintf(stderr, "STATEMENT (");
    switch (statement->statementType) {
        case STATEMENT_RETURN:
            fprintf(stderr, "return)\n");
            print_expression(tabs + 1, statement->return_expression);
            break;
        case STATEMENT_IF:
            fprintf(stderr, "if)\n");
            print_if_statement(tabs + 1, statement->if_statement);
            break;
        case STATEMENT_FOR:
            fprintf(stderr, "for)\n");
            print_for_statement(tabs + 1, statement->for_statement);
            break;
        case STATEMENT_BLOCK:
            fprintf(stderr, "block)\n");
            print_block_item(tabs + 1, statement->block);
            break;
    }
}

void print_operator(int tabs, operator_t operator)
{
    print_tabs(tabs);
    fprintf(stderr, "OPERATOR (");
    switch (operator) {
        case OPERATOR_PLUS:
            fprintf(stderr, "+)\n");
            break;
        case OPERATOR_MINUS:
            fprintf(stderr, "-)\n");
            break;
        case OPERATOR_MULTIPLY:
            fprintf(stderr, "*)\n");
            break;
        case OPERATOR_DIVIDE:
            fprintf(stderr, "/)\n");
            break;
    }
}

void print_args(int tabs, argument_list_t* args)
{
    if (!args) return;
    print_tabs(tabs);
    fprintf(stderr, "ARG\n");
    print_expression(tabs + 1, args->expression);
    print_args(tabs, args->next);
}

void print_expression(int tabs, expression_t* expression)
{
    if (!expression) return;
    print_tabs(tabs);
    fprintf(stderr, "EXPRESSION (");
    switch (expression->expression_type) {
        case EXPRESSION_COMPOUND:
        fprintf(stderr, "compound)\n");
            print_expression(tabs + 1, expression->compound_expression.left);
            print_operator(tabs + 1, expression->compound_expression.op);
            print_expression(tabs + 1, expression->compound_expression.right);
            break;
        case EXPRESSION_LITERAL:
        fprintf(stderr, "literal)\n");
            print_literal(tabs + 1, expression->literal);
            break;
        case EXPRESSION_IDENTIFIER:
            fprintf(stderr, "identifier): %s\n", expression->identifier);\
            break;
        case EXPRESSION_LAMDA:
            fprintf(stderr, "lamda)\n");
            print_lamda(tabs + 1, expression->lamda);
            break;
        case EXPRESSION_ASSIGNMENT:
            fprintf(stderr, "assignment) (%s)\n", expression->assignment_expression.identifier);
            print_expression(tabs + 1, expression->assignment_expression.value);
            break;
        case EXPRESSION_FUNCTION_CALL:
            fprintf(stderr, "function call) (%s)\n", expression->function_call->function_name);
            print_args(tabs + 1, expression->function_call->args);
            break;
    }
}

void print_literal(int tabs, literal_t* literal)
{
    if (!literal) return;
    print_tabs(tabs);
    switch (literal->literalType) {
        case LITERAL_INT:
            fprintf(stderr, "LITERAL (int) %ld\n", literal->value_int);
            break;
        case LITERAL_FLOAT:
            fprintf(stderr, "LITERAL (float) %f\n", literal->value_float);
            break;
        case LITERAL_STRING:
            fprintf(stderr, "LITERAL (string) %s\n", literal->value_string);
            break;
        case LITERAL_CHAR:
            fprintf(stderr, "LITERAL (char) %c\n", literal->value_char);
            break;
    }
}

void print_primitive(int tabs, primitive_t primitive)
{
    switch (primitive) {
        case PRIMITIVE_CHAR:
            fprintf(stderr, "PRIMITIVE (char)\n");
            break;
        case PRIMITIVE_SHORT:
        fprintf(stderr, "PRIMITIVE (short)\n");
            break;
        case PRIMITIVE_INT:
        fprintf(stderr, "PRIMITIVE (int)\n");
            break;
        case PRIMITIVE_LONG:
        fprintf(stderr, "PRIMITIVE (long)\n");
            break;
    }
}

void print_type(int tabs, type_t* type)
{
    if (!type) return;
    print_tabs(tabs);
    switch (type->typeType) {
        case TYPE_IDENTIFIER:
            fprintf(stderr, "TYPE (%s)\n", type->identifier);
            break;
        case TYPE_PRIMITIVE:
            print_primitive(tabs + 1, type->primitive);
            break;
        case TYPE_LAMDA:
            print_lamda_type(tabs, type->lamda);
            break;
        case TYPE_STRUCT:
            print_struct_member(tabs, type->struct_member);
            break;
        case TYPE_UNION:
            print_union_member(tabs, type->union_member);
            break;
        case TYPE_ENUM:
            print_enum_member(tabs + 1, type->enum_member);
            break;
    }
}

void print_parameter_list(int tabs, parameter_list_t* parameter_list)
{
    if (!parameter_list) return;
    print_tabs(tabs);
    fprintf(stderr, "PARAMETERS (%s)\n", parameter_list->name);
    print_type(tabs + 1, parameter_list->type);
    print_parameter_list(tabs, parameter_list->next);
}

void print_function_definition(int tabs, function_definition_t* function_definition)
{
    if (!function_definition) return;
    print_tabs(tabs);
    fprintf(stderr, "FUNCTION (%s)\n", function_definition->function_name);
    print_parameter_list(tabs + 1, function_definition->parameters);
    print_type(tabs + 1, function_definition->return_type);
    print_statement(tabs + 1, function_definition->statement);
}

void print_lamda(int tabs, lamda_t* lamda)
{
    if (!lamda) return;
    print_tabs(tabs);
    fprintf(stderr, "LAMDA\n");
    print_parameter_list(tabs + 1, lamda->parameter_list);
    print_type(tabs + 1, lamda->return_type);
    print_statement(tabs + 1, lamda->statement);
}

void print_lamda_type(int tabs, lamda_type_t* lamda)
{
    if (!lamda) return;
    fprintf(stderr, "LAMDA TYPE\n");
    print_parameter_list(tabs + 1, lamda->parameter_list);
    print_type(tabs + 1, lamda->return_type);
}

void print_variable_declaration(int tabs, variable_declaration_t* variable_declaration)
{
    if (!variable_declaration) return;
    print_tabs(tabs);
    fprintf(stderr, "VARIABLE DECALRATION (%s) static: %d, mutable: %d\n", variable_declaration->name, variable_declaration->static_var, variable_declaration->mutable_var);
    print_type(tabs + 1, variable_declaration->type);
    print_expression(tabs + 1, variable_declaration->initializer);
}

void print_type_definition(int tabs, type_definition_t* type_definition)
{
    if (!type_definition) return;
    print_tabs(tabs);
    fprintf(stderr, "TYPE DEFINITION (%s)\n", type_definition->identifier);
    print_type(tabs + 1, type_definition->type);
}

void print_struct_member(int tabs, struct_member_t* member)
{
    if (!member) return;
    print_tabs(tabs);
    fprintf(stderr, "STRUCT MEMBER (%s)\n", member->name);
    print_type(tabs + 1, member->type);
    print_struct_member(tabs, member->next);
}

void print_union_member(int tabs, union_member_t* member)
{
    if (!member) return;
    print_tabs(tabs);
    fprintf(stderr, "UNION MEMBER (%s)\n", member->name);
    print_type(tabs + 1, member->type);
    print_union_member(tabs, member->next);
}

void print_enum_member(int tabs, enum_member_t* member)
{
    if (!member) return;
    print_tabs(tabs);
    fprintf(stderr, "ENUM MEMBER (%s)\n", member->name);
    print_enum_member(tabs, member->next);
}

void print_if_statement(int tabs, if_statement_t* if_statement)
{
    if (!if_statement) return;
    print_tabs(tabs);
    fprintf(stderr, "IF STATEMENT\n");
    print_expression(tabs + 1, if_statement->expression);
    print_statement(tabs + 1, if_statement->statement);
}

void print_for_statement(int tabs, for_statement_t* for_statement)
{
    if (!for_statement) return;
    print_tabs(tabs);
    fprintf(stderr, "FOR STATEMENT\n");
    print_statement(tabs + 1, for_statement->initialize);
    print_expression(tabs + 1, for_statement->condition);
    print_statement(tabs + 1, for_statement->loop);
}