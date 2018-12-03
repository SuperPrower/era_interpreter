#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "era_interpreter.h"
#include "math_operators.h"
#include "era_util.h"

/*
 * Bunch of tests on math operators
 *
 * read more about writing tests at https://api.cmocka.org/group__cmocka__exec.html
 */


/* loads binary file for mathematical operations test */
static int setup_math_tests(void **state)
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));
	init_era(era);

	*state = era;

	return 0;
}

static int teardown_math_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	free_era(era);
	free(era);

	return 0;
}

static void format_8_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// ADD test
	era->registers[0] = 5;
	era->registers[1] = 3;
	add(era, 1, 0, F_8_BIT);
	assert_int_equal(era->registers[0], 8);

	// ADD test with negative numbers
	era->registers[0] = 5;
	era->registers[1] = reg_put(F_8_BIT, -4);
	add(era, 1, 0, F_8_BIT);
	assert_int_equal(era->registers[0], 1);

	// SUB test
	era->registers[0] = 9;
	era->registers[1] = 2;
	sub(era, 1, 0, F_8_BIT);
	assert_int_equal(era->registers[0], 7);

	// SUB test with negative numbers and result
	era->registers[0] = reg_put(F_8_BIT, -6);
	era->registers[1] = reg_put(F_8_BIT, -4);
	sub(era, 1, 0, F_8_BIT);
	assert_int_equal(reg_get(F_8_BIT, era->registers[0]), -2);

	// ASR test
	era->registers[0] = 5;
	asr(era, 0, 0, F_8_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_8_BIT, era->registers[0]), 2);

	// ASR test with negative numbers
	// put -3 in there, but as a 8-bit 2th complement, not 32-bit
	era->registers[0] = reg_put(F_8_BIT, -3);
	asr(era, 0, 0, F_8_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_8_BIT, era->registers[0]), -66);

	// ASL test
	era->registers[0] = reg_put(F_8_BIT, 5);
	asl(era, 0, 0, F_8_BIT);
	assert_int_equal(reg_get(F_8_BIT, era->registers[0]), 10);

	// ASL test with negative numbers
	era->registers[0] = reg_put(F_8_BIT, -5);
	asl(era, 0, 0, F_8_BIT);
	assert_int_equal(reg_get(F_8_BIT, era->registers[0]), -10);
}

static void format_16_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// ADD test
	era->registers[0] = 5;
	era->registers[1] = 3;
	add(era, 1, 0, F_16_BIT);
	assert_int_equal(era->registers[0], 8);

	// ADD test with negative numbers
	era->registers[0] = 5;
	era->registers[1] = reg_put(F_16_BIT, -4);
	add(era, 1, 0, F_16_BIT);
	assert_int_equal(era->registers[0], 1);

	// SUB test
	era->registers[0] = 9;
	era->registers[1] = 2;
	sub(era, 1, 0, F_16_BIT);
	assert_int_equal(era->registers[0], 7);

	// SUB test with negative numbers and result
	era->registers[0] = -6;
	era->registers[1] = reg_put(F_16_BIT, -4);
	sub(era, 1, 0, F_16_BIT);
	assert_int_equal(reg_get(F_16_BIT, era->registers[0]), -2);

	// ASR test
	era->registers[0] = 513;
	asr(era, 0, 0, F_16_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_16_BIT, era->registers[0]), 256);

	// ASR test with negative numbers
	era->registers[0] = reg_put(F_16_BIT, -513);
	asr(era, 0, 0, F_16_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_16_BIT, era->registers[0]), -16641);

	// ASL test
	era->registers[0] = reg_put(F_16_BIT, 5);
	asl(era, 0, 0, F_16_BIT);
	assert_int_equal(reg_get(F_16_BIT, era->registers[0]), 10);

	// ASL test with negative numbers
	era->registers[0] = reg_put(F_16_BIT, -5);
	asl(era, 0, 0, F_16_BIT);
	assert_int_equal(reg_get(F_16_BIT, era->registers[0]), -10);

}

static void format_32_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// ADD test
	era->registers[0] = 70420;
	era->registers[1] = 80310;
	add(era, 1, 0, F_32_BIT);
	assert_int_equal(era->registers[0], 150730);

	// ADD test with negative numbers
	era->registers[0] = 5;
	era->registers[1] = reg_put(F_32_BIT, -4);
	add(era, 1, 0, F_32_BIT);
	assert_int_equal(era->registers[0], 1);

	// SUB test
	era->registers[0] = 9;
	era->registers[1] = 2;
	sub(era, 1, 0, F_32_BIT);
	assert_int_equal(era->registers[0], 7);

	// SUB test with negative numbers and result
	era->registers[0] = -6;
	era->registers[1] = reg_put(F_32_BIT, -4);
	sub(era, 1, 0, F_32_BIT);
	assert_int_equal(reg_get(F_32_BIT, era->registers[0]), -2);

	// ASR test
	era->registers[0] = 3221337;
	asr(era, 0, 0, F_32_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_32_BIT, era->registers[0]), 1610668);

	// ASR test with negative numbers
	era->registers[0] = reg_put(F_32_BIT, -3221337);
	asr(era, 0, 0, F_32_BIT);
	// don't forget proper retrieval to avoid incorrect type conversion
	assert_int_equal(reg_get(F_32_BIT, era->registers[0]), (int32_t)(-1075352493));

	// ASL test
	era->registers[0] = reg_put(F_32_BIT, 3221337);
	asl(era, 0, 0, F_32_BIT);
	assert_int_equal(reg_get(F_32_BIT, era->registers[0]), 6442674);

	// ASL test with negative numbers
	era->registers[0] = reg_put(F_32_BIT, -3221337);
	asl(era, 0, 0, F_32_BIT);
	assert_int_equal(reg_get(F_32_BIT, era->registers[0]), -6442674);

}

int main(void)
{

	const struct CMUnitTest math_tests[] = {
		cmocka_unit_test(format_8_tests),
		cmocka_unit_test(format_16_tests),
		cmocka_unit_test(format_32_tests),
	};

	return cmocka_run_group_tests_name(
			"Mathematical Operators Tests",
			math_tests,
			setup_math_tests,
			teardown_math_tests
		);
}
