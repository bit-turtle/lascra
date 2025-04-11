# Parameter Statements
Parameter statements are used to pass values into blocks
## Example
```
(when flag
  (say (join "Parameter " "Statement") )
)
```
The parameter statement in `say` is `join`, which takes in two parameter statements of strings
## Types of parameter statements
* Number
  - Number
  - Positive Number
  - Integer
  - Positive Integer
  - Generic Parameter
* String
  - String
  - Generic Parameter
* Boolean (Not yet implemented)
  - Boolean parameters are always boolean blocks.
  - Boolean blocks:
    - (= *string* *string*)
    - (> *string* *string*)
    - (< *string* *string*)
## Generic Parameters
Generic parameters are blocks passed as values instead of inputing the value directly. List of generic parameters
* (variable *variableName*)
* (list *listName*)
* (size *listName*)
* (item *integer* *listName*)
* (item# *string* *listName*)
* (value *valueid*)
  - `x`
  - `y`
  - `direction`
  - `size`
  - `volume`
  - `mouse_x`
  - `mouse_y`
  - `answer`
  - `loudness`
  - `timer`
  - `days_since_2000`
  - `username`
  - Extensions:
    - `music_tempo`
    - `translate_language`
    - `ev3_distance`
    - `ev3_brightness`
    - `wedo_distance`
    - `go_force`
* (costume *numbername*)
  - `number`
  - `name`
* (backdrop *numbername*)
  - `number`
  - `name`
* (distance *spritename*)
  - `_mouse_` for mouse pointer
* (current *timeperiod*)
  - `year`
  - `month`
  - `date`
  - `day_of_week`
  - `hour`
  - `minute`
  - `second`
* (property *propertyname* *spritename*)
  - `_stage_` for stage
  - Check scratch for list of properties. Sensing: (property of sprite) block
  - Example: `(property "backdrop name" _stage_)`
* (join *string* *string*)
* (letter *positiveInteger* *string*)
* (length *string*)
* (round *number*)
* (random *number* *number*)
* Math Operators (*operator* *number* *number*)
  - (+ *number* *number*)
  - (- *number* *number*)
  - (* *number* *number*)
  - (/ *number* *number*)
* (mod *number* *number*)
* (math *functionName* *number*)
  - Check scratch for list of functions. Operators: (function of number) block
  - Example: `(math sqrt 2.5)`
* Extensions:
  - (translate *string* *languagecode*)
    - Check ISO 639 for language codes
    - Example: `(translate "Hello!" es)` Translate to spanish
  - (video *attribute* *subject*)
    - Attributes:
      - `motion`
      - `direction`
    - Subjects:
      - `sprite`
      - `stage`
  - Tilt blocks:
    - (boost_tilt *direction*)
    - (micro_tilt *direction*)
    - (wedo_tilt *direction*)
    - (go_tilt *direction*)
    - Check scratch for valid values
    - Example: `(micro_tilt front)`
  - Motor Position blocks:
    - (boost_motorpos *motorID*)
    - (ev3_motorpos *motorID*)
    - Motor IDs: A, B, C, D
