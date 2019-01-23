#include "branch_operators.h"

// NOTE : Not sure if it's better to put them here or as variables into the function
#define CND_RESULT 0x0000000f
#define CND_EQUAL  0x00000004
#define CND_LESS   0x00000002
#define CND_MORE   0x00000001

sword_t cnd(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	lword_t mask = get_mask(format);

	lword_t rj = erric->registers[j] & mask;
	lword_t ri = erric->registers[i] & mask;

	// Clear the space used by the result bits
	erric->registers[j] &= ~CND_RESULT;

	if (rj == ri) {
		erric->registers[j] |= CND_EQUAL;

	} else if (rj > ri) {
		erric->registers[j] |= CND_LESS;

	} else if (rj < ri) {
		erric->registers[j] |= CND_MORE;
	}

	return ERRIC_STATUS_NONE;
}

sword_t cbr(struct erric_t * erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	// we don't want i to be PC since we store old PC value in i.
	// Even though we do it before actual jump, this may possibly introduce
	// some bad behaviour.
	if (i == PC || i >= N_REGISTERS || j >= N_REGISTERS) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	if (erric->registers[i] != 0) {
		if (erric->registers[j] >= erric->memory_size) {
			return ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS;
		}

		erric->registers[i] = erric->registers[PC];
		erric->registers[PC] = erric->registers[j];
	}

	return ERRIC_STATUS_NONE;
}

sword_t nop(struct erric_t * erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_16_BIT) {
		// Congratulations, you messed up a NOP function somehow.
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	return ERRIC_STATUS_NONE;
}

sword_t stop(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	return ERRIC_STATUS_STOP;
}

sword_t nopstop(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	switch (format) {
		case F_8_BIT:
			return stop(erric, i, j, format);
		case F_16_BIT:
			return nop(erric, i, j, format);
		default:
			return ERRIC_STATUS_WRONG_FORMAT;
	}
}
