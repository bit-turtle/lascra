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
* (repeat *positiveInteger* *code...*)
* (forever *code...*)
### Data
* (set *variableName* *string*)
* (change *variableName* *number*)
