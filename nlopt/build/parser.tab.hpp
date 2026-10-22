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

#ifndef YY_YY_USERS_PIYUSHAJITCHAVAN_DESKTOP_CD_PROJECT_NLOPT_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_USERS_PIYUSHAJITCHAVAN_DESKTOP_CD_PROJECT_NLOPT_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "src/parser/parser.y"

#include "ast/rule.h"
#include <memory>

#line 54 "/Users/piyushajitchavan/Desktop/CD_project/nlopt/build/parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FOR = 258,                     /* FOR  */
    AN = 259,                      /* AN  */
    A = 260,                       /* A  */
    WITH = 261,                    /* WITH  */
    WHERE = 262,                   /* WHERE  */
    REPLACE = 263,                 /* REPLACE  */
    THE = 264,                     /* THE  */
    OPERATION = 265,               /* OPERATION  */
    EXPRESSION = 266,              /* EXPRESSION  */
    FIRST = 267,                   /* FIRST  */
    SECOND = 268,                  /* SECOND  */
    OTHER = 269,                   /* OTHER  */
    OPERAND = 270,                 /* OPERAND  */
    OPERANDS = 271,                /* OPERANDS  */
    THEIR = 272,                   /* THEIR  */
    SUM = 273,                     /* SUM  */
    PRODUCT = 274,                 /* PRODUCT  */
    ZERO = 275,                    /* ZERO  */
    ONE = 276,                     /* ONE  */
    TWO = 277,                     /* TWO  */
    COMMA = 278,                   /* COMMA  */
    DOT = 279,                     /* DOT  */
    NUMBER = 280,                  /* NUMBER  */
    ADDITION = 281,                /* ADDITION  */
    SUBTRACTION = 282,             /* SUBTRACTION  */
    MULTIPLICATION = 283,          /* MULTIPLICATION  */
    DIVISION = 284,                /* DIVISION  */
    CONSTANT = 285,                /* CONSTANT  */
    BRANCH = 286                   /* BRANCH  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "src/parser/parser.y"

    int num;
    nlopt::OperationType op_type;
    nlopt::ConditionNode* cond;
    nlopt::ASTNode* expr;
    nlopt::OptimizationRuleNode* rule;

#line 110 "/Users/piyushajitchavan/Desktop/CD_project/nlopt/build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_USERS_PIYUSHAJITCHAVAN_DESKTOP_CD_PROJECT_NLOPT_BUILD_PARSER_TAB_HPP_INCLUDED  */
