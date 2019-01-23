#ifndef ERRIC_INTERPRETER_H
#define ERRIC_INTERPRETER_H

// All files needed either by the interpreter or any potential user of the interpreter
#include "erric_struct.h"
#include "erric_status.h"
#include "erric_util.h"

#define N_REGISTERS (32)
#define PC 31
#define SB 30
#define SP 29
#define FP 28

struct instruction_t {
	enum format_t format;
	sword_t code;
	sword_t i;
	sword_t j;
};

/**
 * Initialize ERRIC interpreter: allocate memory and registers
 *
 * @returns initialized erric_t struct pointer
 */
struct erric_t* init_erric();

/**
 * Initialize ERRIC interpreter with given memory size
 *
 * @param[in] _mem_size: memory size in words
 * @returns initialized erric_t struct pointer
 */
struct erric_t* init_erric_m(uint32_t _mem_size);

/**
 * Deallocate ERRIC struct
 * @param[in]	erric	struct to deallocate
 *
 * @returns 0 on success
 */
int free_erric(struct erric_t * erric);

/**
 * Load ERRIC program from disk into memory location,
 * process headers and etc.
 *
 * @param[in]	filename	file to be loaded
 * @param[out]	erric		pointer to allocated erric structure
 *
 * @returns	ERRIC_STATUS_NONE on success, error code on failure
 */
sword_t read_file(char *filename, struct erric_t *erric);

/**
 * Parse the instruction into instuction_t structure
 *
 * @param[in] instruction instruction word to try to parse
 *
 * @return parsed instruction information, even if the instruction is invalid
 */
struct instruction_t parse_instruction(word_t instruction);

/**
 * Make one step in execution
 *
 * @param[in]	erric	pointer to erric structure
 *
 * @returns status code returned by the executed instruction
 */
sword_t step(struct erric_t * erric);

/**
 * Execute until halted by some error
 *
 * @param[in]	erric	pointer to erric structure
 *
 * @returns final status code
 */
sword_t execute(struct erric_t * erric);

#endif /* ifndef ERRIC_INTERPRETER_H */
