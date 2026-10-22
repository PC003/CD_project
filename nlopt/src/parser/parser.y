%{
#include <iostream>
#include <memory>
#include "ast/rule.h"

extern int yylex();
extern int yylineno;
void yyerror(const char* s);

std::shared_ptr<nlopt::OptimizationRuleNode> root_rule;

%}

%code requires {
#include "ast/rule.h"
#include <memory>
}

%union {
    int num;
    nlopt::OperationType op_type;
    nlopt::ConditionNode* cond;
    nlopt::ASTNode* expr;
    nlopt::OptimizationRuleNode* rule;
}

%token FOR AN A WITH WHERE REPLACE THE OPERATION EXPRESSION FIRST SECOND OTHER OPERAND OPERANDS THEIR SUM PRODUCT ZERO ONE TWO COMMA DOT
%token <num> NUMBER
%token ADDITION SUBTRACTION MULTIPLICATION DIVISION CONSTANT BRANCH

%type <op_type> operation
%type <cond> condition
%type <expr> replacement expression target
%type <rule> rule pattern

%%

start:
    rule { root_rule = std::shared_ptr<nlopt::OptimizationRuleNode>($1); }
    ;

rule:
    FOR pattern COMMA REPLACE target WITH replacement DOT
    {
        $2->replacement = std::shared_ptr<nlopt::ASTNode>($7);
        $$ = $2;
    }
    | FOR pattern REPLACE target WITH replacement DOT
    {
        $2->replacement = std::shared_ptr<nlopt::ASTNode>($6);
        $$ = $2;
    }
    ;

pattern:
    an_or_a operation condition
    {
        $$ = new nlopt::OptimizationRuleNode();
        $$->match_op = $2;
        $$->condition = std::shared_ptr<nlopt::ConditionNode>($3);
    }
    | operation condition
    {
        $$ = new nlopt::OptimizationRuleNode();
        $$->match_op = $1;
        $$->condition = std::shared_ptr<nlopt::ConditionNode>($2);
    }
    ;

an_or_a:
    AN
    | A
    ;

operation:
    ADDITION { $$ = nlopt::OperationType::ADDITION; }
    | SUBTRACTION { $$ = nlopt::OperationType::SUBTRACTION; }
    | MULTIPLICATION { $$ = nlopt::OperationType::MULTIPLICATION; }
    | DIVISION { $$ = nlopt::OperationType::DIVISION; }
    | CONSTANT { $$ = nlopt::OperationType::CONSTANT; }
    | BRANCH { $$ = nlopt::OperationType::BRANCH; }
    ;

condition:
    WITH ZERO
    {
        $$ = new nlopt::ConditionNode();
        $$->type = nlopt::ConditionType::WITH_OPERAND_CONSTANT;
        $$->constant_value = 0;
    }
    | WITH ONE
    {
        $$ = new nlopt::ConditionNode();
        $$->type = nlopt::ConditionType::WITH_OPERAND_CONSTANT;
        $$->constant_value = 1;
    }
    | WITH TWO CONSTANT OPERANDS
    {
        $$ = new nlopt::ConditionNode();
        $$->type = nlopt::ConditionType::WITH_TWO_CONSTANTS;
    }
    | /* empty */
    {
        $$ = new nlopt::ConditionNode();
        $$->type = nlopt::ConditionType::NONE;
    }
    ;

target:
    THE OPERATION { $$ = nullptr; /* Implicitly the matched operation */ }
    | THE EXPRESSION { $$ = nullptr; }
    ;

replacement:
    expression { $$ = $1; }
    | THEIR SUM
    {
        auto add = new nlopt::OperationNode(nlopt::OperationType::ADDITION);
        add->add_child(std::make_shared<nlopt::OperandNode>(nlopt::OperandType::FIRST));
        add->add_child(std::make_shared<nlopt::OperandNode>(nlopt::OperandType::SECOND));
        $$ = add;
    }
    | THEIR PRODUCT
    {
        auto mul = new nlopt::OperationNode(nlopt::OperationType::MULTIPLICATION);
        mul->add_child(std::make_shared<nlopt::OperandNode>(nlopt::OperandType::FIRST));
        mul->add_child(std::make_shared<nlopt::OperandNode>(nlopt::OperandType::SECOND));
        $$ = mul;
    }
    ;

expression:
    THE OTHER OPERAND
    {
        $$ = new nlopt::OperandNode(nlopt::OperandType::OTHER);
    }
    | THE FIRST OPERAND
    {
        $$ = new nlopt::OperandNode(nlopt::OperandType::FIRST);
    }
    | THE SECOND OPERAND
    {
        $$ = new nlopt::OperandNode(nlopt::OperandType::SECOND);
    }
    | NUMBER
    {
        $$ = new nlopt::ConstantNode($1);
    }
    ;

%%

void yyerror(const char* s) {
    std::cerr << "Syntax Error: " << s << " at line " << yylineno << "\n";
}
