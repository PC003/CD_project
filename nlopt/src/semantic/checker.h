#ifndef NLOPT_SEMANTIC_CHECKER_H
#define NLOPT_SEMANTIC_CHECKER_H

#include "ast/rule.h"
#include <string>

namespace nlopt {

class SemanticChecker {
public:
    bool check(std::shared_ptr<OptimizationRuleNode> rule);
    std::string get_error() const { return error_message; }
private:
    std::string error_message;
};

} // namespace nlopt

#endif // NLOPT_SEMANTIC_CHECKER_H
