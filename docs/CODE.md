# Code Statements
Code statements describe the code blocks
## Example
```
(say "Hi!")
```
Here `say` is a block which accepts a string parameter as an input `PARAM.md`
## List of blocks
### Motion
* (move *number*)
### Looks
* (say *string*)
### Events
* (broadcast *broadcastName*)
* (waitbroadcast *broadcastName*)
### Control
* (wait *seconds*)
* (wait_until *condition*)
* Conditionals:
  - (if *condition* *code...*)
  - (elif *condition* *code...*)
    - Must occur after an if or elif
  - (else *code...*)
    - Must occur after an if or elif
* (repeat *positiveInteger* *code...*)
* (repeat_until *condition* *code...*)
* (forever *code...*)
* (stop *what*)
  - Same as scratch, example: `(stop all)`
* (clone *spriteName*)
  - Myself is: "_myself_"
  - `(clone _myself_)`
* (delete_clone)
  - Can also be written without parentheses
### Data
* (set *variableName* *string*)
* (change *variableName* *number*)
* (show_variable *variableName*)
* (hide_variable *variableName*)
