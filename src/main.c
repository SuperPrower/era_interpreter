#include <stdio.h>
#include <stdlib.h>

// XXX: strcmp is posix!
#include <string.h>

#include "era_interpreter.h"

const char* help =
	"ERA machine code interpreter\n"
	"Usage: ./era [--filename filename] [--memory_size words] [--help]\n"
	"--filename: name of file to read and interpret, default: code.bin\n"
	"--memory_size: size of memory in words, max 2 bil. (4GiB), default: 64k (128KiB)\n"
	"--help: print this message and exit\n"
	"Innopolis University, Fall 2018\n"
	"Sergey Koziakov\n"
	"Alex Gospodchikov\n"
	"Danila Romanov\n";

void simple_mem_dump(struct era_t *era)
{
	FILE *dump = fopen("memdump", "w");

	fprintf(dump, "ERA status: %u\n", era->status_code);

	fprintf(dump, "Registers:\n");
	for(int c = 0; c < 32; ++c)
	{
		if(c == FP)
			fprintf(dump, "R%u (FP): %u\n", c, era->registers[c]);
		else if(c == SP)
			fprintf(dump, "R%u (SP): %u\n", c, era->registers[c]);
		else if(c == SB)
			fprintf(dump, "R%u (SB): %u\n", c, era->registers[c]);
		else if(c == PC)
			fprintf(dump, "R%u (PC): %u\n", c, era->registers[c]);
		else
			fprintf(dump, "R%u: %u\n", c, era->registers[c]);
	}

	fprintf(dump, "Raw memory:\n");

	for(uint32_t c = 0; c < era->memory_size; ++c)
	{
		if (c % 8 == 0)
			fprintf(dump, "\n");
		fprintf(dump, "%04X\t", era->memory[c]);
	}

	fclose(dump);
}

int main(int argc, char *argv[])
{
	// parse arguments
	unsigned long memory_size = 64 * 1024;
	const char* filename = "code.bin";

	if (argc > 1) {
		// parse arguments
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "--help") == 0) {
				printf("%s\n", help);
				return 0;
			} else if (strcmp(argv[i], "--filename") == 0) {
				filename = argv[++i];
			} else if (strcmp(argv[i], "--memory_size") == 0) {
				char * size = argv[++i];
				memory_size = strtoul(size, NULL, 10);
			}

		}

	}

	struct era_t * era = init_era_m(memory_size);
	if (read_file(filename, era) != ERA_STATUS_NONE) {
		return 1;
	}

	execute(era);

	simple_mem_dump(era);

	free_era(era);

	return 0;

	/*
	read_file("test_binaries/v0_simple_ops.bin", era);
	sword_t status = execute(era);
	// 7 is not a mistake here.
	// Word 4 should be 0, Word 5 should be 7 since ST is 32-bit.
	// Word 6 should be zero, so we check it just in case
	for(int c = 0; c < 7; c++)
	{
		printf("Word %u : %u\n", c, read_word(era, c));
	}

	*/
}
