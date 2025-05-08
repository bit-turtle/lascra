# Top Level Statements
There are 5 different top level statements
1. `declare` properties for the sprite
2. `define` variables, lists, and broadcasts for the sprite
3. Run code `when` an event happens
4. Define a `procedure`
5. Define a `function` which runs without screen refresh
## Declare statements
Many sprite properties can be modified with declare statements. List of properties:
* `name`: Sprite Name *string*
* `layerOrder`: Layer Number *number*
* Sprites Only:
  * `size`: Sprite Size % *number*
  * `x`: X Position *number*
  * `y`: Y Position *number*
  * `direction`: Sprite Angle *number*
  * `volume`: Sound Volume *number*
  * `visible`: Sprite Visibility *boolean*
  * `draggable`: Sprite Draggability *boolean*
  * `rotationStyle`: Sprite Rotation Style
    - `all around`: Normal Rotation
    - `left-right`: Left-Right Rotation
    - `don't rotate`: Prevent Rotation
* Stage Only:
  * `tempo`: Tempo in BPM *number*
  * `videoState`: Video State
    - `on`
    - `off`
    - `on-flipped`
  * `videoTransparency`: Video Transparency % *number*
  * `textToSpeechLanguage`: Text to Speech Language *string* (Language Code)
```
(declare
  (name "MySprite")
  (x 0)
  (y 0)
  (size 100)
  (direction 90)
  (volume 100)
  (visible true)
  (draggable false)
  (rotationStyle "all around")
)
```
## Define Statements
Variables, lists, and broadcasts are created with define statements. List of definitions:
* `variable`: Define a variable with an optional value
* `list`: Define a list, optionally with some values.
* `broadcast`: Define a broadcast
```
(define
  (variable MyVariable 0)
  (list MyList first second third fourth fifth)
  (broadcast MyBroadcast)
)
```
## When Statements
When statements are used to run code when a certain event happens. List of events:
* `flag`: Green Flag Pressed
* `clicked`: Sprite Clicked
* `(received broadcastName)`: Broadcast Received
```
(when flag
  (say "Green Flag Pressed!")
)
(when clicked
  (say "Sprite Clicked!")
)
(when (received MyBroadcast)
  (say "Received Broadcast!")
)
```
## Procedure and Function Statements
Procedures and Functions are identical except for the fact that functions run without screen
refresh.
### Procedure Structure
`(procedure Name (arguments) code...)`
### Procedure Arguments
Either text or arguments can be entered into the arguments section, argument types:
* `(number Name)`
* `(string Name)`
* `(boolean Name)`
### Example Procedure
```
(procedure say_if (Say (string message) if (boolean condition) )
    (if (argument condition)
        (say (argument message) )
    )
)
```
