#ifndef ERA_REVERSE_TRANSLATION_H
#define ERA_REVERSE_TRANSLATION_H

#include "era_interpreter.h"

/**
 * Returns the name of the given instruction based on the format and instruction code
 *
 * @param[in]	format	format of the function
 * @param[in]	code	instruction code
 *
 * @return string representing the name of the instruction in ERA assembler
 */
char *get_instruction_name(enum format_t format, sword_t code);

#endif //ERA_REVERSE_TRANSLATION_H
