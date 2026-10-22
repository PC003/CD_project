#include "rule.h"
#include <iostream>

namespace nlopt {

static void print_indent(std::ostream& os, int indent) {
    for (int i = 0; i < indent; ++i) os << "  ";
}

static const char* op_type_to_string(OperationType op) {
    switch(op) {
        case OperationType::ADDITION: return "ADDITION";
        case OperationType::SUBTRACTION: return "SUBTRACTION";
        case OperationType::MULTIPLICATION: return "MULTIPLICATION";
        case OperationType::DIVISION: return "DIVISION";
        case OperationType::CONSTANT: return "CONSTANT";
        case OperationType::BRANCH: return "BRANCH";
        default: return "UNKNOWN";
    }
}

static const char* operand_type_to_string(OperandType op) {
    switch(op) {
        case OperandType::FIRST: return "FIRST_OPERAND";
        case OperandType::SECOND: return "SECOND_OPERAND";
        case OperandType::OTHER: return "OTHER_OPERAND";
        default: return "UNKNOWN_OPERAND";
    }
}

void OperandNode::print(std::ostream& os, int indent) const {
    print_indent(os, indent);
    os << "Operand: " << operand_type_to_string(op_type) << "\n";
}

void ConstantNode::print(std::ostream& os, int indent) const {
    print_indent(os, indent);
    os << "Constant: " << value << "\n";
}

void OperationNode::print(std::ostream& os, int indent) const {
    print_indent(os, indent);
    os << "Operation: " << op_type_to_string(op) << "\n";
    for (auto& child : children) {
        child->print(os, indent + 1);
    }
}

void ConditionNode::print(std::ostream& os, int indent) const {
    print_indent(os, indent);
    if (type == ConditionType::WITH_OPERAND_CONSTANT) {
        os << "Condition: ONE_OPERAND == " << constant_value << "\n";
    } else if (type == ConditionType::WITH_TWO_CONSTANTS) {
        os << "Condition: TWO_CONSTANTS\n";
    } else {
        os << "Condition: NONE\n";
    }
}

void OptimizationRuleNode::print(std::ostream& os, int indent) const {
    print_indent(os, indent);
    os << "Rule:\n";
    print_indent(os, indent + 1);
    os << "Match Operation: " << op_type_to_string(match_op) << "\n";
    if (condition) {
        condition->print(os, indent + 1);
    }
    if (replacement) {
        print_indent(os, indent + 1);
        os << "Replacement:\n";
        replacement->print(os, indent + 2);
    }
}

} // namespace nlopt
