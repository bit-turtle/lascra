# Top Level Statements
There are only 3 top level statements
1. `declare` properties for the sprite
2. `define` variables, lists, and broadcasts for the sprite
3. Run code `when` an event happens
## Declare statements
Many sprite properties can be modified with declare statements. List of properties:
* `name`: Sprite Name *string*
* `x`: X Position *number*
* `y`: Y Position *number*
* `size`: Sprite Size % *number*
* `direction`: Sprite Angle *number*
* `volume`: Sound Volume *number*
* `visible`: Sprite Visibility *boolean*
* `draggable`: Sprite Draggability *boolean*
* `rotationStyle`: Sprite Rotation Style
  - `all around`: Normal Rotation
  - `left-right`: Left-Right Rotation
  - `don't rotate`: Prevent Rotation
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
