# Y3k-8 
### v0.0.2 alpha

Name is placeholder. This is an 8 bit emulator. All programs will be made in my own assembly. It will probably borrow ideas from assembly and other emulators I have seen.

Atm I am working on working on making the metaprogrammer more efficent. I also need it to do more things for me, so I will work on that next.

I will eventually make a custom C like language for the emulator, then make an OS with it.

## Compiling

The source code is divided between 4 root folders (projects)

1. `assembler/`: Assembler code goes here.
2. `include/`  : Shared header libraries goes here
3. `emulator/` : Emulator code goes here
4. `meta/`     : metaprogrammer code goes here (dev tool, only needed if you're contributing)

- Source files        : `main.c` inside whichever project you want
- Include directories : `include/`

For example, I use clang on windows, so I do this:

```
// Compiles assembler
clang -I./include -o bin/assm.exe assembler/main.c

// Compiles emulator
clang -I./include -o bin/emu.exe emulator/main.c
```

I usually pass `-g` so I can have debug symbols. Pass whatever you want.

## Usage

First, you need to compile an assembly file to a binary. Do something like this,

`./bin/assm.exe "../tests/xxx.asm" "xxx.bin"`

Now, that you have the compiled binary, do this,

`./bin/emu.exe "xxx.bin"`

Check the `docs/spec` and `tests/` to look at the assembly instructions that are currently supported.

When you compile an asm file, you will see the lexer and parser output.

When you run the emulator, you will see the binary's output and the register values

## Contributing

Open an issue before you choose to work on it because it is possible I am aware / working on it. This isn't needed if we already spoke elsewhere. (however, when doing a pr, explain the thing for documentation's sake).

I denounce all build systems. They are all rubbish and I refuse to use them. I have bat scripts in my root directory to automate tasks that hold meaning to me but I gitignore them. Feel free to do the same with any shell/make/ninja/cmake/etc that you make.

Check `STYLE.md` for the style guide