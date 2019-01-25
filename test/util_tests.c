#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"
#include "branch_operators.h"

static int setup_util_tests(void **state)
{
	*state = init_erric_m(128);

	return 0;
}

static int teardown_util_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	free_erric(erric);

	return 0;
}

static void write_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	// Basic tests
	// 11100011 11001100 01100101 10110110
	lword_t x = 3821823414;
	ret = write_data(erric, 10, (uint8_t*)&x, 1);
	assert_int_equal(erric->memory[10], 182);
	assert_int_equal(ret, 0);

	ret = write_data(erric, 10, (uint8_t*)&x, 2);
	assert_int_equal(erric->memory[10], 26038);
	assert_int_equal(ret, 0);

	ret = write_data(erric, 10, (uint8_t*)&x, 4);
	if(little_endian()) {
		assert_int_equal(erric->memory[10], 26038);
		assert_int_equal(erric->memory[11], 58316);
	} else {
		assert_int_equal(erric->memory[10], 58316);
		assert_int_equal(erric->memory[11], 26038);
	}
	assert_int_equal(ret, 0);

	// Edge cases
	// Writing at the beginning
	ret = write_data(erric, 0, (uint8_t*)&x, 1);
	assert_int_equal(erric->memory[0], 182);
	assert_int_equal(ret, 0);

	// Writing close to/at the end
	ret = write_data(erric, 127, (uint8_t*)&x, 1);
	assert_int_equal(erric->memory[127], 182);
	assert_int_equal(ret, 0);

	ret = write_data(erric, 126, (uint8_t*)&x, 4);
	if(little_endian()) {
		assert_int_equal(erric->memory[126], 26038);
		assert_int_equal(erric->memory[127], 58316);
	} else {
		assert_int_equal(erric->memory[126], 58316);
		assert_int_equal(erric->memory[127], 26038);
	}
	assert_int_equal(ret, 0);

	// Negative cases
	// Trying to write too much
	ret = write_data(erric, 127, (uint8_t*)&x, 4);
	if(little_endian()) {
		assert_int_equal(erric->memory[126], 26038);
		assert_int_equal(erric->memory[127], 58316);
	} else {
		assert_int_equal(erric->memory[126], 58316);
		assert_int_equal(erric->memory[127], 26038);
	}
	assert_int_equal(ret, 1);

	// Trying to write past memory
	ret = write_data(erric, 128, (uint8_t*)&x, 1);
	if(little_endian()) {
		assert_int_equal(erric->memory[126], 26038);
		assert_int_equal(erric->memory[127], 58316);
	} else {
		assert_int_equal(erric->memory[126], 58316);
		assert_int_equal(erric->memory[127], 26038);
	}
	assert_int_equal(ret, 1);
}

static void read_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	lword_t ret;

	// Basic cases
	// 11100011 11001100 01100101 10110110
	lword_t x = 3821823414;
	write_data(erric, 0, (uint8_t*)&x, 4);
	ret = read_sword(erric, 0);
	assert_int_equal(ret, 182);

	ret = read_word(erric, 0);
	if(little_endian()) {
		assert_int_equal(ret, 26038);
	} else {
		assert_int_equal(ret, 58316);
	}

	ret = read_lword(erric, 0);
	assert_int_equal(ret, 3821823414);

	// Negative cases
	// Trying to read too much
	ret = read_lword(erric, 127);
	assert_int_equal(ret, 0);

	// Trying to read past memory
	ret = read_word(erric, 128);
	assert_int_equal(ret, 0);
}

int main(void)
{

	const struct CMUnitTest util_tests[] = {
			cmocka_unit_test(write_tests),
			cmocka_unit_test(read_tests)
	};

	return cmocka_run_group_tests_name(
			"ERRIC Utility Tests",
			util_tests,
			setup_util_tests,
			teardown_util_tests
	);
}
