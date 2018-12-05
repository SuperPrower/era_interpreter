#include "branch_operators.h"

// NOTE : Not sure if it's better to put them here or as variables into the function
#define CND_RESULT 0x0000000f
#define CND_EQUAL  0x00000004
#define CND_LESS   0x00000002
#define CND_MORE   0x00000001

sword_t cnd(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return ERA_STATUS_WRONG_REGISTER;

	lword_t mask = get_mask(format);

	lword_t rj = era->registers[j] & mask;
	lword_t ri = era->registers[i] & mask;

	// Clear the space used by the result bits
	era->registers[j] &= ~CND_RESULT;

	if (rj == ri)
	{
		era->registers[j] |= CND_EQUAL;
	}
	else if (rj > ri)
	{
		era->registers[j] |= CND_LESS;
	}
	else if (rj < ri)
	{
		era->registers[j] |= CND_MORE;
	}

	return ERA_STATUS_NONE;
}

sword_t cbr(struct era_t * era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return ERA_STATUS_WRONG_REGISTER;

	if (era->registers[i] != 0)
	{
		era->registers[i] = era->registers[PC];
		// TODO : Sanity checking
		era->registers[PC] = era->registers[j];
	}

	return ERA_STATUS_NONE;
}

sword_t nop(struct era_t * era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_16_BIT)
	{
		// Congratulations, you messed up a NOP function somehow.
		return ERA_STATUS_WRONG_FORMAT;
	}

	return ERA_STATUS_NONE;
}

sword_t stop(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT)
	{
		return ERA_STATUS_WRONG_FORMAT;
	}
	return ERA_STATUS_STOP;
}

sword_t nopstop(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch (format)
	{
		case F_8_BIT:
			return stop(era, i, j, format);
		case F_16_BIT:
			return nop(era, i, j, format);
		default:
			return ERA_STATUS_WRONG_FORMAT;
	}
	return ERA_STATUS_NONE;
}
