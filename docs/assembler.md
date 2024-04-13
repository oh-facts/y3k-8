## Assembler v0.1.0

```
// I call this assembler but I mean lexer + parser + assembler
// I think I will call it le parseler, or maybe le arse ass
```

### About
Lexer converts characters to tokens. Parser puts tokens inside of ASTs. Assembler converts AST trees to binary. atm, the parser node representation is entirely composed of nodes and tokens. I don't know if its
better to convert literal tokens to literals at this step or do it all in the assembler (what I am currently doing)

Only instructions. No labels. No data section.
No validation done at any stage.
very verbose - addv and addr. Eventually the lexer will 
be able to figure out from context and you'll only need
to do add

## Grammar
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

### Parser Tokens

OPCODE, REGISTER, LITERAL, ","