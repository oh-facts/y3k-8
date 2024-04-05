## Assembler v0.1.0

// I call this assembler but I mean lexer + parser + assembler
// I think I will call it le parseler, or maybe le arse ass

Only instructions. No labels. No data section
No validation done at any stage.
very verbose - addv and addr. Eventually the lexer will 
be able to figure out from context and you'll only need
to do add


```
program -----------------------> x
         |               |
         |-------<--------
        \|/             /|\
         |               |
          --instruction--


instruction ------OPCODE-------------------> x
                          |            |
                          |-<---","--<-|
                         \|/          /|\
                          |            |
                           ----param---


param --------- REGISTER -----------> x
      |                         |
      |                         |
       ----------LITERAL--------


```

## Parser Tokens

OPCODE, REGISTER, LITERAL, ","