#include <stdio.h>
#include <stdlib.h>

#include "era_interpreter.h"

int main(int argc, char *argv[])
{
	struct era_t * era = init_era();
	read_file("test_binaries/v0_simple_ops.bin", era);
	sword_t status = execute(era);
	// 7 is not a mistake here.
	// Word 4 should be 0, Word 5 should be 7 since ST is 32-bit.
	// Word 6 should be zero, so we check it just in case
	for(int c = 0; c < 7; c++)
	{
		printf("Word %u : %u\n", c, read_word(era, c));
	}
	for(int c = 0; c < 32; c++)
	{
		printf("R%u : %u\n", c, era->registers[c]);
	}
	printf("Final status: %u\n", status);
	free_era(era);

	return 0;
}
