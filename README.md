# Y3k-8 
### v0.0.2

Name is placeholder. This is an 8 bit emulator. All programs will be made in my own assembly. It will probably borrow ideas from assembly and other emulators I have seen. 

Atm I am working on cleaning this speghetti fuck fest I have created.

I will eventually make a custom C like language for the emulator, then make an OS with it.

## Compiling

The source code is divided between 5 root folders (projects)

`assembler/`: Assembler code goes here.
`include/`  : Shared header libraries goes here
`emulator/` : Emulator code goes here
`gen/`      : generated code goes here

`meta/`     : metaprogrammer code goes here (dev tool, only needed if you're contributing)

Source files        : `main.c` inside whichever project you want
Include directories : `include/` and `gen/`

For example, I use clang on windows, so I do this:

```
// Compiles assembler
clang -I./include -I./gen -o bin/assm.exe assembler/main.c

// Compiles emulator
clang -I./include -I./gen -o bin/emu.exe emulator/main.c
```

I usually pass `-g` so I can have debug symbols. Pass whatever you want.

## Usage

First, you need to compile an assembly file to a binary. Do something like this,

`./bin/assm.exe "../tests/xxx.asm" "xxx.bin"`

Now, that you have the compiled binary, do this,

`./bin/emu.exe "xxx.bin"`

Check the docs and `tests/` to look at the assembly instructions that are currently supported.

When you compile an asm file, you will see the lexer and parser output.

When you run the emulator, you will see the binary's output and the register values

## Contributing

Open an issue before you choose to work on it because it is possible I am aware / working on it. This isn't needed if we already spoke elsewhere. (however, when doing a pr, explain the thing for documentation's sake).

I don't like build systems so I don't use them. I have bat scripts in my root directory to automate things that mean to me but I gitignore them. Feel free to do the same with shell/make/ninja/cmake if you prefer.

Check `STYLE.md` for the style guide