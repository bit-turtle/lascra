# lascra (Lisp and Scratch)
lascra is a compiler that compiles a lisp like language into scratch sprite3 files
## Information
* Documentation in `docs` folder
* Not all scratch blocks are supported at the moment.
* A web version can be compiled using Emscripten
## Usage
`lascra sprite.sprite3 [code files...]`
* Opens `sprite.json` in `sprite.sprite3`
* Deletes existing code
* Compiles code files
* Adds generated code into `sprite.json` and saves `sprite.sprite3`
## Example Usage
1. Export a Sprite in the scratch editor called "MySprite"  
![Export Sprite](images/export.png)
2. Run `lascra MySprite.sprite3 examples/example.scra`  
Contents of `example.scra`:
```
(declare
    (name MySprite)
)
(define
    (variable counter 0)
)
(when flag
    (say "Hello, World!")
    (wait 5)
    (say (join 
        "2*4+3="
        (+ (* 2 4) 3)
    ) )
    (wait 5)
    (set counter 0)
    (say "Counting to 10")
    (wait 5)
    (repeat_until (= (variable counter) 10)
        (wait 1)
        (change counter 1)
        (say (join
            "Value of Counter: "
            (variable counter)
        ) )
    )
    (wait 1)
    (say "Done!")
    (wait 5)
    (ask "What is 2+2?")
    (if (= (value answer) 4)
        (say "Correct!")
    )
    (else
        (say "Incorrect")
    )
)
```
3. Upload the edited Sprite file in the scratch editor  
![Upload Sprite](images/upload.png)

This results in the following code:  
![Resulting Code](images/example.png)
