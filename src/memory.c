#include "memory.h"

#include "util.h"

int ld(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	if (i > N_REGISTERS || j > N_REGISTERS)
		return MEMORY_ERROR_WRONG_REGISTER;

	lword_t address = era->registers[i];
	// TODO: Add something like a era->mem_size field to check such situations
	if(address > MEM_SIZE)
		return MEMORY_ERROR_OUT_OF_BOUNDS;

	era->registers[j] = read_lword(era, address);

	return 0;
}

int lda(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return MEMORY_ERROR_WRONG_REGISTER;

	lword_t constant = read_lword(era, era->registers[PC]);

	era->registers[j] = era->registers[i] + constant;

	// TODO: The assumption here
	++(era->registers[PC]);

	return 0;
}

int ldc(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	if (j >= N_REGISTERS)
		return MEMORY_ERROR_WRONG_REGISTER;

	era->registers[j] = i;

	return 0;
}

int st(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return MEMORY_ERROR_WRONG_REGISTER;

	if(write_lword(era, era->registers[j], era->registers[i]) == 1)
		return MEMORY_ERROR_OUT_OF_BOUNDS;

	return 0;
}

int mov(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j > N_REGISTERS)
		return MEMORY_ERROR_WRONG_REGISTER;

	lword_t mask;

	switch(format)
	{
		case F_32_BIT:
			mask = 0xffffffff;
			break;
		case F_16_BIT:
			mask = 0x0000ffff;
			break;
		case F_8_BIT:
			mask = 0x000000ff;
			break;
	}

	// AND with the inverse of the mask - preserve everything except for the values we are copying
	era->registers[j] &= ~mask;
	era->registers[j] |= era->registers[i] & mask;

	return 0;
}