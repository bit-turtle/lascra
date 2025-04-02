# lascra (Lisp and Scratch)
lascra is a lisp to scratch compiler
## Usage
`lascra sprite.sprite3 [code files...]`
* Opens `sprite.json` in `sprite.sprites`
* Deletes existing code
* Compiles code files
* Adds generated code into `sprite.json` and saves `sprite.sprite3`
## Example
``
(when flag (do
    (say (message "Hi"))
    (move 0 3)
    (set "My Variable" 5)
    (if (equal (var "My Variable") 5)
        (then
            (change-y 10)
        )
        (else
            (change-x 20)
        )
    )
    (item# "List name" "Item Name")
    (add "Thing" "List name")
))
``
