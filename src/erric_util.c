#include "erric_util.h"

uint8_t little_endian()
{
	// Little-endian:
	// 01 00
	// Big endian:
	// 00 01
	// Therefore, 1 will be read on little-endian and 0 on big-endian
	uint16_t x = 1;
	return *(uint8_t *) &x;
}

sword_t read_sword(struct erric_t *erric, lword_t address)
{
	if(address > erric->memory_size)
		return 0;
	return (sword_t)(erric->memory[address] & get_mask(F_8_BIT));
}

word_t read_word(struct erric_t *erric, lword_t address)
{
	if(address > erric->memory_size)
		return 0;
	return erric->memory[address];
}

lword_t read_lword(struct erric_t *erric, lword_t address)
{
	if(address + 1 > erric->memory_size)
		return 0;
	// sizeof(word_t) * 8 returns number of bits
	// Little endian reverses the bits, so we need to read them in a different order
	if(little_endian())
		return (lword_t)((lword_t)erric->memory[address + 1] << (sizeof(word_t) * 8) | erric->memory[address]);
	return (lword_t)((lword_t)erric->memory[address] << (sizeof(word_t) * 8) | erric->memory[address + 1]);
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

int write_lword(struct erric_t *erric, lword_t address, lword_t word)
{
	return write_data(erric, address, (uint8_t *) (&word), sizeof(word));
}

int write_data(struct erric_t * erric, lword_t address, uint8_t * data, size_t data_length)
{
	size_t mem_size = sizeof(erric->memory[address]);
	// If data_length is less or equal to data_length, then no additional space is taken.
	size_t max_addr = mem_size > data_length ? 0 : data_length - mem_size;

	if(address > erric->memory_size || address + max_addr > erric->memory_size)
		return 1;

	// Treat the memory as an array of 8-bit values
	uint8_t *memory = (uint8_t*)erric->memory;

	for(int c = 0; c < data_length; ++c)
	{
		memory[(address * mem_size) + c] = data[c];
	}

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
