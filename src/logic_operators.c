#include "logic_operators.h"

enum logic_op_t {
	LOGIC_OR,
	LOGIC_AND,
	LOGIC_XOR,
	LOGIC_LSL,
	LOGIC_LSR
};

// ALL of the functions just differed by 1 line. Decided to move it here for better modularity
sword_t logic_operation(struct erric_t *erric, sword_t i, sword_t j, enum format_t format, enum logic_op_t operator)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	lword_t mask = get_mask(format);
	// Save the Rj since the original will be modified
	lword_t rj = erric->registers[j];

	// Clear the bits into which the value will be written
	// AND with the inverse of the mask preserves everything but the area covered by the mask
	erric->registers[j] &= ~mask;
	// rj & mask, ri & mask - get the needed bits
	// use the needed C operation on the extracted bits
	// put them back again with bitwise OR
	switch(operator) {
		case LOGIC_OR:
			erric->registers[j] |= (rj & mask) | (erric->registers[i] & mask);
			break;
		case LOGIC_AND:
			erric->registers[j] |= (rj & mask) & (erric->registers[i] & mask);
			break;
		case LOGIC_XOR:
			erric->registers[j] |= (rj & mask) ^ (erric->registers[i] & mask);
			break;
		case LOGIC_LSL:
			// Shift to the left
			erric->registers[j] |= (erric->registers[i] & mask) << 1;
			// Remove the overflow - only  take the needed bits
			erric->registers[j] &= mask;
			break;
		case LOGIC_LSR:
			// No need to deal with overflow here
			erric->registers[j] = (erric->registers[i] & mask) >> 1;
			break;
		default:
			return ERRIC_STATUS_WRONG_OPERATOR;
	}

	return ERRIC_STATUS_NONE;
}

sword_t or(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(erric, i, j, format, LOGIC_OR);
}

sword_t and(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(erric, i, j, format, LOGIC_AND);
}

sword_t xor(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(erric, i, j, format, LOGIC_XOR);
}

sword_t lsl(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(erric, i, j, format, LOGIC_LSL);
}

sword_t lsr(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(erric, i, j, format, LOGIC_LSR);
}
