#include "logic.h"

#include "util.h"

enum logic_op_t {
	LOGIC_OR,
	LOGIC_AND,
	LOGIC_XOR,
	LOGIC_LSL,
	LOGIC_LSR
};

// ALL of the functions just differed by 1 line. Decided to move it here for better modularity
int logic_operation(struct era_t *era, sword_t i, sword_t j, enum format_t format, enum logic_op_t operator)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return LOGIC_ERROR_WRONG_REGISTER;

	lword_t mask = get_mask(format);

	// Save the Rj since the original will be modified
	lword_t rj = era->registers[j];

	// Clear the bits into which the value will be written
	// AND with the inverse of the mask preserves everything but the area covered by the mask
	era->registers[j] &= ~mask;
	// rj & mask, ri & mask - get the needed bits
	// use the needed C operation on the extracted bits
	// put them back again with bitwise OR
	switch(operator)
	{
		case LOGIC_OR:
			era->registers[j] |= (rj & mask) | (era->registers[i] & mask);
			break;
		case LOGIC_AND:
			era->registers[j] |= (rj & mask) & (era->registers[i] & mask);
			break;
		case LOGIC_XOR:
			era->registers[j] |= (rj & mask) ^ (era->registers[i] & mask);
			break;
		case LOGIC_LSL:
			era->registers[j] |= (era->registers[i] & mask) << 1;
			break;
		case LOGIC_LSR:
			era->registers[j] |= (era->registers[i] & mask) >> 1;
			break;
		default:
			return LOGIC_ERROR_WRONG_OPERATOR;
	}

	return 0;
}

int or(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_OR);
}

int and(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_AND);
}

int xor(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_XOR);
}

int lsl(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_LSL);
}

int lsr(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_LSR);
}