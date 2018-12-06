#ifndef ERA_UTIL_H
#define ERA_UTIL_H

#include "era_interpreter.h"

/**
 * Reads a short word from memory
 *
 * @param[in]	era 	pointer to era structure
 * @param[in]	address address to read the word from
 *
 * @return word read or 0 on unsuccessful read
 */
sword_t read_sword(struct era_t *era, lword_t address);

/**
 * Reads a word from memory
 * IMPORTANT : be mindful of memory overlapping
 *
 * @param[in]	era 	pointer to era structure
 * @param[in]	address address to read the word from
 *
 * @return word read or 0 on unsuccessful read
 */
word_t read_word(struct era_t *era, lword_t address);

/**
 * Reads a long word from memory
 * IMPORTANT : be mindful of memory overlapping
 *
 * @param[in]	era 	pointer to era structure
 * @param[in]	address address to read the word from
 *
 * @return word read or 0 on unsuccessful read
 */
lword_t read_lword(struct era_t *era, lword_t address);

/**
 * Get the mask for bit extraction based on the given format
 *
 * @param[in]	format format to get the mask for
 *
 * @return mask to extract the bytes corresponding to the given format
 */
lword_t get_mask(enum format_t format);

/**
 * Writes an lword into the memory
 *
 * @param[in]	era		pointer to era structure
 * @param[in]	address	address to read the word from
 * @param[in]	word	lword to write to the memory address
 *
 * @return 0 on success, 1 on failure
 */
// XXX: type-dependent, VERY bad
int write_lword(struct era_t *era, lword_t address, lword_t word);

/**
 * Helper function used to put 2th complement integers in registers
 *
 * Usage: era->registers[i] = reg_put(F_16_BIT, -1078);
 *
 * @param[in] format: integer format (size)
 * @param[in] number: number to put
 */
int32_t reg_put(enum format_t format, int32_t number);

/**
 * Helper function used to get 2th complement integers from registers
 *
 * Usage: int32_t res = reg_get(F_16_BIT, era->registers[i]);
 *
 * @param[in] format: integer format (size)
 * @param[in] number: number to put
 */
int32_t reg_get(enum format_t format, int32_t number);

/**
 * Returns brief explanation for a given status code
 *
 * @param[in] status: era status code
 *
 * @returns: status text
 */
const char* status_what(uint8_t status);

#endif //ERA_UTIL_H
