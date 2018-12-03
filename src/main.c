#include "era_interpreter.h"
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int main(int argc, char *argv[])
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));

	init_era(era);
	read_file("test_binaries/v0Test.bin", era);
	// 6 is not a mistake here. Word 5 should be zero, so we check it just in case
	for(int c = 0; c < 6; c++)
	{
		printf("Word %u : %u\n", c, read_word(era, c));
	}
	for(int c = 0; c < 32; c++)
	{
		printf("R%u : %u\n", c, era->registers[c]);
	}
	free_era(era);

	printf("\n");

	init_era(era);
	read_file("test_binaries/v1Test.bin", era);
	// 6 is not a mistake here. Word 5 should be zero, so we check it just in case
	for(int c = 0; c < 6; c++)
	{
		printf("Word %u : %u\n", c, read_word(era, c));
	}
	for(int c = 0; c < 32; c++)
	{
		printf("R%u : %u\n", c, era->registers[c]);
	}
	free_era(era);

	return 0;
}
