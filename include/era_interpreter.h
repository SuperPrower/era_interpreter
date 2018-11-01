#ifndef ERA_INTERPRETER_H
#define ERA_INTERPRETER_H

#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE (64 * 1024) /// memory size in words
#define N_REGISTERS (32)
#define PC 31
#define SB 30
#define SP 29
#define FP 28

// Convenience functions, to make sure it's hard to mess stuff up
#define ERA_WORDS(bytes) (bytes) * sizeof(era_word_t)
#define ERA_LWORDS(bytes) (bytes) * sizeof(era_lword_t)

// Not sure about these names
// Unable to open the file
#define READ_ERROR_FILE 1
// Incorrect version
#define READ_ERROR_VERSION 2
// Read failure
#define READ_ERROR_READ 3

typedef uint16_t era_word_t;
// Long Word
typedef uint32_t era_lword_t;

struct era_t {
	era_word_t *memory;	/// machine memory
	era_lword_t *registers;	/// common registers
	era_word_t IR;		/// instruction register
};

/**
 * Initialize ERA interpreter: allocate memory and registers
 * @param[out]	era	pointer to era structure
 *
 * @returns 0 on success
 */
int init_era(struct era_t *era);

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
uint64_t read_file(char *filename, struct era_t *era);

/**
 * Make one step in execution
 *
 * @param[in]	era	pointer to era structure
 *
 * @returns 0 on success
 */
int step(struct era_t *era);

/**
 * Execute until halted
 *
 * @param[in]	era	pointer to era structure
 *
 * @returns 0 on success
 */
int execute(struct era_t *era);

#endif /* ifndef ERA_INTERPRETER_H */
