#ifndef ERRIC_TYPES_H
#define ERRIC_TYPES_H

#include <stdint.h>

/// @brief one byte type. Called short in regards to regular word.
typedef uint8_t sword_t;
/// @brief two byte type. Commands and memory are sized in words.
typedef uint16_t word_t;
/// @brief 4 byte type. Registers and constants are sized in long words.
typedef uint32_t lword_t;

// NB: can't use identifier like 8_BIT, had to add F_ (Format) prefix
enum format_t
{
	F_8_BIT,
	F_16_BIT,
	F_32_BIT,
};

#endif //ERRIC_TYPES_H
