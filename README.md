# BrainCuck

## About

This is a simple BrainF\*ck translator that translates BrainF\*ck into C.
The C file can then be compiled using `gcc` or any standard-compliant C compiler.

BrainCuck is written in C++ however.

This translator does perform minor optimizations (which would probably be done by
the C compiler anyway) such as turning multiple `+` into a single addition and
the same with `-`, `<`, and `>`.

## Usage
`mkdir build`

`cmake ..`

`make`

`./out ../res/tictactoe.bf bf.c`

`gcc bf.c -O3`

`./a.out`
