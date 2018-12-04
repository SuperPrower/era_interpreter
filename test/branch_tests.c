#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "era_interpreter.h"
#include "branch_operators.h"

static int setup_branch_tests(void **state)
{
	*state = init_era();

	return 0;
}

static int teardown_branch_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	free_era(era);

	return 0;
}

static void cnd_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// Byte comparison test
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	cnd(era, 0, 1, F_8_BIT);
	// CNDed = 00010100 01010010 01011101 10110001
	assert_int_equal(era->registers[1], 340942257);

	// 00010100 01010010 01011101 10110011 = 23987
	era->registers[1] = 340942259;
	cnd(era, 0, 1, F_16_BIT);
	// CNDed = 00010100 01010010 01011101 10110010
	assert_int_equal(era->registers[1], 340942258);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	cnd(era, 0, 1, F_32_BIT);
	// CNDed = 00010100 01010010 01011101 10110010
	assert_int_equal(era->registers[1], 340942258);

	// Simple comparison tests
	era->registers[0] = 10;

	era->registers[1] = 10;
	cnd(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[1], 4);

	era->registers[1] = 5;
	cnd(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[1], 2);

	era->registers[1] = 15;
	cnd(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[1], 1);
}

static void cbr_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	era->registers[PC] = 20;
	era->registers[0] = 10;
	era->registers[1] = 5;
	cbr(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[0], 20);
	assert_int_equal(era->registers[PC], 5);

	era->registers[PC] = 20;
	era->registers[0] = 0;
	era->registers[1] = 5;
	cbr(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[0], 0);
	assert_int_equal(era->registers[PC], 20);
}

static void nop_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		era->registers[c] = 0;
	}
	for(int c = 0; c < 10; ++c)
	{
		era->registers[c] = 0;
	}

	sword_t status = nop(era, 0, 1, F_16_BIT);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(era->registers[c], 0);
	}

	// Small memory check
	for(int c = 0; c < 10; ++c)
	{
		assert_int_equal(era->memory[c], 0);
	}

	assert_int_equal(status, ERA_STATUS_NONE);
}

static void stop_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		era->registers[c] = 0;
	}
	for(int c = 0; c < 10; ++c)
	{
		era->registers[c] = 0;
	}

	sword_t status = stop(era, 0, 1, F_8_BIT);

	for(int c = 0; c < N_REGISTERS; ++c)
	{
		assert_int_equal(era->registers[c], 0);
	}

	// Small memory check
	for(int c = 0; c < 10; ++c)
	{
		assert_int_equal(era->memory[c], 0);
	}

	assert_int_equal(status, ERA_STATUS_STOP);
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