#include "file_reading.h"

void swap_bytes(uint8_t *bytes, size_t length)
{
	uint8_t temp;
	for(size_t c = 0; c < length / 2; ++c)
	{
		temp = bytes[c];
		bytes[c] = bytes[length - c - 1];
		bytes[length - c - 1] = temp;
	}
}

sword_t read_v0_file(struct erric_t *erric, FILE *executable)
{
	uint32_t length = 0;
	size_t read = 0;

	// Skip the padding
	fseek(executable, 1, SEEK_CUR);
	if (ferror(executable) != 0 || feof(executable) != 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Load the length
	fread((void*)&length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Load the static data and the code
	read = fread((void*) erric->memory, sizeof(word_t), erric->memory_size, executable);
	// We CAN get EOF here, but errors are still possible
	if (ferror(executable) != 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Deal with little-endianness
	if (little_endian() == 1) {
		CHANGE_ENDIAN(length);
		for (size_t c = 0; c < read; ++c) {
			CHANGE_ENDIAN(erric->memory[c]);
		}
	}

	// Populate The needed registers
	// length relates to the length of data in the global data + code, NOT in the file.
	// We don't need to modify it
	erric->registers[PC] = length;
	erric->registers[SP] = read;
	// Other registers are already zero

	return ERRIC_STATUS_NONE;
}

sword_t read_v1_file(struct erric_t *erric, FILE *executable)
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
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Read info about static data
	fread((void*)&data_start, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || data_start == 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	fread((void*)&data_length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || data_length == 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Read info about code
	fread((void*)&code_start, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || code_start == 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	fread((void*)&code_length, sizeof(uint32_t), 1, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || code_length == 0) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Deal with little-endianness
	if (little_endian() == 1) {
		CHANGE_ENDIAN(code_start);
		CHANGE_ENDIAN(code_length);
		CHANGE_ENDIAN(data_start);
		CHANGE_ENDIAN(data_length);
	}

	fseek(executable, data_start, SEEK_SET);
	// Read data into the beginning of the memory
	read = fread(erric->memory, sizeof(word_t), data_length, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || read != data_length) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}


	fseek(executable, code_start, SEEK_SET);
	// Read code right after data into the memory
	read = fread(erric->memory + data_length, sizeof(word_t), code_length, executable);
	if (ferror(executable) != 0 || feof(executable) != 0 || read != code_length) {
		return ERRIC_STATUS_FILE_READ_ERROR;
	}

	// Set the registers to needed values
	erric->registers[PC] = data_length;
	erric->registers[SP] = data_length + code_length;
	// Other registers are already zero

	// Deal with little-endianness
	if (little_endian() == 1) {
		for(size_t c = 0; c < data_length + code_length; ++c) {
			CHANGE_ENDIAN(erric->memory[c]);
		}
	}

	return ERRIC_STATUS_NONE;
}
