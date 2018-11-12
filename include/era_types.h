#ifndef ERA_ERA_TYPES_H
#define ERA_ERA_TYPES_H

#include <stdint.h>

// Short word
typedef uint8_t sword_t;
// Word
typedef uint16_t word_t;
// Long word
typedef uint32_t lword_t;

// NB: can't use identifier like 8_BIT, had to add F_ (Format) prefix
enum format_t
{
	F_8_BIT,
	F_16_BIT,
	F_32_BIT,
};

#endif //ERA_ERA_TYPES_H
