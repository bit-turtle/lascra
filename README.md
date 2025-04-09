# lascra (Lisp and Scratch)
lascra is a compiler that compiles a lisp like language into scratch sprite3 files
## Usage
`lascra sprite.sprite3 [code files...]`
* Opens `sprite.json` in `sprite.sprite3`
* Deletes existing code
* Compiles code files
* Adds generated code into `sprite.json` and saves `sprite.sprite3`
## Example Usage
1. Export a Sprite in the scratch editor called "MySprite"
2. Run `lascra MySprite.sprite3 code.scra`  
Contents of `code.scra`:
```
(declare
    (name "MySprite")
)
(define
    (variable "Compiler Name" "lascra")
    (list "Example List" "thing1" "thing2" "thing3")
    (broadcast "Example Broadcast")
)
(when flag
    (say "Hello, World!")
    (say "Length of \"apple\": " (length "apple") )
    (say (join "Two plus two, times two equals: " (* (+ 2 2) 2) ) )
)
(when clicked
    (say (join "Compiler Name: " (variable "Compiler Name") ) )
    (say (join "Square root of 2 is: " (math sqrt 2) ) )
)
```
