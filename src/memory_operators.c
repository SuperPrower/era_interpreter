#include "memory_operators.h"

sword_t ld(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERA_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERA_STATUS_WRONG_REGISTER;
	}

	lword_t address = era->registers[i];
	if (address >= era->memory_size) {
		return ERA_STATUS_MEMORY_OUT_OF_BOUNDS;
	}

	era->registers[j] = read_lword(era, address);

	return ERA_STATUS_NONE;
}

sword_t lda(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT) {
		return ERA_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERA_STATUS_WRONG_REGISTER;
	}

	lword_t constant = read_lword(era, era->registers[PC]);

	era->registers[j] = era->registers[i] + constant;

	// Depending on correctness of our understanding of LDA instruction,
	// this may or may not be correct
	era->registers[PC] += 2;

	return ERA_STATUS_NONE;
}

sword_t ldc(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERA_STATUS_WRONG_FORMAT;
	}

	if (j >= N_REGISTERS || j == PC) {
		return ERA_STATUS_WRONG_REGISTER;
	}

	era->registers[j] = i;

	return ERA_STATUS_NONE;
}

sword_t st(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERA_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS) {
		return ERA_STATUS_WRONG_REGISTER;
	}

	if (write_lword(era, era->registers[j], era->registers[i]) == 1) {
		return ERA_STATUS_MEMORY_OUT_OF_BOUNDS;
	}

	return ERA_STATUS_NONE;
}

sword_t mov(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERA_STATUS_WRONG_REGISTER;
	}

	lword_t mask = get_mask(format);

	// AND with the inverse of the mask - preserve everything except for the values we are copying
	era->registers[j] &= ~mask;
	era->registers[j] |= era->registers[i] & mask;

	return ERA_STATUS_NONE;
}

sword_t ldaldc(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch (format)
	{
		case F_8_BIT:
			return lda(era, i, j, format);
		case F_32_BIT:
			return ldc(era, i, j, format);
		default:
			return ERA_STATUS_WRONG_FORMAT;
	}
	return ERA_STATUS_NONE;
}
