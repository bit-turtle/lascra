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
