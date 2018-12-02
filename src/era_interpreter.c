#include "era_interpreter.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "era_status.h"

// Operations for the step function
#include "branching.h"
#include "logic.h"
#include "memory.h"
#include "operators.h"

typedef sword_t (*era_command)(struct era_t*, sword_t, sword_t, enum format_t);

// The execution array is indexed by the command code. The format is parsed separately.
era_command commands[] = {&nopstop, &ld, &ldaldc, &st, &mov, &add, &sub, &asr, &asl, &or, &and, &xor, &lsl, &lsr, &cnd, &cbr};

int init_era(struct era_t *era)
{
	era->memory = (word_t*) malloc(sizeof(word_t) * MEM_SIZE);
	era->registers = (lword_t*) malloc(sizeof(lword_t) * N_REGISTERS);
	era->status_code = ERA_STATUS_NONE;

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
		return ERA_STATUS_FILE_ERROR;
	}

	// Get the version
	fread((void*)&version, sizeof(uint8_t), 1, executable);
	if(ferror(executable) != 0 || feof(executable) != 0)
	{
		status = ERA_STATUS_FILE_READ_ERROR;
		goto cleanup;
	}

	switch(version)
	{
		case(0):
		{
			status = read_v0_file(era, executable);
			break;
		}
		case 1:
		{
			status = read_v1_file(era, executable);
			break;
		}
		default:
			status = ERA_STATUS_FILE_VERSION_ERROR;
			goto cleanup;
	}

	// We always have static data at the beginning of memory
	era->registers[SB] = 0;

	cleanup:
	fclose(executable);
	return status;
}

sword_t step(struct era_t *era)
{
	word_t command = read_word(era, era->registers[PC]);
	sword_t format = (sword_t) (command >> 14 & 0x3);
	sword_t code = (sword_t)(command >> 10 & 0xF);
	sword_t i = (sword_t)(command >> 5 & 0x1F);
	sword_t j = (sword_t)(command & 0x1F);
	return commands[code](era, i, j, format);
}

sword_t execute(struct era_t *era)
{
	sword_t status = ERA_STATUS_NONE;
	while (status == ERA_STATUS_NONE)
	{
		status = step(era);
		++(era->registers[PC]);
	}
	return status;
}
