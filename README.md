# lascra (Lisp and Scratch)
lascra is a compiler that compiles a lisp like language into scratch sprite3 files
## Information
* Documentation in `docs` folder
* Not all scratch blocks are supported at the moment.
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
    (name MySprite)
)
(define
    (variable counter 0)
)
(when flag
    (say "Hello, World!")
    (say (join 
        "2*4+3="
        (+ (* 2 4) 3)
    ) )
    (set counter 0)
    (forever
        (say (join
            "Value of Counter: "
            (variable counter)
        ) )
        (change counter 1)
    )
)
```
