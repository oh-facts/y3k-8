# Y3k-8 
### v0.0.4 alpha

Name is placeholder. This is an 8 bit emulator. Programs are made in my own assembly.

atm, I am working on the assembler.

I will eventually make a custom C like language for the emulator, then make an OS with it.

## Compiling

- Source files        : `src/fcpu/main.c`
- Include directories : `src/`

For example, I use clang on windows, so I do this:

```
clang -I./src -o bin/fcpu.exe src/fcpu/main.c
```

I pass `-g` so I can have debug symbols. Pass whatever you want.

## Usage

First, you need to compile an assembly file to a binary. Do something like this,

`./bin/fcpu.exe "../tests/xxx.asm" "xxx.bin"`

Now, that you have the compiled binary, do this,

`./bin/fcpu.exe "xxx.bin"`

Check the docs and `tests/` to look at the assembly instructions that are currently supported.

When you compile an asm file, you will see the lexer and parser output.

When you run the emulator, you will see the binary's output (if its using a logger to print values) and the register values

## For contributors

### Contributing

Open an issue before you choose to work on it because it is possible I am aware / working on it. This isn't needed if we already spoke elsewhere. (however, when doing a pr, explain the thing for documentation's sake).

I have bat scripts in my root directory to automate things that hold meaning to me but I gitignore them. Feel free to do the same with shell/make/ninja/cmake if you prefer. Add them to the gitignore if you're using them.

Report bugs if you find them. Work on them if you want to. Make an issue first.

Check `STYLE.md` for the style guide

### Project Structure

- `fcpu/` Application entry point.
- `base/` contains common util functions I use. These don't depend on other folders. All other folders depend on this.
- `assembler/` The lexer, parser and assembler code goes here.
- `emulator/` Main computer. Assembler backend depends on it to know what the assembly binary representations are.
- `gen/` Files generated by the metaprogrammer go here.
- `meta/` Entry point for the metaprogrammer. Only uses `base/` Doesn't need to be built unless you are developing.