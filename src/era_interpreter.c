#include "era_interpreter.h"

#include <stdio.h>
#include <stdlib.h>

int init_era(struct era_t *era)
{
	era->memory = (uint16_t*) malloc(sizeof(uint16_t) * MEM_SIZE);
	era->registers = (uint16_t*) malloc(sizeof(uint16_t) * N_REGISTERS);

	return 0;
}

int free_era(struct era_t *era)
{
	free(era->memory);
	free(era->registers);

	return 0;
}

size_t read_file(char *filename, struct era_t *era)
{
	FILE * executable;
	executable = fopen(filename, "rb");

	size_t bytes_read = fread((void*) era->memory, sizeof(uint8_t), MEM_SIZE, executable);

	fclose(executable);
	return bytes_read;
}
