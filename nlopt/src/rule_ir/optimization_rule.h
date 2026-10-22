#ifndef NLOPT_RULE_IR_H
#define NLOPT_RULE_IR_H

#include "ast/rule.h"
#include <string>

namespace nlopt {

enum class SafetyLevel {
    SAFE,
    UNSAFE,
    REQUIRES_DATAFLOW
};

struct OptimizationRule {
    std::string name;
    OperationType match_operation;
    
    // Constraints
    bool has_constant_operand;
    int constant_value;
    bool has_two_constants;

    // Replacement pattern
    enum class ReplaceTarget {
        OTHER_OPERAND,
        FIRST_OPERAND,
        SECOND_OPERAND,
        CONSTANT,
        EVALUATED_SUM,
        EVALUATED_PRODUCT
    };

    ReplaceTarget replacement_type;
    int replacement_constant;

    SafetyLevel safety;

    void print(std::ostream& os) const;
};

OptimizationRule generate_rule_ir(std::shared_ptr<OptimizationRuleNode> ast_rule);

} // namespace nlopt

#endif // NLOPT_RULE_IR_H
