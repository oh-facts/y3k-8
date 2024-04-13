### style guide

### 1 Indentation:
- I don't care too much for statement lenght. If its too long and typing is tiring, make it a local macro or a function.
- Multiple indentations even upto 8 are fine. Put body in a function only if you find yourself repeating code.
- Don't return early from functions if you can help it. Code flow is easier to read if you have a defined entry and exit.

- switch is written like
```.c
switch(type)
{
    case type_a:
    {
        printf("The type is a on this one");
    }break;
    case type_b:
    {
        printf("The type is b on this one");
    }break;

    default:
    {
        printf("WUHAAAAT");
    }break;
}
```
- single assignments / statements per line

### 2 Breaking long lines and strings

- my award winning editor has line wrap so I don't know what to say. If its easy to follow, break it, if not, don't

### 3 Placing Braces and Spaces

- if/elses/functions are always written with brackets like this
```
if(something)
{
    // 1 or more lines
}
```

### 3.1
https://www.kernel.org/doc/html/v4.10/process/coding-style.html#spaces

### 4
- MACRO_CONSTANTS_ARE_SCREAMING_SNAKE_CASE
- snake_case_for_everything_else 

### 5
- no typedefs for pointers and structs
- stdint types are typedef'd. Check `include/common.h`
- enums and unions are typedef'd
- nested unions are anonymous
  
### 6
- functions are as long as need be. Use local blocks { } and write //comments above it to hold blocks of text that you want to semanticaly divide. Make a function only if you find yourself writing the same code. Or if its an easier representation (consider local macros for this. My award winning language will have proper aliases). 

### 7
- avoid goto. Sometimes they are needed for elegant quitting. But are avoidable in 99% of cases. I use them inside the lexer. That is an example of easily avoidable goto. I am lazy. This is bad and I will fix it.

### 8
- if I can tell what your code is doing by skimming at names of variables / functions its calling, it is appropriately commented. If not, put in the bare minimum to fill in those gaps.
- Use note(name) or todo(name) to annotate as appropriate
- always mention unhandled edge cases / bugs / quirks / something misc that could be helpful to the next programmer that works on the code.

### 9 - 14 (not relevant / covered elsewhere)

### 14
- only one allocation is made, which is zero initialized, and then that memory is given to whoever needs it. This memory is never freed.
- for times when the upper limit for allocations cannot be predicted (as is case for parsing files that are several thousands of lines long), a different strategy will be used. We haven't reached this state, so we won't be exploring it.

### 15
- inline doesn't do anything. modern compilers ignore it. I use it still, but only as a programmer hint. don't use it in hopes that the compiler will inline it.

### 16

- booleans are b32. true is 1, false is 0

### misc
- zero is initialization (ZII)
- Only headers inside `include` and `gen` are allowed to be included with < >. Everything else uses " " and only references code inside of its root project.
- mark all functions with internal linkage as internal and all globals with global and all local static vars with local_persist
- avoid header gaurds unless they make sense. Single translation unit build so they are unrequired.
- code is organized between files based on functionality, not struct names.
- avoid const
- use fopen_s / xxx_s equivalents to stop stupid fucking microsoft compilers from crying.