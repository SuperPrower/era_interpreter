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

//GOTOs in here are responsible and sensible, don't worry about it
uint64_t read_file(char *filename, struct era_t *era)
{
	FILE * executable;
	// 255 is used to make sure invalid reads are detected
	uint8_t version = 255;
	uint64_t status = 0;

	executable = fopen(filename, "rb");
	if(executable == NULL)
	{
		return READ_ERROR_FILE;
	}

	// Get the version
	fread((void*)&version, sizeof(uint8_t), 1, executable);
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

			// Skip the padding
			fseek(executable, 1, SEEK_CUR);
			if(ferror(executable) != 0 || feof(executable) != 0)
			{
				status = READ_ERROR_READ;
				goto cleanup;
			}

			// Load the length
			fread((void*)&length, sizeof(uint32_t), 1, executable);
			if(ferror(executable) != 0 || feof(executable) != 0)
			{
				status = READ_ERROR_READ;
				goto cleanup;
			}

			// Load the static data and the code
			fread((void*) era->memory, sizeof(uint8_t), MEM_SIZE, executable);
			// We CAN get EOF here, but errors are still possible
			if(ferror(executable) != 0)
			{
				status = READ_ERROR_READ;
				goto cleanup;
			}

			// Populate PC
			// I was a bit dumb at first.
			// length relates to the length of data in the global data + code, NOT in the file.
			// We don't need to modify it
			era->registers[PC] = length;
			break;
		}
		default:
			status = READ_ERROR_VERSION;
			goto cleanup;
	}

	// We always have static data at the beginning of memory
	era->registers[SB] = 0;

	cleanup:
	fclose(executable);
	return status;
}
