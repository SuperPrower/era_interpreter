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
	if (read_file(filename, era) != 0) {
		return 1;
	}

	sword_t status = execute(era);

	for(int c = 0; c < 32; c++)
	{
		printf("R%u : %u\n", c, era->registers[c]);
	}
	printf("Final status: %u\n", status);
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
