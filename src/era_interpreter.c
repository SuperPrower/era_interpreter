#include "era_interpreter.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int init_era(struct era_t *era)
{
	era->memory = (word_t*) malloc(sizeof(word_t) * MEM_SIZE);
	era->registers = (lword_t*) malloc(sizeof(lword_t) * N_REGISTERS);

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
	// NOTE : header fields are independent from words and stuff and have fixed bit size
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
			status = read_v0_file(era, executable);
		}
		case 1:
		{
			status = read_v1_file(era, executable);
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
