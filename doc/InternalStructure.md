## Internal structure of ERA Interpreter

### ERA struct
Struct `era_t` represents one ERA machine, or at least set of CPU with registers and a memory chunk.

### Operators
Operators are not bound to the ERA struct, rather, they operate on given `era_t` struct. There also are some helper functions, like those that unify similar instructions in one code block to remove redundant code.

### Instruction execution
All run functions first call `parse_instruction` procedure, that fetches and decodes instruction pointed by PC register. Then, instruction in `instruction_t` struct format is given to `execute` function, which executes it.


## Files and their contents

### Data types
`era_types.h` describes several data types used in ERA interpreter. Those are short word, word and long word, sized one, two and four bytes respectively.

### `era_t` structure
`era_t` structure, defined in `era_struct.h`, describes representation of ERA machine. It main parts are memory, registers, and machine status code.

### Operators
`*_operators.h` files describe operators that ERA CPU can perform, and helper functions for them.

### Interpretation
`era_interpreter.c` contains mapping from operation code to the function that executes given instruction, and also functions to fetch instruction in `instruction_t` struct and parse said instruction.

### Helper functions
`era_util.h` contains helper functions, for example functions that can make accessing memory easier.
