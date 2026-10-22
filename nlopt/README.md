# NLOpt — Natural-Language Optimization

NLOpt is a controlled-natural-language DSL for specifying compiler optimizations. It allows users to write restricted English-like optimization rules which are deterministically parsed, semantically validated, and converted into an Optimization Rule IR. This IR is then used by a rewrite engine to perform optimizations on an abstract syntax tree / internal representation.

## Compiler Pipeline

1. **Lexical Analysis**: Flex lexer tokenizes the controlled English input.
2. **Syntax Analysis**: Bison parser validates the grammar and constructs an AST.
3. **AST**: The syntax tree represents the optimization rule.
4. **Semantic Analysis**: Checks if the rule is logically valid and safe.
5. **Optimization Rule IR**: Lowers the AST into a standalone Intermediate Representation.
6. **Backend / Rewrite Engine**: Uses the Rule IR to pattern match and optimize target expressions.

## Architecture
See [Architecture Documentation](docs/architecture.md)

## Grammar
See [Grammar Documentation](docs/grammar.md)

## Examples
See [Examples Documentation](docs/examples.md)

## Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Running NLOpt

```bash
./build/nlopt examples/add_zero.nlopt
```
