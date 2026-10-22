#ifndef NLOPT_AST_RULE_H
#define NLOPT_AST_RULE_H

#include "expression.h"

namespace nlopt {

enum class ConditionType {
    WITH_OPERAND_CONSTANT,
    WITH_TWO_CONSTANTS,
    NONE
};

class ConditionNode : public ASTNode {
public:
    ConditionType type;
    OperandType operand_target;
    int constant_value;

    ConditionNode() : type(ConditionType::NONE), operand_target(OperandType::UNKNOWN), constant_value(0) {}
    
    // For: with zero (second operand = 0, implicitly, or we can just say one of the operands)
    // Actually the grammar says "with zero", which implies one operand is zero. 
    // Or "with two constant operands".
    
    void print(std::ostream& os, int indent) const override;
};

class OptimizationRuleNode : public ASTNode {
public:
    OperationType match_op;
    std::shared_ptr<ConditionNode> condition;
    std::shared_ptr<ASTNode> replacement;

    OptimizationRuleNode() : match_op(OperationType::UNKNOWN) {}
    void print(std::ostream& os, int indent) const override;
};

} // namespace nlopt

#endif // NLOPT_AST_RULE_H
