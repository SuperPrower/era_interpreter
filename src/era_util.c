#include "era_util.h"

sword_t read_sword(struct era_t *era, lword_t address)
{
	if(address > era->memory_size)
		return 0;
	return (sword_t)(era->memory[address] & get_mask(F_8_BIT));
}

word_t read_word(struct era_t *era, lword_t address)
{
	if(address > era->memory_size)
		return 0;
	return era->memory[address];
}

lword_t read_lword(struct era_t *era, lword_t address)
{
	if(address + 1 > era->memory_size)
		return 0;
	// sizeof(word_t) * 8 returns number of bits
	return (lword_t)(era->memory[address] << (sizeof(word_t) * 8) | era->memory[address + 1]);
}

lword_t get_mask(enum format_t format)
{
	switch(format)
	{
		case F_32_BIT:
			return 0xFFFFFFFF;
		case F_16_BIT:
			return 0x0000FFFF;
		case F_8_BIT:
			return 0x000000FF;
		default:
			return 0x00000000;
	}
}

int write_lword(struct era_t *era, lword_t address, lword_t word)
{
	if(address > era->memory_size || address + 1 > era->memory_size)
		return 1;

	era->memory[address] = (word_t)((word >> 16) & get_mask(F_16_BIT));
	era->memory[address + 1] = (word_t)(word & get_mask(F_16_BIT));

	return 0;
}

int32_t reg_put(enum format_t format, int32_t number)
{
	switch(format) {
	case F_8_BIT:
		return get_mask(F_32_BIT) & (int8_t)(number);

	case F_16_BIT:
		return get_mask(F_32_BIT) & (int16_t)(number);

	case F_32_BIT:
		return get_mask(F_32_BIT) & (int32_t)(number);

	}
}

int32_t reg_get(enum format_t format, int32_t number)
{
	switch(format) {
	case F_8_BIT:
		return (int8_t)(number & get_mask(F_8_BIT));

	case F_16_BIT:
		return (int16_t)(number & get_mask(F_16_BIT));

	case F_32_BIT:
		return (int32_t)(number & get_mask(F_32_BIT));

	}
}


const char* status_texts[] = {
	[0] = "No error",
	[1] = "Exit normal",

	[6] = "Invalid register",
	[7] = "Invalid instruction format",

	[65] = "File error",
	[66] = "Invalid file version",
	[67] = "File read error",

	[68] = "Invalid operator",
	[69] = "Memory out of bounds access"
};

const char* status_what(uint8_t status)
{
	if (status >= sizeof(status_texts)) {
		return "Invalid status code";
	}

	const char * text = status_texts[status];

	if (text == 0) {
		return "Unknown status code";
	}

	return text;
}
