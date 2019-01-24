#include "erric_interpreter.h"

#include <stdlib.h>
#include "file_reading.h"

// Include the operations for the step function
#include "branch_operators.h"
#include "logic_operators.h"
#include "memory_operators.h"
#include "math_operators.h"

#define ERRIC_DEFAULT_MEM_SIZE 64 * 1024

#define LAST_2_BITS 0x3
#define LAST_4_BITS 0xF
#define LAST_5_BITS 0x1F

// Type of the instruction function pointer
typedef sword_t (*erric_instruction)(struct erric_t*, sword_t, sword_t, enum format_t);

// The execution array is indexed by the command code. The format is parsed separately.
erric_instruction instructions[] = {&nopstop, &ld, &ldaldc, &st, &mov, &add, &sub, &asr, &asl, &or, &and, &xor, &lsl, &lsr, &cnd, &cbr};


struct erric_t* init_erric()
{
	return init_erric_m(ERRIC_DEFAULT_MEM_SIZE);
}

struct erric_t* init_erric_m(uint32_t _mem_size)
{
	struct erric_t * erric = (struct erric_t *) malloc(sizeof(struct erric_t));

	erric->memory_size = _mem_size;

	// Calloc clears everything to zero, which should be good for us
	erric->memory = (word_t*) calloc(erric->memory_size, sizeof(word_t));
	erric->registers = (lword_t*) calloc(N_REGISTERS, sizeof(lword_t));
	erric->status_code = ERRIC_STATUS_NONE;

	return erric;
}

int free_erric(struct erric_t * erric)
{
	free(erric->memory);
	free(erric->registers);
	free(erric);

	return 0;
}

//GOTOs in here are responsible and sensible, so no need to worry about it
sword_t read_file(const char *filename, struct erric_t *erric)
{
	FILE * executable;
	sword_t status = ERRIC_STATUS_NONE;
	// NOTE : header fields are independent from words and stuff and have fixed bit size
	// 255 is used to make sure invalid reads are detected
	uint8_t version = 255;

	executable = fopen(filename, "rb");

	if(executable == NULL)
	{
		return ERRIC_STATUS_FILE_ERROR;
	}

	// Get the version
	fread((void*)&version, sizeof(uint8_t), 1, executable);
	if(ferror(executable) != 0 || feof(executable) != 0)
	{
		status = ERRIC_STATUS_FILE_READ_ERROR;
		goto cleanup;
	}

	switch(version)
	{
		case(0):
		{
			status = read_v0_file(erric, executable);
			break;
		}
		case 1:
		{
			status = read_v1_file(erric, executable);
			break;
		}
		default:
			status = ERRIC_STATUS_FILE_VERSION_ERROR;
			goto cleanup;
	}

	cleanup:
	fclose(executable);
	return status;
}

struct instruction_t parse_instruction(word_t instruction)
{
	struct instruction_t out;
	sword_t format_code = (sword_t) (instruction >> 14 & LAST_2_BITS);

	out.code = (sword_t)(instruction >> 10 & LAST_4_BITS);
	out.i = (sword_t)(instruction >> 5 & LAST_5_BITS);
	out.j = (sword_t)(instruction & LAST_5_BITS);

	switch(format_code)
	{
		case 0:
			out.format = F_8_BIT;
			break;
		case 1:
			out.format = F_16_BIT;
			break;
		case 3:
			out.format = F_32_BIT;
			break;
		default:
			break;
	}

	return out;
}

sword_t step(struct erric_t *erric)
{
	word_t command = read_word(erric, erric->registers[PC]);

	struct instruction_t instruction = parse_instruction(command);

	++(erric->registers[PC]);
	return instructions[instruction.code](erric, instruction.i, instruction.j, instruction.format);
}

sword_t execute(struct erric_t *erric)
{
	while (erric->status_code == ERRIC_STATUS_NONE)
	{
		erric->status_code = step(erric);
	}
	return erric->status_code;
}
