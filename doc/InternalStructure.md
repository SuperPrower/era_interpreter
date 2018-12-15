# Internal structure of ERA Interpreter

## Data types
`era_types.h` describes several data types used in ERA interpreter. Those are short word, word and long word, sized one, two and four bytes respectively.

## `era_t` structure
`era_t` structure, defined in `era_struct.h`, describes representation of ERA machine. It main parts are memory, registers, and machine status code.

## Operators
`*_operators.h` files describe operators that ERA CPU can perform, and helper functions for them.

## Helper functions
`era_util.h` contains helper functions, for example functions that can make accessing memory easier.
