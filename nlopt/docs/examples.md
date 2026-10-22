# NLOpt Examples

Here are some valid examples of NLOpt optimization rules:

## 1. Addition with Zero
```nlopt
For an addition with zero, replace the operation with the other operand.
```
**Effect**: Transforms `add(x, 0)` into `x`.

## 2. Multiplication with One
```nlopt
For a multiplication with one, replace the operation with the other operand.
```
**Effect**: Transforms `mul(x, 1)` into `x`.

## 3. Multiplication with Zero
```nlopt
For a multiplication with zero, replace the operation with 0.
```
**Effect**: Transforms `mul(x, 0)` into `0` (assuming purity is enforced by the semantic checker).

## 4. Constant Folding (Addition)
```nlopt
For an addition with two constant operands, replace the operation with their sum.
```
**Effect**: Transforms `add(3, 4)` into `7`.

## 5. Constant Folding (Multiplication)
```nlopt
For a multiplication with two constant operands, replace the operation with their product.
```
**Effect**: Transforms `mul(3, 4)` into `12`.
