#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"
#include "branch_operators.h"

static int setup_branch_tests(void **state)
{
	*state = init_erric();

	return 0;
}

static int teardown_branch_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	free_erric(erric);

	return 0;
}

static void cnd_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	// Byte comparison test
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	ret = cnd(erric, 0, 1, F_8_BIT);
	// CNDed = 00010100 01010010 01011101 10110010
	assert_int_equal(erric->registers[1], 340942258);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// 00010100 01010010 01011101 10110011 = 23987
	erric->registers[1] = 340942259;
	ret = cnd(erric, 0, 1, F_16_BIT);
	// CNDed = 00010100 01010010 01011101 10110001
	assert_int_equal(erric->registers[1], 340942257);
	assert_int_equal(ret, ERRIC_STATUS_NONE);


	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	ret = cnd(erric, 0, 1, F_32_BIT);
	// CNDed = 00010100 01010010 01011101 10110001
	assert_int_equal(erric->registers[1], 340942257);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Simple comparison tests
	erric->registers[0] = 10;

	erric->registers[1] = 10;
	ret = cnd(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[1], 4);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	erric->registers[1] = 5;
	ret = cnd(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[1], 1);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	erric->registers[1] = 15;
	ret = cnd(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[1], 2);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative Test: Bad Registers
	ret = cnd(erric, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);
}

static void cbr_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	erric->registers[PC] = 20;
	erric->registers[0] = 10;
	erric->registers[1] = 5;
	ret = cbr(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[0], 20);
	assert_int_equal(erric->registers[PC], 5);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	erric->registers[PC] = 20;
	erric->registers[0] = 0;
	erric->registers[1] = 5;
	ret = cbr(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[0], 0);
	assert_int_equal(erric->registers[PC], 20);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative Test: Bad Format
	ret = cbr(erric, 0, 0, F_8_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_FORMAT);

	// Negative Test: Bad Registers
	ret = cbr(erric, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);

	// Negative Test: Out of Memory Bounds
	erric->registers[0] = 1;
	erric->registers[1] = erric->memory_size;
	ret = cbr(erric, 0, 1, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS);
}

static void nop_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		erric->registers[c] = 0;
	}
	for(int c = 0; c < 10; ++c)
	{
		erric->registers[c] = 0;
	}

	sword_t status = nop(erric, 0, 1, F_16_BIT);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(erric->registers[c], 0);
	}

	// Small memory check
	for(int c = 0; c < 10; ++c)
	{
		assert_int_equal(erric->memory[c], 0);
	}

	assert_int_equal(status, ERRIC_STATUS_NONE);

	status = nop(erric, 0, 1, F_32_BIT);
	assert_int_equal(status, ERRIC_STATUS_WRONG_FORMAT);
}

static void stop_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		erric->registers[c] = 0;
	}
	for(int c = 0; c < 10; ++c)
	{
		erric->registers[c] = 0;
	}

	sword_t status = stop(erric, 0, 1, F_8_BIT);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(erric->registers[c], 0);
	}

	// Small memory check
	for(int c = 0; c < 10; ++c)
	{
		assert_int_equal(erric->memory[c], 0);
	}

	assert_int_equal(status, ERRIC_STATUS_STOP);

	status = stop(erric, 0, 0, F_32_BIT);
	assert_int_equal(status, ERRIC_STATUS_WRONG_FORMAT);
}

int main(void)
{

	const struct CMUnitTest branch_tests[] = {
			cmocka_unit_test(cnd_tests),
			cmocka_unit_test(cbr_tests),
			cmocka_unit_test(nop_tests),
			cmocka_unit_test(stop_tests)
	};

	return cmocka_run_group_tests_name(
			"Branch Operators Tests",
			branch_tests,
			setup_branch_tests,
			teardown_branch_tests
	);
}
