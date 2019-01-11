#ifndef ERA_STRUCT_H
#define ERA_STRUCT_H

#include "era_types.h"

/**
 * @brief Structure, describing ERA Interpreter
 */
struct era_t {
	/// common registers
	lword_t *registers;
	/// machine memory
	word_t *memory;
	/// size of the memory (in words)
	uint32_t memory_size;
	/// instruction register - currently unused
	word_t IR;
	/// Status code field, checked after every insturction, see era_status.h
	sword_t status_code;
};

#endif //ERA_STRUCT_H
