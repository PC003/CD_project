#include "checker.h"
#include <iostream>

namespace nlopt {

bool SemanticChecker::check(std::shared_ptr<OptimizationRuleNode> rule) {
    if (!rule) {
        error_message = "Rule is null.";
        return false;
    }

    // Example checks:
    // "For an addition with two constant operands, replace the operation with their product." -> Invalid
    
    if (rule->condition && rule->condition->type == ConditionType::WITH_TWO_CONSTANTS) {
        if (rule->replacement) {
            auto op_node = dynamic_cast<OperationNode*>(rule->replacement.get());
            if (op_node) {
                if (rule->match_op == OperationType::ADDITION && op_node->op != OperationType::ADDITION) {
                    error_message = "SEMANTIC ERROR: Addition cannot use something other than sum as its replacement for two constants.";
                    return false;
                }
                if (rule->match_op == OperationType::MULTIPLICATION && op_node->op != OperationType::MULTIPLICATION) {
                    error_message = "SEMANTIC ERROR: Multiplication cannot use something other than product as its replacement for two constants.";
                    return false;
                }
            }
        }
    }

    // Safety checks:
    if (rule->match_op == OperationType::DIVISION && rule->condition) {
        if (rule->condition->type == ConditionType::WITH_OPERAND_CONSTANT && rule->condition->constant_value == 0) {
            error_message = "UNSAFE RULE: Division identity may be invalid because division by zero is possible.";
            return false;
        }
    }

    return true;
}

} // namespace nlopt
