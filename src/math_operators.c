#include "math_operators.h"

/*
 * NOTE: all the different functions here are needed to more easily deal with potential overflow
 */

// Can't think of a better name or way to use them
#define LAST_7_BITS  0x7F
#define LAST_15_BITS 0x7FFF
#define LAST_31_BITS 0x7FFFFFFF

#define SIGN_8_BIT  0x80
#define SIGN_16_BIT 0x8000
#define SIGN_32_BIT 0x80000000

/* ADD */

sword_t add8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 8 bits only
	sword_t v1 = era->registers[i] & get_mask(F_8_BIT);
	sword_t v2 = era->registers[j] & get_mask(F_8_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & ((v1 + v2) & get_mask(F_8_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t add16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 16 bits only
	word_t v1 = era->registers[i] & get_mask(F_16_BIT);
	word_t v2 = era->registers[j] & get_mask(F_16_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & ((v1 + v2) & get_mask(F_16_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t add32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 32 bits only
	lword_t v1 = era->registers[i] & get_mask(F_32_BIT);
	lword_t v2 = era->registers[j] & get_mask(F_32_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & ((v1 + v2) & get_mask(F_32_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t add(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return add8(era, i, j);

	case F_16_BIT:
		return add16(era, i, j);

	case F_32_BIT:
		return add32(era, i, j);

	}
	return ERA_STATUS_NONE;
}

/* SUB */

sword_t sub8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 8 bits only
	sword_t v1 = era->registers[i] & get_mask(F_8_BIT);
	sword_t v2 = era->registers[j] & get_mask(F_8_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_16_BIT) & ((v2 - v1) & get_mask(F_8_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t sub16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 16 bits only
	word_t v1 = era->registers[i] & get_mask(F_16_BIT);
	word_t v2 = era->registers[j] & get_mask(F_16_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & ((v2 - v1) & get_mask(F_16_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t sub32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 32 bits only
	lword_t v1 = era->registers[i] & get_mask(F_32_BIT);
	lword_t v2 = era->registers[j] & get_mask(F_32_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & ((v2 - v1) & get_mask(F_32_BIT));
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t sub(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return sub8(era, i, j);

	case F_16_BIT:
		return sub16(era, i, j);

	case F_32_BIT:
		return sub32(era, i, j);

	}

	return ERA_STATUS_NONE;
}

/* ASR */

sword_t asr8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 7 bits only
	sword_t v1 = era->registers[i] & LAST_7_BITS;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & SIGN_8_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_8_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asr16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 15 bits only
	word_t v1 = era->registers[i] & LAST_15_BITS;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & SIGN_16_BIT);

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_16_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asr32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 31 bits only
	lword_t v1 = era->registers[i] & LAST_31_BITS;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & SIGN_32_BIT);


	// avoid implicit casting by inserting bits wit AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_32_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asr(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return asr8(era, i, j);

	case F_16_BIT:
		return asr16(era, i, j);

	case F_32_BIT:
		return asr32(era, i, j);

	}

	return ERA_STATUS_NONE;
}

/* ASL */

sword_t asl8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 7 bits only
	sword_t v1 = era->registers[i] & LAST_7_BITS;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & LAST_7_BITS) | (era->registers[i] & SIGN_8_BIT);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_8_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asl16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 15 bits only
	int16_t v1 = era->registers[i] & LAST_15_BITS;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & LAST_15_BITS) | (era->registers[i] & SIGN_16_BIT);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_16_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asl32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 31 bits only
	int32_t v1 = era->registers[i] & LAST_31_BITS;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & LAST_31_BITS) | (era->registers[i] & SIGN_32_BIT);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(F_32_BIT);
	era->registers[j] = res;

	return ERA_STATUS_NONE;
}

sword_t asl(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return asl8(era, i, j);

	case F_16_BIT:
		return asl16(era, i, j);

	case F_32_BIT:
		return asl32(era, i, j);

	}

	return ERA_STATUS_NONE;
}
