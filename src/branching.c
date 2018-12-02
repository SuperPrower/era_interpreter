#include "branching.h"

#include "util.h"
#include "era_errors.h"

// NOTE : Not sure if it's better to put them here or as variables into the function
#define CND_RESULT 0x0000000f
#define CND_EQUAL  0x00000004
#define CND_MORE   0x00000001
#define CND_LESS   0x00000002

int cnd(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return BRANCH_ERROR_WRONG_REGISTER;

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
		era->registers[j] |= CND_MORE;
	}
	else if (rj < ri)
	{
		era->registers[j] |= CND_LESS;
	}

	return 0;
}

int cbr(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return BRANCH_ERROR_WRONG_REGISTER;

	if (era->registers[i] != 0)
	{
		era->registers[i] = era->registers[PC];
	}
	// TODO : Sanity checking
	era->registers[PC] = era->registers[j];

	return 0;
}

int nop(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_16_BIT)
	{
		// Congratulations, you messed up a NOP function somehow.
		return BRANCH_ERROR_WRONG_FORMAT;
	}

	return 0;
}

int stop(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	era->error_code = ERROR_STOP;
	return 0;
}