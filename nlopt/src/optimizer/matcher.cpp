#include "matcher.h"

namespace nlopt {

MatchResult Matcher::match(const OptimizationRule& rule, std::shared_ptr<DemoIRNode> node) {
    MatchResult result;
    result.matched = false;

    auto op_node = std::dynamic_pointer_cast<DemoOperation>(node);
    if (!op_node) return result;

    if (op_node->op != rule.match_operation) return result;

    result.first_operand = op_node->left;
    result.second_operand = op_node->right;

    auto left_const = std::dynamic_pointer_cast<DemoConstant>(op_node->left);
    auto right_const = std::dynamic_pointer_cast<DemoConstant>(op_node->right);

    if (rule.has_two_constants) {
        if (left_const && right_const) {
            result.matched = true;
            result.const1 = left_const->value;
            result.const2 = right_const->value;
        }
        return result;
    }

    if (rule.has_constant_operand) {
        if (left_const && left_const->value == rule.constant_value) {
            result.matched = true;
            result.other_operand = op_node->right;
        } else if (right_const && right_const->value == rule.constant_value) {
            result.matched = true;
            result.other_operand = op_node->left;
        }
        return result;
    }

    // Unconstrained match
    result.matched = true;
    return result;
}

} // namespace nlopt
