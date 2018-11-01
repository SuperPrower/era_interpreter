#include "era_interpreter.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));
	init_era(era);

	size_t bytes_read = read_file("test.bin", era);
	printf("Read %lu bytes\n", (unsigned long)bytes_read);

	free_era(era);
	return 0;
}
