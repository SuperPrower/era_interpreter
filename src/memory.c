#include "memory.h"

int ld(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	lword_t address = era->registers[i];
	// TODO: Add something like a era->mem_size field to check such situations
	if(address > MEM_SIZE)
		return MEMORY_ERROR_OUT_OF_BOUNDS;

	// TODO : We need to take 2 words, not just 1
	era->registers[j] = era->memory[address];

	return 0;
}

int lda(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	// TODO : We need to take 2 words, not just 1
	lword_t constant = era->memory[era->registers[PC]]

	return 0;
}