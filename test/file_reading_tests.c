#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"
#include "logic_operators.h"

static struct erric_t * setup_erric()
{
	return init_erric();
}

static void remove_erric(struct erric_t * erric)
{
	free_erric(erric);
}

static void v0_tests(void **state)
{
	struct erric_t * erric = setup_erric();

	sword_t status = read_file("../test_binaries/v0Test.bin", erric);

	assert_int_equal(status, ERRIC_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		if (c == PC)
			assert_int_equal(erric->registers[c], 2);
		else if (c == SP)
			assert_int_equal(erric->registers[c], 5);
		else
			assert_int_equal(erric->registers[c], 0);
	}

	assert_int_equal(read_word(erric, 0), 65522);
	assert_int_equal(read_word(erric, 1), 65524);
	assert_int_equal(read_word(erric, 2), 44508);
	assert_int_equal(read_word(erric, 3), 22121);
	assert_int_equal(read_word(erric, 4), 63409);
	assert_int_equal(read_word(erric, 5), 0);

	remove_erric(erric);
}

static void v1_tests(void **state)
{
	struct erric_t * erric = setup_erric();

	sword_t status = read_file("../test_binaries/v1Test.bin", erric);

	assert_int_equal(status, ERRIC_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		if (c == PC)
			assert_int_equal(erric->registers[c], 2);
		else if (c == SP)
			assert_int_equal(erric->registers[c], 5);
		else
			assert_int_equal(erric->registers[c], 0);
	}

	assert_int_equal(read_word(erric, 0), 65522);
	assert_int_equal(read_word(erric, 1), 65524);
	assert_int_equal(read_word(erric, 2), 44508);
	assert_int_equal(read_word(erric, 3), 22121);
	assert_int_equal(read_word(erric, 4), 63409);
	assert_int_equal(read_word(erric, 5), 0);

	remove_erric(erric);
}

static void exact_comparison_tests(void **state)
{
	// It is possible to get some strange inconsistency errors due to memory allocation
	// For example, registers with seemingly equal contents, like:
	// erric->registers[0] = 192
	// erric->registers[1] = 192
	// Not be equal due to allocations mis-aligning them in strange ways
	struct erric_t * v0_erric = setup_erric();
	struct erric_t * v1_erric = setup_erric();

	sword_t status = read_file("../test_binaries/v0Test.bin", v0_erric);
	assert_int_equal(status, ERRIC_STATUS_NONE);

	status = read_file("../test_binaries/v1Test.bin", v1_erric);
	assert_int_equal(status, ERRIC_STATUS_NONE);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(v0_erric->registers[c], v1_erric->registers[c]);
	}

	assert_int_equal(read_word(v0_erric, 0), read_word(v1_erric, 0));
	assert_int_equal(read_word(v0_erric, 1), read_word(v1_erric, 1));
	assert_int_equal(read_word(v0_erric, 2), read_word(v1_erric, 2));
	assert_int_equal(read_word(v0_erric, 3), read_word(v1_erric, 3));
	assert_int_equal(read_word(v0_erric, 4), read_word(v1_erric, 4));
	assert_int_equal(read_word(v0_erric, 5), read_word(v1_erric, 5));
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