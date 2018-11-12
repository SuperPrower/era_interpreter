#ifndef ERA_UTIL_H
#define ERA_UTIL_H

#include "era_interpreter.h"

sword_t read_sword(struct era_t *era, lword_t address);

word_t read_word(struct era_t *era, lword_t address);

lword_t read_lword(struct era_t *era, lword_t address);

#endif //ERA_UTIL_H
