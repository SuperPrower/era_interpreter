#include "logic_operators.h"

enum logic_op_t {
	LOGIC_OR,
	LOGIC_AND,
	LOGIC_XOR,
	LOGIC_LSL,
	LOGIC_LSR
};

// ALL of the functions just differed by 1 line. Decided to move it here for better modularity
sword_t logic_operation(struct era_t *era, sword_t i, sword_t j, enum format_t format, enum logic_op_t operator)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return ERA_STATUS_WRONG_REGISTER;

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
			// Shift to the left
			era->registers[j] |= (era->registers[i] & mask) << 1;
			// Remove the overflow - only  take the needed bits
			era->registers[j] &= mask;
			// Put the rest of the register in
			era->registers[j] |= era->registers[i] & ~mask;
			break;
		case LOGIC_LSR:
			// No need to deal with overflow here
			era->registers[j] = era->registers[i] & ~mask;
			era->registers[j] |= (era->registers[i] & mask) >> 1;
			break;
		default:
			return ERA_STATUS_WRONG_OPERATOR;
	}

	return ERA_STATUS_NONE;
}

sword_t or(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_OR);
}

sword_t and(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_AND);
}

sword_t xor(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_XOR);
}

sword_t lsl(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_LSL);
}

sword_t lsr(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	return logic_operation(era, i, j, format, LOGIC_LSR);
}