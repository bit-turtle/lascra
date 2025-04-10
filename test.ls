(declare
	(name "MySprite")
	(x -10)
	(y -50)
	(size 90)
	(direction 40)
	(volume 100)
	(visible true)
	(rotationStyle "left-right")
	(draggable true)
)
(define
	(variable "My Variable" 99)
	(list "My List"
		thing1
		thing2
		"thing 3"
	)
	(list emptylist)
	(list smollist onething)
	(variable emptyvariable)
	(broadcast turtlemessage)
)
(when flag
	(say (join "The square root of 8 times 5 plus 1 is: " (+ (* (math sqrt 8) 5) 1) ) )
)
(when clicked
	(say (length (join "wow" (length "lascra" ) ) ) )
	(say (join "length of thing: " (length "thing") ) )
	(say (join "current day since 2000 is: " (round (value days_since_2000) ) ) )
	(say (join "random number from 2 to 5: " (random 2 5) ) )
	(say (join "mod 5 2: " (mod 5 2)))
)
(when flag
	(say (costume name) )
	(say (backdrop number) )
	(say (value answer) )
	(say (distance _mouse_))
	(say (property "backdrop #" _stage_) )
	(say (item 2 "My List") )
)
