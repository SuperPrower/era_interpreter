#ifndef ERRIC_STRUCT_H
#define ERRIC_STRUCT_H

#include "erric_types.h"

/**
 * @brief Structure, describing ERRIC Interpreter
 */
struct erric_t {
	/// common registers
	lword_t *registers;
	/// machine memory
	word_t *memory;
	/// size of the memory (in words)
	uint32_t memory_size;
	/// instruction register - currently unused
	word_t IR;
	/// Status code field, checked after every insturction, see erric_status.h
	sword_t status_code;
};

#endif //ERRIC_STRUCT_H
