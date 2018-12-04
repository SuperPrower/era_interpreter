#ifndef ERA_INTERPRETER_H
#define ERA_INTERPRETER_H

// All files needed either by the interpreter or any potential user of the interpreter
#include "era_struct.h"
#include "era_status.h"
#include "era_util.h"

#define N_REGISTERS (32)
#define PC 31
#define SB 30
#define SP 29
#define FP 28

// TODO: Make dynamic later on: either get it from the file or from command line?
// Seeing as we're trying to make it API-like, we should also add functions to modify the values on the fly
// Sizes are in words
#define HEAP_SIZE 100
#define STACK_SIZE 100

/**
 * Initialize ERA interpreter: allocate memory and registers
 *
 * @returns initialized era_t struct pointer
 */
struct era_t* init_era();

/**
 * Initialize ERA interpreter with given memory size
 *
 * @param[in] _mem_size: memory size in words
 * @returns initialized era_t struct pointer
 */
struct era_t* init_era_m(uint32_t _mem_size);


/**
 * Deallocate ERA struct
 * @param[in]	ERA	struct to deallocate
 *
 * @returns 0 on success
 */
int free_era(struct era_t *era);

/**
 * Load ERA program from disk into memory location,
 * process headers and etc.
 *
 * @param[in]	filename	file to be loaded
 * @param[out]	era		pointer to allocated era structure
 *
 * @returns	0 on success, error code on failure
 */
sword_t read_file(char *filename, struct era_t *era);

/**
 * Make one step in execution
 *
 * @param[in]	era	pointer to era structure
 *
 * @returns 0 on success
 */
sword_t step(struct era_t * era);

/**
 * Execute until halted
 *
 * @param[in]	era	pointer to era structure
 *
 * @returns 0 on success
 */
sword_t execute(struct era_t * era);

#endif /* ifndef ERA_INTERPRETER_H */
