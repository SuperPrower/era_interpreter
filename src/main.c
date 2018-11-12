#include "era_interpreter.h"
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int main(int argc, char *argv[])
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));
	init_era(era);

	//uint64_t bytes_read = read_file("test.bin", era);
	//printf("Read %lu bytes\n", bytes_read);

	read_file("tests/v0Test.bin", era);
	printf("%u", read_lword(era, 2));

	free_era(era);
	return 0;
}
