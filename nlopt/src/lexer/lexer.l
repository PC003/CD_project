%{
#include <iostream>
#include "ast/rule.h"
#include "parser.tab.hpp"

extern int yylineno;
%}

%option noyywrap
%option yylineno

%%
[Ff]or                  { return FOR; }
[Aa]n                   { return AN; }
[Aa]                    { return A; }
[Aa]ddition             { return ADDITION; }
[Ss]ubtraction          { return SUBTRACTION; }
[Mm]ultiplication       { return MULTIPLICATION; }
[Dd]ivision             { return DIVISION; }
[Cc]onstant             { return CONSTANT; }
[Bb]ranch               { return BRANCH; }
[Ww]ith                 { return WITH; }
[Ww]here                { return WHERE; }
[Rr]eplace              { return REPLACE; }
[Tt]he                  { return THE; }
[Oo]peration            { return OPERATION; }
[Ee]xpression           { return EXPRESSION; }
[Ff]irst                { return FIRST; }
[Ss]econd               { return SECOND; }
[Oo]ther                { return OTHER; }
[Oo]perand              { return OPERAND; }
[Oo]perands             { return OPERANDS; }
[Tt]heir                { return THEIR; }
[Ss]um                  { return SUM; }
[Pp]roduct              { return PRODUCT; }
[Zz]ero                 { return ZERO; }
[Oo]ne                  { return ONE; }
[Tt]wo                  { return TWO; }
","                     { return COMMA; }
"."                     { return DOT; }
[0-9]+                  { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n\r]+              { /* Ignore whitespace */ }
.                       { std::cerr << "Lexical Error: Unknown character '" << yytext[0] << "'\n"; }

%%
