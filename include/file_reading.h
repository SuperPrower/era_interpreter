#ifndef ERA_FILE_READING_H
#define ERA_FILE_READING_H

#include <stdio.h>
#include "era_interpreter.h"

// A macro to swap bytes for endianness in a quick and easy manner
#define CHANGE_ENDIAN(x) swap_bytes((uint8_t*)&(x), sizeof(x))

/**
 * Checks if the system is little-endian
 * Needed mostly for file I/O
 *
 * @return 1 if little-endian, 0 otherwise
 */
uint8_t little_endian();

/**
 * Tries to swap bytes in a byte array
 * Used here to swap between little and big endianness by casting values to arrays with sizeof(variable)
 *
 * @param bytes pointer to an array of uint8_t (usually cast from other types)
 * @param length length of the array (sizoef(original variable)
 */
void swap_bytes(uint8_t *bytes, size_t length);

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
