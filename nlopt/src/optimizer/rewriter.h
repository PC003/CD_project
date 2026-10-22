#ifndef NLOPT_REWRITER_H
#define NLOPT_REWRITER_H

#include "matcher.h"
#include <vector>

namespace nlopt {

class Rewriter {
public:
    std::shared_ptr<DemoIRNode> rewrite(std::shared_ptr<DemoIRNode> node, const std::vector<OptimizationRule>& rules);

private:
    std::shared_ptr<DemoIRNode> apply_rules(std::shared_ptr<DemoIRNode> node, const std::vector<OptimizationRule>& rules);
    Matcher matcher;
};

} // namespace nlopt

#endif // NLOPT_REWRITER_H
