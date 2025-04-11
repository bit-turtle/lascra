# File Structure (`.scra` files)
The code files for lascra are organized into 3 different layers
1. Top Level Statements which structure the sprite as a whole `TOP.md`
  - `define` variables, lists, and broadcasts
  - `declare` sprite information
  - Run code `when` and event happens
2. Code Statements which describe a code block to be run inside of a `when` statement `CODE.md`
3. Parameter Statements which are passed to code statements `PARAM.md`
## Example
```
(when flag
    (say "Hi!")
)
```
`when` is a top level statement. `flag` is the event. `say` is a code statement. `"Hi!"` is a parameter statement.
