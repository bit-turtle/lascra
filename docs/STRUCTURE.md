# File Structure (`.scra` files)
The code files for lascra are organized into 3 different layers
1. [Top Level Statements](TOP.md) which structure the sprite as a whole
2. [Code Statements](CODE.md) which describe block of code inside of a `when` or `procedure`/`function` top level statement
3. [Parameter Statements](PARAM.md) which are passed to code statements
## Example
```
(when flag
    (say "Hi!")
)
```
`when` is a top level statement. `flag` is the event. `say` is a code statement. `"Hi!"` is a parameter statement.
