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
	(say "Hi!")
	(say (variable "My Variable"))
	(say (join "Hello, " "World!"))
	(say
		(join
			"Hello, "
			(join (variable "My Variable") "!")
		)
	)
)
(when clicked
	(say "Bye!")
	(say (list "My List"))
	(say (value timer))
)
