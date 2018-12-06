#ifndef ERA_FILE_READING_H
#define ERA_FILE_READING_H

#include <stdio.h>
#include "era_interpreter.h"

/**
 * Checks if the system is little-endian
 * Needed mostly for file I/O
 *
 * @return 1 if little-endian, 0 otherwise
 */
uint8_t little_endian();

// TODO: Yes, both of these functions are bad and WILL break if ported.
// I can't figure out a way to make swapping bit-length independent right now. What type should we use and return?
/**
 * Swaps the bytes in a word to change its endianness
 *
 * @param[in] word word to be converted to other endianness
 *
 * @return swapped word
 */
word_t swap_word(word_t word);

/**
 * Swaps the bytes in a long word to change its endianness
 *
 * @param[in] word long word to be converted to other endianness
 *
 * @return swapped long word
 */
lword_t swap_lword(lword_t word);

/**
 * Reads a version 0 executable file
 * See documentation for the format itself
 *
 * @param era			pointer to the era structure
 * @param executable	file to read from
 * @return ERA_STATUS_NONE on success, error status code on failure
 */
sword_t read_v0_file(struct era_t *era, FILE *executable);

/**
 * Reads a version 1 executable file
 * See documentation for the format itself
 *
 * @param era			pointer to the era structure
 * @param executable	file to read from
 * @return ERA_STATUS_NONE on success, error status code on failure
 */
sword_t read_v1_file(struct era_t *era, FILE *executable);

#endif //ERA_FILE_READING_H
