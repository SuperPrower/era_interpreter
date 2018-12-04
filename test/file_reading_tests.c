#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "era_interpreter.h"
#include "logic_operators.h"

static struct era_t * setup_era()
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));
	init_era(era);

	return era;
}

static void remove_era(struct era_t *era)
{
	free_era(era);
	free(era);
}

static void v0_tests(void **state)
{
	struct era_t * era = setup_era();

	sword_t status = read_file("../test_binaries/v0Test.bin", era);

	assert_int_equal(status, ERA_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		if (c == PC)
			assert_int_equal(era->registers[c], 2);
		else if (c == SP)
			assert_int_equal(era->registers[c], 5);
		else
			assert_int_equal(era->registers[c], 0);
	}

	assert_int_equal(read_word(era, 0), 65522);
	assert_int_equal(read_word(era, 1), 65524);
	assert_int_equal(read_word(era, 2), 44508);
	assert_int_equal(read_word(era, 3), 22121);
	assert_int_equal(read_word(era, 4), 63409);
	assert_int_equal(read_word(era, 5), 0);
	// TODO: When memory is fully fleshed-out, check that everything else is 0.

	remove_era(era);
}

static void v1_tests(void **state)
{
	struct era_t * era = setup_era();

	sword_t status = read_file("../test_binaries/v1Test.bin", era);

	assert_int_equal(status, ERA_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		if (c == PC)
			assert_int_equal(era->registers[c], 2);
		else if (c == SP)
			assert_int_equal(era->registers[c], 5);
		else
			assert_int_equal(era->registers[c], 0);
	}

	assert_int_equal(read_word(era, 0), 65522);
	assert_int_equal(read_word(era, 1), 65524);
	assert_int_equal(read_word(era, 2), 44508);
	assert_int_equal(read_word(era, 3), 22121);
	assert_int_equal(read_word(era, 4), 63409);
	assert_int_equal(read_word(era, 5), 0);
	// TODO: When memory is fully fleshed-out, check that everything else is 0.

	remove_era(era);
}

static void exact_comparison_tests(void **state)
{
	// It is possible to get some strange inconsistency errors due to memory allocation
	// For example, registers with seemingly equal contents, like:
	// era->registers[0] = 192
	// era->registers[1] = 192
	// Not be equal due to allocations mis-aligning them in strange ways
	struct era_t * v0_era = setup_era();
	struct era_t * v1_era = setup_era();

	sword_t status = read_file("../test_binaries/v0Test.bin", v0_era);
	assert_int_equal(status, ERA_STATUS_NONE);

	status = read_file("../test_binaries/v1Test.bin", v1_era);
	assert_int_equal(status, ERA_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(v0_era->registers[c], v1_era->registers[c]);
	}

	assert_int_equal(read_word(v0_era, 0), read_word(v1_era, 0));
	assert_int_equal(read_word(v0_era, 1), read_word(v1_era, 1));
	assert_int_equal(read_word(v0_era, 2), read_word(v1_era, 2));
	assert_int_equal(read_word(v0_era, 3), read_word(v1_era, 3));
	assert_int_equal(read_word(v0_era, 4), read_word(v1_era, 4));
	assert_int_equal(read_word(v0_era, 5), read_word(v1_era, 5));
}

int main(void)
{

	const struct CMUnitTest file_reading_tests[] = {
			cmocka_unit_test(v0_tests),
			cmocka_unit_test(v1_tests),
			cmocka_unit_test(exact_comparison_tests),
	};

	return cmocka_run_group_tests_name(
			"File Reading Tests",
			file_reading_tests,
			NULL,
			NULL
	);
}