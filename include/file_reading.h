#ifndef ERA_FILE_READING_H
#define ERA_FILE_READING_H

#include <stdio.h>
#include "era_interpreter.h"

uint8_t little_endian();

// TODO: Yes, both of these functions are bad and WILL break if ported.
// I can't figure out a way to make swapping bit-length independent. What type should we use and return?
word_t swap_word(word_t word);

lword_t swap_lword(lword_t word);

sword_t read_v0_file(struct era_t *era, FILE *executable);

sword_t read_v1_file(struct era_t *era, FILE *executable);

#endif //ERA_FILE_READING_H
