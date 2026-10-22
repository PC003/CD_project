#ifndef NLOPT_BACKEND_H
#define NLOPT_BACKEND_H

#include "rule_ir/optimization_rule.h"

namespace nlopt {

class Backend {
public:
    virtual ~Backend() = default;
    virtual void register_rule(const OptimizationRule& rule) = 0;
    virtual void run_demo() = 0;
};

class DemoBackend : public Backend {
public:
    void register_rule(const OptimizationRule& rule) override;
    void run_demo() override;

private:
    std::vector<OptimizationRule> rules;
};

} // namespace nlopt

#endif // NLOPT_BACKEND_H
