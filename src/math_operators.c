#include "math_operators.h"

// Can't think of a better name them
#define LAST_7_BITS  0x7F
#define LAST_15_BITS 0x7FFF
#define LAST_31_BITS 0x7FFFFFFF

#define SIGN_8_BIT  0x80
#define SIGN_16_BIT 0x8000
#define SIGN_32_BIT 0x80000000

/**
 * Get the bitmask for shifting that takes everything except the sign
 *
 * @param format needed format
 * @return bitmask that ignores the number sign
 */
lword_t get_shift_mask(enum format_t format)
{
	switch(format) {
		case F_8_BIT:
			return LAST_7_BITS;
		case F_16_BIT:
			return LAST_15_BITS;
		case F_32_BIT:
			return LAST_31_BITS;
	}
}

/**
 * Get the bitmask for shifting that takes only the sign
 *
 * @param format needed format
 * @return bitmask that covers the number sign
 */
lword_t get_sign_mask(enum format_t format)
{
	switch(format) {
		case F_8_BIT:
			return SIGN_8_BIT;
		case F_16_BIT:
			return SIGN_16_BIT;
		case F_32_BIT:
			return SIGN_32_BIT;
	}
}

/* ADD */

sword_t add(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	// get the needed bits
	lword_t v1 = erric->registers[i] & get_mask(format);
	lword_t v2 = erric->registers[j] & get_mask(format);

	// The mask is needed to deal with over- and underflow
	erric->registers[j] = (v1 + v2) & get_mask(format);

	return ERRIC_STATUS_NONE;
}

/* SUB */

sword_t sub(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	// get the needed bits
	lword_t v1 = erric->registers[i] & get_mask(format);
	lword_t v2 = erric->registers[j] & get_mask(format);

	// The mask is needed to deal with over- and underflow
	erric->registers[j] = (v2 - v1) & get_mask(format);

	return ERRIC_STATUS_NONE;
}

/* ASR */

sword_t asr(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	// get the bits to shift (all except for sign)
	lword_t v1 = erric->registers[i] & get_shift_mask(format);
	// shift
	v1 >>= 1;

	// add sign back
	v1 = v1 | (erric->registers[i] & get_sign_mask(format));

	// avoid implicit casting by inserting bits with AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(format);
	erric->registers[j] = res;

	return ERRIC_STATUS_NONE;
}

/* ASL */

sword_t asl(struct erric_t *erric, sword_t i, sword_t j, enum format_t format)
{
	// get last 31 bits only
	lword_t v1 = erric->registers[i] & get_shift_mask(format);
	// shift
	v1 <<= 1;

	// add sign back
	// the current sign of v1 is ignored and the old sign is put back
	v1 = (v1 & get_shift_mask(format)) | (erric->registers[i] & get_sign_mask(format));

	// avoid implicit casting by inserting bits wit AND
	lword_t res = get_mask(F_32_BIT) & v1 & get_mask(format);
	erric->registers[j] = res;

	return ERRIC_STATUS_NONE;
}