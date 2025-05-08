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
* (set_x *number*)
* (set_y *number*)
* (change_x *number*)
* (change_y *number*)
* (goto *spriteName*)
  - `_mouse_` Mouse Pointer
  - `_random_` Random Position
* (glide *seconds* *spriteName*)
  - `_mouse_` Mouse Pointer
  - `_random_` Random Position
* (goto_xy *x* *y*)
* (glide_xy *seconds* *x* *y*)
* (turn_right *number*)
* (turn_left *number*)
* (point_direction *angle*)
* (point_towards *spriteName*)
  - `_mouse_` Mouse Pointer
* (set_rotation_style *rotationStyle*)
  - `all around`
  - `left-right`
  - `don't rotate`
* (if_on_edge_bounce)
### Looks
* (say *string*)
* (say_for *string* *seconds*)
* (think *string*)
* (think_for *string* *seconds*)
* (costume *costumeName*)
* (backdrop *backdropName*)
* (next_costume)
* (next_backdrop)
* (change_size *size*)
* (set_size *size*)
### Events
* (broadcast *broadcastName*)
* (broadcast_wait *broadcastName*)
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
  - Myself is: `_myself_`
  - `(clone _myself_)`
* (delete_clone)
  - Can also be written without parentheses
### Sensing
* (ask *string*)
* (reset_timer)
* (draggable *true/false*)
  - `true`
  - `false`
### Data
* (set *variableName* *string*)
* (change *variableName* *number*)
* (show_variable *variableName*)
* (hide_variable *variableName*)
* (show_list *listName*)
* (hide_list *listName*)
### My Blocks
* (call *procedureName* *arguments...*)
### Extentions
#### Pen
* (pen_up)
* (pen_down)
* (pen_stamp)
* (pen_clear)
* (pen_set *valueName* *number*)
  - `size`
  - `color`
  - `brightness`
  - `transparency`
* (pen_change *valueName* *number*)
  - `size`
  - `color`
  - `brightness`
  - `transparency`
* (pen_color *hexColor*)
  - Example: `(pen_color #ffffff)`
