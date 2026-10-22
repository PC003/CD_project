#include "optimization_rule.h"
#include <iostream>

namespace nlopt {

void OptimizationRule::print(std::ostream& os) const {
    os << "OptimizationRule IR:\n";
    os << "  Name: " << name << "\n";
    os << "  Safety: " << (safety == SafetyLevel::SAFE ? "SAFE" : "UNSAFE") << "\n";
}

OptimizationRule generate_rule_ir(std::shared_ptr<OptimizationRuleNode> ast_rule) {
    OptimizationRule rule;
    rule.name = "GeneratedRule";
    rule.match_operation = ast_rule->match_op;
    rule.has_constant_operand = false;
    rule.has_two_constants = false;
    rule.safety = SafetyLevel::SAFE;
    
    if (ast_rule->condition) {
        if (ast_rule->condition->type == ConditionType::WITH_OPERAND_CONSTANT) {
            rule.has_constant_operand = true;
            rule.constant_value = ast_rule->condition->constant_value;
        } else if (ast_rule->condition->type == ConditionType::WITH_TWO_CONSTANTS) {
            rule.has_two_constants = true;
        }
    }

    if (ast_rule->replacement) {
        if (auto op_node = dynamic_cast<OperandNode*>(ast_rule->replacement.get())) {
            if (op_node->op_type == OperandType::OTHER) rule.replacement_type = OptimizationRule::ReplaceTarget::OTHER_OPERAND;
            else if (op_node->op_type == OperandType::FIRST) rule.replacement_type = OptimizationRule::ReplaceTarget::FIRST_OPERAND;
            else if (op_node->op_type == OperandType::SECOND) rule.replacement_type = OptimizationRule::ReplaceTarget::SECOND_OPERAND;
        } else if (auto const_node = dynamic_cast<ConstantNode*>(ast_rule->replacement.get())) {
            rule.replacement_type = OptimizationRule::ReplaceTarget::CONSTANT;
            rule.replacement_constant = const_node->value;
        } else if (auto operation_node = dynamic_cast<OperationNode*>(ast_rule->replacement.get())) {
            if (operation_node->op == OperationType::ADDITION) {
                rule.replacement_type = OptimizationRule::ReplaceTarget::EVALUATED_SUM;
            } else if (operation_node->op == OperationType::MULTIPLICATION) {
                rule.replacement_type = OptimizationRule::ReplaceTarget::EVALUATED_PRODUCT;
            }
        }
    }

    if (rule.match_operation == OperationType::MULTIPLICATION && rule.has_constant_operand && rule.constant_value == 0) {
        // x * 0 is only safe without side effects, but for MVP we assume pure expressions or mark it safe if handled by matcher.
        // Actually, requirement 11: "account for side effects... For MVP, we can mark it as safe but matcher must verify purity"
        rule.safety = SafetyLevel::SAFE; 
    }

    return rule;
}

} // namespace nlopt
