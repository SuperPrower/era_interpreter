#ifndef ERA_UTIL_H
#define ERA_UTIL_H

#include "era_interpreter.h"

uint64_t read_v0_file(struct era_t *era, FILE *executable);

uint64_t read_v1_file(struct era_t *era, FILE *executable);

sword_t read_sword(struct era_t *era, lword_t address);

word_t read_word(struct era_t *era, lword_t address);

lword_t read_lword(struct era_t *era, lword_t address);

// Get the mask for bit extraction based on the given format
lword_t get_mask(enum format_t format);

// Returns 0 on success, 1 on failure
// TODO: type-dependent, VERY bad
int write_lword(struct era_t *era, lword_t address, lword_t word);

uint8_t little_endian();

// TODO: Yes, both of these functions are bad and WILL break if ported.
// I can't figure out a way to make swapping bit-length independent. What type should we use and return?
word_t swap_word(word_t word);

lword_t swap_lword(lword_t word);

#endif //ERA_UTIL_H
