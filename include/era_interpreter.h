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

struct era_t {
	uint16_t *memory;	/// machine memory
	uint32_t *registers;	/// common registers
	uint32_t IR;		/// instruction register
};

/**
 * Initializa ERA interpreter: allocate memory and registers
 * @param[out]	era	pointer to era structure
 *
 * @returns 0 on success
 */
int init_era(struct era_t *era);

/**
 * de-allocate ERA struct
 * @param[in]	era	struct to deallocate
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
 * @returns	count of bytes readed into memory
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
