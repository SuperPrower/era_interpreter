#include "era_interpreter.h"

#include <stdio.h>
#include <stdlib.h>

// Sizes are in bytes
#define HEADER_V1_SIZE 6

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

//GOTOs in here are responsible and sensible, don't worry about it
uint64_t read_file(char *filename, struct era_t *era)
{
	FILE * executable;
	uint8_t version = 0;
	uint64_t status = 0;
	executable = fopen(filename, "rb");

	if(executable == NULL)
	{
		return READ_ERROR_FILE;
	}

	fread((void*)version, sizeof(uint8_t), 1, executable);

	if(ferror(executable) != 0 || feof(executable) != 0)
	{
		status = READ_ERROR_READ;
		goto cleanup;
	}

	switch(version)
	{
		case(0):
		{
			uint32_t length = 0;
			fread((void*)length, sizeof(uint32_t), 1, executable);
			if(ferror(executable) != 0 || feof(executable) != 0)
			{
				status = READ_ERROR_READ;
				goto cleanup;
			}
			era->registers[PC] = (length + HEADER_V1_SIZE) / 2;
			fread((void*) era->memory, sizeof(uint8_t), MEM_SIZE, executable);
			// We CAN get EOF here, but errors are still possible
			if(ferror(executable) != 0)
			{
				status = READ_ERROR_READ;
				goto cleanup;
			}
			break;
		}
		default:
			status = READ_ERROR_VERSION;
			goto cleanup;
	}

	cleanup:
	fclose(executable);
	return status;
}
