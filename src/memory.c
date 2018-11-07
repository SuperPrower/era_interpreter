#include "memory.h"

int ld(struct era_t *era, uint8_t i, uint8_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	uint32_t address = era->registers[i];
	// TODO: Add something like a era->mem_size field to check such situations
	if(address > MEM_SIZE)
		return MEMORY_ERROR_OUT_OF_BOUNDS;

	// Convert words to bytes.
	// TODO: Should probably make it a function.
	address *= 2;

	// TODO : We need to take 2 words, not just 1
	era->registers[j] = era->memory[address];

	return 0;
}

int lda(struct era_t *era, uint8_t i, uint8_t j, enum format_t format)
{
	if (format != F_32_BIT)
		return MEMORY_ERROR_WRONG_FORMAT;

	// TODO : We need to take 2 words, not just 1
	uint32_t constant = era->memory[era->registers[PC]]

	return 0;
}