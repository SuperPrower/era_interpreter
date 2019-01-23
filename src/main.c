#include <stdio.h>
#include <stdlib.h>

// XXX: strcmp is posix!
#include <string.h>

#include "erric_interpreter.h"

const char* help =
	"ERRIC machine code interpreter\n"
	"Usage: ./erric [--filename filename] [--memory_size words] [--help]\n"
	"--filename: name of file to read and interpret, default: code.bin\n"
	"--memory_size: size of memory in words, max 2 bil. (4GiB), default: 64k (128KiB)\n"
	"--help: print this message and exit\n\n"
	"After execution, machine state is dumped to memdump file\n\n"
	"Innopolis University, Fall 2018\n"
	"Sergey Koziakov\n"
	"Alex Gospodchikov\n"
	"Danila Romanov\n";

void simple_mem_dump(struct erric_t *erric)
{
	FILE *dump = fopen("memdump", "w");

	fprintf(dump, "ERRIC status: %u, %s\n", erric->status_code, status_what(erric->status_code));

	fprintf(dump, "Registers:\n");
	for(int c = 0; c < N_REGISTERS; ++c)
	{
		if(c == FP)
			fprintf(dump, "R%u (FP): %u\n", c, erric->registers[c]);
		else if(c == SP)
			fprintf(dump, "R%u (SP): %u\n", c, erric->registers[c]);
		else if(c == SB)
			fprintf(dump, "R%u (SB): %u\n", c, erric->registers[c]);
		else if(c == PC)
			fprintf(dump, "R%u (PC): %u\n", c, erric->registers[c]);
		else
			fprintf(dump, "R%u: %u\n", c, erric->registers[c]);
	}

	fprintf(dump, "Raw memory:\n");

	for(uint32_t c = 0; c < erric->memory_size; ++c)
	{
		if (c % 8 == 0)
			fprintf(dump, "\n");
		fprintf(dump, "%04X\t", erric->memory[c]);
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
				if(memory_size == 0){
					printf("Memory size must be greater than 0");
					return ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS;
				}
			}

		}

	}

	struct erric_t * erric = init_erric_m(memory_size);
	if (read_file(filename, erric) != ERRIC_STATUS_NONE) {
		return ERRIC_STATUS_FILE_ERROR;
	}

	execute(erric);

	simple_mem_dump(erric);

	free_erric(erric);

	return ERRIC_STATUS_NONE;
}
