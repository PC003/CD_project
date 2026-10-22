#include "rewriter.h"
#include <iostream>

namespace nlopt {

std::shared_ptr<DemoIRNode> Rewriter::rewrite(std::shared_ptr<DemoIRNode> node, const std::vector<OptimizationRule>& rules) {
    auto current = node;
    bool changed = true;
    
    while (changed) {
        changed = false;
        
        // Post-order traversal / bottom-up rewrite
        if (auto op_node = std::dynamic_pointer_cast<DemoOperation>(current)) {
            auto new_left = rewrite(op_node->left, rules);
            auto new_right = rewrite(op_node->right, rules);
            
            if (new_left != op_node->left || new_right != op_node->right) {
                op_node->left = new_left;
                op_node->right = new_right;
                changed = true;
            }
        }

        auto rewritten = apply_rules(current, rules);
        if (rewritten != current) {
            current = rewritten;
            changed = true;
        }
    }
    
    return current;
}

std::shared_ptr<DemoIRNode> Rewriter::apply_rules(std::shared_ptr<DemoIRNode> node, const std::vector<OptimizationRule>& rules) {
    for (const auto& rule : rules) {
        auto match_result = matcher.match(rule, node);
        if (match_result.matched) {
            std::cout << "MATCH: rule applied\n"; // Debug info
            if (rule.replacement_type == OptimizationRule::ReplaceTarget::OTHER_OPERAND) {
                return match_result.other_operand;
            } else if (rule.replacement_type == OptimizationRule::ReplaceTarget::FIRST_OPERAND) {
                return match_result.first_operand;
            } else if (rule.replacement_type == OptimizationRule::ReplaceTarget::SECOND_OPERAND) {
                return match_result.second_operand;
            } else if (rule.replacement_type == OptimizationRule::ReplaceTarget::CONSTANT) {
                return std::make_shared<DemoConstant>(rule.replacement_constant);
            } else if (rule.replacement_type == OptimizationRule::ReplaceTarget::EVALUATED_SUM) {
                return std::make_shared<DemoConstant>(match_result.const1 + match_result.const2);
            } else if (rule.replacement_type == OptimizationRule::ReplaceTarget::EVALUATED_PRODUCT) {
                return std::make_shared<DemoConstant>(match_result.const1 * match_result.const2);
            }
        }
    }
    return node;
}

} // namespace nlopt
