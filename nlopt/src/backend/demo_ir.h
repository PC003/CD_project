#ifndef NLOPT_DEMO_IR_H
#define NLOPT_DEMO_IR_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "ast/expression.h" // For OperationType

namespace nlopt {

class DemoIRNode {
public:
    virtual ~DemoIRNode() = default;
    virtual void print(std::ostream& os) const = 0;
    virtual std::shared_ptr<DemoIRNode> clone() const = 0;
};

class DemoConstant : public DemoIRNode {
public:
    int value;
    explicit DemoConstant(int v) : value(v) {}
    void print(std::ostream& os) const override { os << value; }
    std::shared_ptr<DemoIRNode> clone() const override { return std::make_shared<DemoConstant>(value); }
};

class DemoVariable : public DemoIRNode {
public:
    std::string name;
    explicit DemoVariable(const std::string& n) : name(n) {}
    void print(std::ostream& os) const override { os << name; }
    std::shared_ptr<DemoIRNode> clone() const override { return std::make_shared<DemoVariable>(name); }
};

class DemoOperation : public DemoIRNode {
public:
    OperationType op;
    std::shared_ptr<DemoIRNode> left;
    std::shared_ptr<DemoIRNode> right;
    
    DemoOperation(OperationType o, std::shared_ptr<DemoIRNode> l, std::shared_ptr<DemoIRNode> r) 
        : op(o), left(l), right(r) {}
        
    void print(std::ostream& os) const override {
        switch(op) {
            case OperationType::ADDITION: os << "add("; break;
            case OperationType::SUBTRACTION: os << "sub("; break;
            case OperationType::MULTIPLICATION: os << "mul("; break;
            case OperationType::DIVISION: os << "div("; break;
            default: os << "op("; break;
        }
        left->print(os);
        os << ", ";
        right->print(os);
        os << ")";
    }
    std::shared_ptr<DemoIRNode> clone() const override { 
        return std::make_shared<DemoOperation>(op, left->clone(), right->clone()); 
    }
};

} // namespace nlopt

#endif // NLOPT_DEMO_IR_H
