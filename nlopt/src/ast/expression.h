#ifndef NLOPT_AST_EXPRESSION_H
#define NLOPT_AST_EXPRESSION_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace nlopt {

enum class OperationType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    CONSTANT,
    BRANCH,
    UNKNOWN
};

enum class OperandType {
    FIRST,
    SECOND,
    OTHER,
    UNKNOWN
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(std::ostream& os, int indent) const = 0;
};

class OperandNode : public ASTNode {
public:
    OperandType op_type;
    explicit OperandNode(OperandType t) : op_type(t) {}
    void print(std::ostream& os, int indent) const override;
};

class ConstantNode : public ASTNode {
public:
    int value;
    explicit ConstantNode(int v) : value(v) {}
    void print(std::ostream& os, int indent) const override;
};

class ExpressionNode : public ASTNode {
public:
    virtual ~ExpressionNode() = default;
};

class OperationNode : public ExpressionNode {
public:
    OperationType op;
    std::vector<std::shared_ptr<ASTNode>> children;
    explicit OperationNode(OperationType o) : op(o) {}
    void add_child(std::shared_ptr<ASTNode> child) {
        children.push_back(child);
    }
    void print(std::ostream& os, int indent) const override;
};

} // namespace nlopt

#endif // NLOPT_AST_EXPRESSION_H
