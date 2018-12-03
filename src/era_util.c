#include "era_util.h"

sword_t read_sword(struct era_t *era, lword_t address)
{
	if(address > MEM_SIZE)
		return 0;
	return (sword_t)(era->memory[address] & 0xFF);
}

word_t read_word(struct era_t *era, lword_t address)
{
	if(address > MEM_SIZE)
		return 0;
	return era->memory[address];
}

lword_t read_lword(struct era_t *era, lword_t address)
{
	if(address + 1 > MEM_SIZE)
		return 0;
	// sizeof(word_t) * 8 returns number of bits
	return (lword_t)(era->memory[address] << (sizeof(word_t) * 8) | era->memory[address + 1]);
}

lword_t get_mask(enum format_t format)
{
	switch(format)
	{
		case F_32_BIT:
			return 0xffffffff;
		case F_16_BIT:
			return 0x0000ffff;
		case F_8_BIT:
			return 0x000000ff;
		default:
			return 0x00000000;
	}
}

int write_lword(struct era_t *era, lword_t address, lword_t word)
{
	// TODO: Add dynamic memory sizing
	if(address > MEM_SIZE || address + 1 > MEM_SIZE)
		return 1;

	era->memory[address] = (word_t)((word >> 16) & 0xffff);
	era->memory[address + 1] = (word_t)(word & 0xffff);

	return 0;
}

int32_t reg_put(enum format_t format, int32_t number)
{
	switch(format) {
	case F_8_BIT:
		return 0xFFFFFFFF & (int8_t)(number);

	case F_16_BIT:
		return 0xFFFFFFFF & (int16_t)(number);

	case F_32_BIT:
		return 0xFFFFFFFF & (int32_t)(number);

	}
}

int32_t reg_get(enum format_t format, int32_t number)
{
	switch(format) {
	case F_8_BIT:
		return (int8_t)(number & 0xFF);

	case F_16_BIT:
		return (int16_t)(number & 0xFFFF);

	case F_32_BIT:
		return (int32_t)(number & 0xFFFFFFFF);

	}
}
