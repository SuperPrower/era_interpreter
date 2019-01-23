#ifndef ERRIC_REVERSE_TRANSLATION_H
#define ERRIC_REVERSE_TRANSLATION_H

#include "erric_interpreter.h"

/**
 * Returns the name of the given instruction based on the format and instruction code
 *
 * @param[in]	format	format of the function
 * @param[in]	code	instruction code
 *
 * @return string representing the name of the instruction in ERRIC assembler
 */
char *get_instruction_name(enum format_t format, sword_t code);

#endif //ERRIC_REVERSE_TRANSLATION_H
