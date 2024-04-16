# Y3k-8 
### v0.0.3 alpha

Name is placeholder. This is an 8 bit emulator. All programs will be made in my own assembly. It will probably borrow ideas from assembly and other emulators I have seen. 

Atm I am making the metaprogrammer better. I am also doing refactors since the project grew too much in complexity.

I will eventually make a custom C like language for the emulator, then make an OS with it.

## Compiling

- Source files        : `src/fcpu/main.c`
- Include directories : `src/`

For example, I use clang on windows, so I do this:

```
clang -I./src -o bin/fcpu.exe src/fcpu/main.c
```

I usually pass `-g` so I can have debug symbols. Pass whatever you want.

## Usage

First, you need to compile an assembly file to a binary. Do something like this,

`./bin/fcpu.exe "../tests/xxx.asm" "xxx.bin"`

Now, that you have the compiled binary, do this,

`./bin/fcpu.exe "xxx.bin"`

Check the docs and `tests/` to look at the assembly instructions that are currently supported.

When you compile an asm file, you will see the lexer and parser output.

When you run the emulator, you will see the binary's output and the register values

## For contributors

### Contributing

Open an issue before you choose to work on it because it is possible I am aware / working on it. This isn't needed if we already spoke elsewhere. (however, when doing a pr, explain the thing for documentation's sake).

All build systems for C/C++ are inreedemably bad. This project will never use one. I have bat scripts in my root directory to automate things that mean to me but I gitignore them. Feel free to do the same with shell/make/ninja/cmake if you prefer. Add them to the gitignore, or don't track them yourself.

Check `STYLE.md` for the style guide

### Project Structure

- `fcpu/` Main entry point. Uses other folders to do its thing
- `base/` contains common util functions I use. These don't depend on other folders
- `assembler/` The lexer, parser and assembler code goes here.
- `emulator/` Main computer. Assembler depends on it to know what assembly instructions are supported
- `gen/` Files generated by the metaprogrammer go here.
- `meta/` Entry point for the metaprogrammer. Only uses `base/`