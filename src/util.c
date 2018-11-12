#include "util.h"

#include <stdlib.h>

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

int write_lword(struct era_t *era, lword_t address, lword_t word)
{
	// TODO: Add dynamic memory sizing
	if(address > MEM_SIZE || address + 1 > MEM_SIZE)
		return 1;

	era->memory[address] = (word_t)((word >> 16) & 0xffff);
	era->memory[address + 1] = (word_t)(word & 0xffff);

	return 0;
}

uint8_t little_endian()
{
	// Little-endian:
	// 01 00
	// Big endian:
	// 00 01
	// Therfore, 1 will be read on little-endian and 0 on big-endian
	uint16_t x = 1;
	return *(uint8_t *) &x;
}

word_t swap_word(word_t word)
{
	return (word_t)(((word & 255) << 8) + ((word >> 8) & 255));
}

lword_t swap_lword(lword_t word)
{
	sword_t p1, p2, p3, p4;
	p1 = word & 255;
	p2 = (word >> 8) & 255;
	p3 = (word >> 16) & 255;
	p4 = (word >> 24) & 255;
	return (lword_t)((p1 << 24) + (p2 << 16) + (p3 << 8) + p4);
}
