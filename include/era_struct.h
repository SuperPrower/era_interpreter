#ifndef ERA_STRUCT_H
#define ERA_STRUCT_H

#include "era_types.h"

struct era_t {
	lword_t *registers;	/// common registers
	word_t *memory;		/// machine memory
	word_t IR;		/// instruction register
	sword_t status_code;	/// Status code field, checked after every insturction, see era_status.h
};

#endif //ERA_STRUCT_H
