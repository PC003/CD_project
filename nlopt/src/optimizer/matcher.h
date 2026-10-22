#ifndef NLOPT_MATCHER_H
#define NLOPT_MATCHER_H

#include "backend/demo_ir.h"
#include "rule_ir/optimization_rule.h"

namespace nlopt {

struct MatchResult {
    bool matched;
    std::shared_ptr<DemoIRNode> matched_node;
    std::shared_ptr<DemoIRNode> other_operand; // the one that is NOT the constant in a constant match
    std::shared_ptr<DemoIRNode> first_operand;
    std::shared_ptr<DemoIRNode> second_operand;
    int const1;
    int const2;
};

class Matcher {
public:
    MatchResult match(const OptimizationRule& rule, std::shared_ptr<DemoIRNode> node);
};

} // namespace nlopt

#endif // NLOPT_MATCHER_H
