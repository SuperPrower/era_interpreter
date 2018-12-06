#include "reverse_translation.h"

// Small translation table for storing. Has 2 edge cases handled by the function
char *era_instruction_text[] = {
	"NS",	// Special case - format dependent
	"LD",
	"LDAC",	// Special case - format dependent
	"ST", "MOV", "ADD", "SUB",
	"ASR", "ASL", "OR", "AND",
	"XOR", "LSL", "LSR", "CND",
	"CBR"
};

char *get_instruction(enum format_t format, sword_t code)
{
	// Not quite good, but this part shouldn't change, so no problem here?
	if (code == 0) {
		if (format == F_8_BIT)
			return "STOP";
		return "NOP";
	}
	else if (code == 2) {
		if (format == F_8_BIT)
			return "LDA";
		return "LDC";
	}
	return era_instruction_text[code];
}