# NLOpt Grammar

The NLOpt parser uses a restricted Context-Free Grammar (CFG) designed specifically for deterministic parsing without ambiguity.

```ebnf
RULE        -> "For" PATTERN "replace" TARGET "with" REPLACEMENT "."
             | "For" PATTERN "," "replace" TARGET "with" REPLACEMENT "."

PATTERN     -> ("an" | "a") OPERATION CONDITION
             | OPERATION CONDITION

CONDITION   -> "with" OPERANDS
             | "with" "zero"
             | "with" "one"
             | "with" "two" "constant" "operands"
             | /* empty */

TARGET      -> "the" "operation"
             | "the" "expression"

REPLACEMENT -> EXPRESSION
             | "their" "sum"
             | "their" "product"

EXPRESSION  -> OPERAND
             | CONSTANT

OPERATION   -> "addition"
             | "subtraction"
             | "multiplication"
             | "division"
             | "constant"
             | "branch"

OPERAND     -> "the" "first" "operand"
             | "the" "second" "operand"
             | "the" "other" "operand"

CONSTANT    -> [0-9]+
```
