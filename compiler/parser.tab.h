/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FUNCTION = 258,                /* FUNCTION  */
    CHAR = 259,                    /* CHAR  */
    SHORT = 260,                   /* SHORT  */
    INT = 261,                     /* INT  */
    LONG = 262,                    /* LONG  */
    STATIC = 263,                  /* STATIC  */
    MUT = 264,                     /* MUT  */
    IMMUT = 265,                   /* IMMUT  */
    RETURN = 266,                  /* RETURN  */
    TYPE = 267,                    /* TYPE  */
    STRUCT = 268,                  /* STRUCT  */
    ENUM = 269,                    /* ENUM  */
    UNION = 270,                   /* UNION  */
    IF = 271,                      /* IF  */
    FOR = 272,                     /* FOR  */
    EQ = 273,                      /* EQ  */
    NEQ = 274,                     /* NEQ  */
    ARROW = 275,                   /* ARROW  */
    INTEGER_LITERAL = 276,         /* INTEGER_LITERAL  */
    IDENTIFIER = 277               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "src/parser.y"

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

#line 108 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
