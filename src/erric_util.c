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
	if(address >= erric->memory_size) {
		return 0;
	}
	return (sword_t)(erric->memory[address] & get_mask(F_8_BIT));
}

word_t read_word(struct erric_t *erric, lword_t address)
{
	if(address >= erric->memory_size) {
		return 0;
	}
	return erric->memory[address];
}

lword_t read_lword(struct erric_t *erric, lword_t address)
{
	if(address + 1 >= erric->memory_size) {
		return 0;
	}
	// sizeof(word_t) * 8 returns number of bits
	return (lword_t)((lword_t)erric->memory[address] << (sizeof(word_t) * 8) | erric->memory[address + 1]);
}

lword_t get_mask(enum format_t format)
{
	switch(format) {
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

uint8_t write_lword(struct erric_t *erric, lword_t address, lword_t word)
{
	return write_data(erric, address, (uint8_t *) (&word), sizeof(word));
}

uint8_t write_data(struct erric_t * erric, lword_t address, uint8_t * data, size_t data_length)
{
	size_t mem_size = sizeof(erric->memory[address]);
	// If data_length is less or equal to than mem_size, then no additional space is taken.
	size_t max_addr = data_length <= mem_size ? 0 : data_length / mem_size - 1;

	if(data_length > 1 && data_length % 2 == 1) {
		// Shouldn't happen, but just in case an odd-sized integers are used
		max_addr += 1;
	}

	if(address + max_addr >= erric->memory_size) {
		return 1;
	}

	// Treat the memory as an array of 8-bit values
	uint8_t *memory = (uint8_t*)erric->memory;

	for(int c = 0; c < data_length; ++c) {
		memory[(address * mem_size) + c] = data[c];
	}

	// Under little-endian, we need to reverse the words in order to read it correctly.
	// E.g. 3821823414
	// Bytes(big-endian): E3 CC 65 B6
	// Bytes(little-endian): B6 65 CC E3
	// During direct writing, the words are written as B6 65 and CC E3
	// Upon reversing: CC E3 B6 65
	// Little-endian reads bytes right-to-left in every word, therefore:
	// Word 1 read: E3 CC
	// Word 2 read: 65 B6
	// Which is what we want

	if(little_endian()) {
		for (int c = 0; c < max_addr; ++c) {
			// We can't use a temp var here since we can't know the memory length
			erric->memory[address + c] += erric->memory[address + max_addr - c];
			erric->memory[address + max_addr - c] = erric->memory[address + c] -
					erric->memory[address + max_addr - c];
			erric->memory[address + c] -= erric->memory[address + max_addr - c];
		}
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
