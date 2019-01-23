#include "memory_operators.h"

sword_t ld(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	lword_t address = erric->registers[i];
	if (address >= erric->memory_size) {
		return ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS;
	}

	erric->registers[j] = read_lword(erric, address);

	return ERRIC_STATUS_NONE;
}

sword_t lda(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_8_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	lword_t constant = read_lword(erric, erric->registers[PC]);

	erric->registers[j] = erric->registers[i] + constant;

	// sizeof are in bytes, therefore we divide by word size to get the amount of words skipped
	erric->registers[PC] += sizeof(lword_t) / sizeof(word_t);

	return ERRIC_STATUS_NONE;
}

sword_t ldc(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	if (j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	erric->registers[j] = i;

	return ERRIC_STATUS_NONE;
}

sword_t st(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (format != F_32_BIT) {
		return ERRIC_STATUS_WRONG_FORMAT;
	}

	if (i >= N_REGISTERS || j >= N_REGISTERS) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	if (write_lword(erric, erric->registers[j], erric->registers[i]) == 1) {
		return ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS;
	}

	return ERRIC_STATUS_NONE;
}

sword_t mov(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	if (i >= N_REGISTERS || j >= N_REGISTERS || j == PC) {
		return ERRIC_STATUS_WRONG_REGISTER;
	}

	lword_t mask = get_mask(format);

	// AND with the inverse of the mask - preserve everything except for the values we are copying
	erric->registers[j] &= ~mask;
	erric->registers[j] |= erric->registers[i] & mask;

	return ERRIC_STATUS_NONE;
}

sword_t ldaldc(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	switch (format)
	{
		case F_8_BIT:
			return lda(erric, i, j, format);
		case F_32_BIT:
			return ldc(erric, i, j, format);
		default:
			return ERRIC_STATUS_WRONG_FORMAT;
	}
}
