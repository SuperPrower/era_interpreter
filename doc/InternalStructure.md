## Internal structure of ERRIC Interpreter

### ERRIC struct
Struct `erric_t` represents one ERRIC machine, or at least set of CPU with registers and a memory chunk.

### Operators
Operators are not bound to the ERRIC struct, rather, they operate on given `erric_t` struct. There also are some helper functions, like those that unify similar instructions in one code block to remove redundant code.

### Instruction execution
All run functions first call `parse_instruction` procedure, that fetches and decodes instruction pointed by PC register. Then, instruction in `instruction_t` struct format is given to `execute` function, which executes it.


## Files and their contents

### Data types
`erric_types.h` describes several data types used in ERRIC interpreter. Those are short word, word and long word, sized one, two and four bytes respectively.

### `erric_t` structure
`erric_t` structure, defined in `erric_struct.h`, describes representation of ERRIC machine. It main parts are memory, registers, and machine status code.

### Operators
`*_operators.h` files describe operators that ERRIC CPU can perform, and helper functions for them.

### Interpretation
`erric_interpreter.c` contains mapping from operation code to the function that executes given instruction, and also functions to fetch instruction in `instruction_t` struct and parse said instruction.

### Helper functions
`erric_util.h` contains helper functions, for example functions that can make accessing memory easier.
