#include "file_reading.h"

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

word_t swap_word(word_t word)
{
	return (word_t)(((word & get_mask(F_8_BIT)) << 8) + ((word >> 8) & get_mask(F_8_BIT)));
}

lword_t swap_lword(lword_t word)
{
	sword_t p1, p2, p3, p4;
	p1 = word & get_mask(F_8_BIT);
	p2 = (word >> 8) & get_mask(F_8_BIT);
	p3 = (word >> 16) & get_mask(F_8_BIT);
	p4 = (word >> 24) & get_mask(F_8_BIT);
	return (lword_t)((p1 << 24) + (p2 << 16) + (p3 << 8) + p4);
}

sword_t read_v0_file(struct era_t *era, FILE *executable)
{
	uint32_t length = 0;
	size_t read = 0;

	// Skip the padding
	fseek(executable, 1, SEEK_CUR);
	if (ferror(executable) != 0 || feof(executable) != 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Load the length
	fread((void*)&length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Load the static data and the code
	read = fread((void*) era->memory, sizeof(word_t), era->memory_size, executable);
	// We CAN get EOF here, but errors are still possible
	if (ferror(executable) != 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Deal with little-endianness
	if (little_endian() == 1) {
		length = swap_lword(length);
		for (size_t c = 0; c < read; ++c) {
			era->memory[c] = swap_word(era->memory[c]);
		}
	}

	// Populate The needed registers
	// length relates to the length of data in the global data + code, NOT in the file.
	// We don't need to modify it
	era->registers[PC] = length;
	era->registers[SP] = read;
	// Other registers are already zero

	return ERA_STATUS_NONE;
}

sword_t read_v1_file(struct era_t *era, FILE *executable)
{
	// Data start offset from the start in bytes
	uint32_t data_start;
	// Data length in words
	uint32_t data_length;
	// Code start offset from the start in bytes
	uint32_t code_start;
	// Data length in words
	uint32_t code_length;

	// Number of words read
	size_t read;

	// Skip the padding
	fseek(executable, 1, SEEK_CUR);
	if (ferror(executable) != 0 || feof(executable) != 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Read info about static data
	fread((void*)&data_start, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || data_start == 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	fread((void*)&data_length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || data_length == 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Read info about code
	fread((void*)&code_start, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || code_start == 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	fread((void*)&code_length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || code_length == 0) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Deal with little-endianness
	if (little_endian() == 1) {
		code_start = swap_lword(code_start);
		code_length = swap_lword(code_length);
		data_start = swap_lword(data_start);
		data_length = swap_lword(data_length);
	}

	fseek(executable, data_start, SEEK_SET);
	// Read data into the beginning of the memory
	read = fread(era->memory, sizeof(word_t), data_length, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || read != data_length) {
		return ERA_STATUS_FILE_READ_ERROR;
	}


	fseek(executable, code_start, SEEK_SET);
	// Read code right after data into the memory
	read = fread(era->memory + data_length, sizeof(word_t), code_length, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || read != code_length) {
		return ERA_STATUS_FILE_READ_ERROR;
	}

	// Set the registers to needed values
	era->registers[PC] = data_length;
	era->registers[SP] = data_length + code_length;
	// Other registers are already zero

	// Deal with little-endianness
	if (little_endian() == 1) {
		for(size_t c = 0; c < data_length + code_length; ++c) {
			era->memory[c] = swap_word(era->memory[c]);
		}
	}

	return ERA_STATUS_NONE;
}
