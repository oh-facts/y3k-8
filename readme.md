# Y3k-8 
### v0.0.1

Name is placeholder. This is an 8 bit emulator. All programs will be made in my own assembly. It will probably borrow ideas from assembly and other emulators I have seen. 

Atm I am working on improving the parser. Once its better, I will add more instructions and sys calls and devices.

I will eventually make a custom C like language for the emulator, then make an OS with it.

## Compiling

Its a unity build atm. Just compile `main.c`. No flags needed, unless you want to provide them. I might make two translation units in the future, but for now, only compile `main.c`. I am not using `cmake` for
this project because a) It is dogshit. b) The codebase size is trivial enough to not matter atm. Might use a lua script in the future.

Personally, I use clang on windows, so I do this inside a `bin` folder.

```
clang  ../src/main.c -o bin.exe
./bin.exe "../tests/oopa.fasm"
```

## Usage

`./out "filename"`

Check `src/language.h` and `tests/` to look at the assembly instructions that are currently supported.
When you run the program, you will see the lexer and parser output. And then you will see the
values inside the registers.

## Contributing

Open an issue if its a bug or a feature or something else before you choose to work on it because it is possible I am aware / working on it.