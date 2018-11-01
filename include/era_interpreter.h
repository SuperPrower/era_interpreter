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
	uint16_t *registers;	/// common registers
	uint16_t IR;		/// instruction register
};

/**
 * Initializa ERA interpreter: allocate memory and registers
 * @param[out]	era	pointer to era structure
 */
int init_era(struct era_t *era);

/**
 * de-allocate ERA struct
 * @param[in]	era	struct to deallocate
 */
int free_era(struct era_t *era);

/**
 * Load ERA program from disk into memory location
 * @param[in]	filename	file to be loaded
 * @param[out]	era		pointer to allocated era structure
 *
 * @returns	count of bytes readed into memory
 */
size_t read_file(char *filename, struct era_t *era);

#endif /* ifndef ERA_INTERPRETER_H */
