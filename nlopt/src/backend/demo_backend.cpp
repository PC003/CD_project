#include "backend.h"
#include "optimizer/rewriter.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

namespace nlopt {

class ExprParser {
    const std::string& input;
    size_t pos = 0;

    void skip_whitespace() {
        while (pos < input.length() && std::isspace(input[pos])) pos++;
    }

    std::shared_ptr<DemoIRNode> parse_primary() {
        skip_whitespace();
        if (pos >= input.length()) throw std::runtime_error("Unexpected end of input");

        if (input[pos] == '(') {
            pos++;
            auto node = parse_expr();
            skip_whitespace();
            if (pos < input.length() && input[pos] == ')') pos++;
            else throw std::runtime_error("Expected ')'");
            return node;
        }

        if (std::isdigit(input[pos])) {
            int val = 0;
            while (pos < input.length() && std::isdigit(input[pos])) {
                val = val * 10 + (input[pos] - '0');
                pos++;
            }
            return std::make_shared<DemoConstant>(val);
        }

        if (std::isalpha(input[pos]) || input[pos] == '_') {
            std::string name;
            while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
                name += input[pos];
                pos++;
            }
            return std::make_shared<DemoVariable>(name);
        }

        throw std::runtime_error(std::string("Unexpected character in expression: ") + input[pos]);
    }

    std::shared_ptr<DemoIRNode> parse_term() {
        auto node = parse_primary();
        while (true) {
            skip_whitespace();
            if (pos < input.length() && (input[pos] == '*' || input[pos] == '/')) {
                char op = input[pos++];
                auto right = parse_primary();
                OperationType type = (op == '*') ? OperationType::MULTIPLICATION : OperationType::DIVISION;
                node = std::make_shared<DemoOperation>(type, node, right);
            } else {
                break;
            }
        }
        return node;
    }

    std::shared_ptr<DemoIRNode> parse_expr() {
        auto node = parse_term();
        while (true) {
            skip_whitespace();
            if (pos < input.length() && (input[pos] == '+' || input[pos] == '-')) {
                char op = input[pos++];
                auto right = parse_term();
                OperationType type = (op == '+') ? OperationType::ADDITION : OperationType::SUBTRACTION;
                node = std::make_shared<DemoOperation>(type, node, right);
            } else {
                break;
            }
        }
        return node;
    }

public:
    ExprParser(const std::string& str) : input(str) {}
    std::shared_ptr<DemoIRNode> parse() {
        auto node = parse_expr();
        skip_whitespace();
        if (pos < input.length()) throw std::runtime_error("Unexpected trailing characters");
        return node;
    }
};

void DemoBackend::register_rule(const OptimizationRule& rule) {
    rules.push_back(rule);
}

void DemoBackend::run_demo() {
    std::cout << "\n=== Running Interactive Demo Backend ===\n";
    std::cout << "Type an expression (e.g. 'x + 0' or '3 + 4') to optimize it.\n";
    std::cout << "Type 'exit' or 'quit' to exit.\n\n";
    
    Rewriter rewriter;
    std::string line;

    while (true) {
        std::cout << "nlopt> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line == "exit" || line == "quit") {
            break;
        }
        if (line.empty()) {
            continue;
        }

        try {
            ExprParser parser(line);
            auto node = parser.parse();

            std::cout << "Before optimization:\n    ";
            node->print(std::cout);
            std::cout << "\n";

            auto optimized = rewriter.rewrite(node, rules);

            std::cout << "After optimization:\n    ";
            optimized->print(std::cout);
            std::cout << "\n\n";

        } catch (const std::exception& e) {
            std::cout << "Parse Error: " << e.what() << "\n\n";
        }
    }
}

} // namespace nlopt
