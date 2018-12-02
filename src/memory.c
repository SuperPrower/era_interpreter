#include "memory.h"

#include "util.h"

int ld(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return ERA_STATUS_WRONG_FORMAT;

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC)
		return ERA_STATUS_WRONG_REGISTER;

	lword_t address = era->registers[i];
	// TODO: Add something like a era->mem_size field to check such situations
	if(address > MEM_SIZE)
		return ERA_STATUS_MEMORY_OUT_OF_BOUNDS;

	era->registers[j] = read_lword(era, address);

	return ERA_STATUS_NONE;
}

int lda(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT)
		return ERA_STATUS_WRONG_FORMAT;

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC)
		return ERA_STATUS_WRONG_REGISTER;

	lword_t constant = read_lword(era, era->registers[PC]);

	era->registers[j] = era->registers[i] + constant;

	// TODO : I think this is correct, but this should be tested.
	era->registers[PC] += 2;

	return ERA_STATUS_NONE;
}

int ldc(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return ERA_STATUS_WRONG_FORMAT;

	if (j >= N_REGISTERS || j == PC)
		return ERA_STATUS_WRONG_REGISTER;

	era->registers[j] = i;

	return ERA_STATUS_NONE;
}

int st(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return ERA_STATUS_WRONG_FORMAT;

	if (i >= N_REGISTERS || j >= N_REGISTERS)
		return ERA_STATUS_WRONG_REGISTER;

	if(write_lword(era, era->registers[j], era->registers[i]) == 1)
		return ERA_STATUS_MEMORY_OUT_OF_BOUNDS;

	return ERA_STATUS_NONE;
}

int mov(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC)
		return ERA_STATUS_WRONG_REGISTER;

	lword_t mask = get_mask(format);

	// AND with the inverse of the mask - preserve everything except for the values we are copying
	era->registers[j] &= ~mask;
	era->registers[j] |= era->registers[i] & mask;

	return ERA_STATUS_NONE;
}