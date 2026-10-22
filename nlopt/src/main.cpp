#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ast/rule.h"
#include "semantic/checker.h"
#include "rule_ir/optimization_rule.h"
#include "backend/backend.h"

extern int yyparse();
extern FILE* yyin;
extern int yylineno;
extern std::shared_ptr<nlopt::OptimizationRuleNode> root_rule;

void print_header() {
    std::cout << "========================================\n";
    std::cout << "             NLOpt Compiler\n";
    std::cout << "========================================\n\n";
}

int main(int argc, char** argv) {
    print_header();

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rule.nlopt>\n";
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }

    yyin = file;

    std::cout << "[1] Lexical & Syntax Analysis\n";
    if (yyparse() == 0 && root_rule) {
        std::cout << "    ✓ Grammar accepted\n\n";
    } else {
        std::cerr << "    ✗ Parsing failed.\n";
        fclose(file);
        return 1;
    }
    fclose(file);

    std::cout << "[2] AST\n";
    root_rule->print(std::cout, 1);
    std::cout << "\n";

    std::cout << "[3] Semantic Analysis\n";
    nlopt::SemanticChecker checker;
    if (checker.check(root_rule)) {
        std::cout << "    ✓ Rule is valid\n";
        std::cout << "    ✓ Safety checks passed\n\n";
    } else {
        std::cerr << "    ✗ Semantic Error: " << checker.get_error() << "\n";
        return 1;
    }

    std::cout << "[4] Optimization Rule IR\n";
    nlopt::OptimizationRule rule_ir = nlopt::generate_rule_ir(root_rule);
    rule_ir.print(std::cout);
    std::cout << "\n";

    std::cout << "[5] Backend\n";
    nlopt::DemoBackend backend;
    backend.register_rule(rule_ir);
    std::cout << "    ✓ Rule generated\n";

    backend.run_demo();

    std::cout << "Status: SUCCESS\n";
    std::cout << "========================================\n";

    return 0;
}
