#include "operators.h"

/* ADD */

int add8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 8 bits only
	int8_t v1 = era->registers[i] & 0xFF;
	int8_t v2 = era->registers[j] & 0xFF;

	// avoid implicit casting by inserting bits with AND
	lword_t res = 0XFFFFFFFF & (v1 + v2);
	era->registers[j] = res;

	return 0;
}

int add16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 16 bits only
	int16_t v1 = era->registers[i] & 0xFFFF;
	int16_t v2 = era->registers[j] & 0xFFFF;

	// avoid implicit casting by inserting bits with AND
	lword_t res = 0XFFFFFFFF & (v1 + v2);
	era->registers[j] = res;

	return 0;
}

int add32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 32 bits only
	int32_t v1 = era->registers[i] & 0xFFFFFFFF;
	int32_t v2 = era->registers[j] & 0xFFFFFFFF;

	// avoid implicit casting by inserting bits with AND
	lword_t res = 0XFFFFFFFF & (v1 + v2);
	era->registers[j] = res;

	return 0;
}

int add(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return add8(era, i, j);

	case F_16_BIT:
		return add16(era, i, j);

	case F_32_BIT:
		return add32(era, i, j);

	}
	return 0;
}

/* SUB */

int sub8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 8 bits only
	int8_t v1 = era->registers[i] & 0xFF;
	int8_t v2 = era->registers[j] & 0xFF;

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & (v2 - v1);
	era->registers[j] = res;

	return 0;
}

int sub16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 16 bits only
	int16_t v1 = era->registers[i] & 0xFFFF;
	int16_t v2 = era->registers[j] & 0xFFFF;

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & (v2 - v1);
	era->registers[j] = res;

	return 0;
}

int sub32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 32 bits only
	int32_t v1 = era->registers[i] & 0xFFFFFFFF;
	int32_t v2 = era->registers[j] & 0xFFFFFFFF;

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & (v2 - v1);
	era->registers[j] = res;

	return 0;
}

int sub(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return sub8(era, i, j);

	case F_16_BIT:
		return sub16(era, i, j);

	case F_32_BIT:
		return sub32(era, i, j);

	}

	return 0;
}

/* ASR */

int asr8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 7 bits only
	int8_t v1 = era->registers[i] & 0x7F;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & 0x80);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asr16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 15 bits only
	int16_t v1 = era->registers[i] & 0x7FFF;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & 0x8000);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asr32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 31 bits only
	int32_t v1 = era->registers[i] & 0x7FFFFFFF;
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (era->registers[i] & 0x80000000);


	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asr(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return asr8(era, i, j);

	case F_16_BIT:
		return asr16(era, i, j);

	case F_32_BIT:
		return asr32(era, i, j);

	}

	return 0;
}

/* ASL */

int asl8(struct era_t *era, sword_t i, sword_t j)
{
	// get last 7 bits only
	int8_t v1 = era->registers[i] & 0x7F;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & 0x7F) | (era->registers[i] & 0x80);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asl16(struct era_t *era, sword_t i, sword_t j)
{
	// get last 15 bits only
	int16_t v1 = era->registers[i] & 0x7FFF;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & 0x7FFF) | (era->registers[i] & 0x8000);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asl32(struct era_t *era, sword_t i, sword_t j)
{
	// get last 31 bits only
	int32_t v1 = era->registers[i] & 0x7FFFFFFF;
	// shift
	v1 <<= 1;

	// add sign back, but this time by setting it to 0 and then using OR
	v1 = (v1 & 0x7FFFFFFF) | (era->registers[i] & 0x80000000);

	// avoid implicit casting by inserting bits wit AND
	lword_t res = 0XFFFFFFFF & v1;
	era->registers[j] = res;

	return 0;
}

int asl(struct era_t *era, sword_t i, sword_t j, enum format_t format)
{
	switch(format) {
	case F_8_BIT:
		return asl8(era, i, j);

	case F_16_BIT:
		return asl16(era, i, j);

	case F_32_BIT:
		return asl32(era, i, j);

	}

	return 0;
}
