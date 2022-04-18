# SDL2 Project

## Just a Game to learn using C++, SDL2 and a Makefile

## Dependencies

- SDL2 (lib)
- SDL2_image (lib)
- lld (linker)
- make (build tool)
- g++ (compiler)
- git (scm)
- gdb (debugger) [optional]

## Clone Source Code

git clone https://github.com/quincyhill/SDL2_project.git

## Coding Standards

### Writing style

- Use under_scores

### Prepends

In this order

- g
  - prepended to global variables, (maybe functions.. later but idk yet...)
- p
  - prepended to all pointers

## Build Environment

Builds the game demo
`$ make build`

Cleans up object files and removes binary
`$ make clean`

## Run

`$ ./bin/game`

## Additional Info

bitmaps are being yeeted off this project,
instead its better to use SDL2_image from here on
fix up some of these looooong names

## Future

Implementing gdb and unit testing as this project grows
Switch from makefile to cmake when the project becomes bigger

## Bugs

Screen currently just display's white so that needs to be addressed
