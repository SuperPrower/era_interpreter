#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "era_interpreter.h"
#include "math_operators.h"

/*
 * Bunch of tests on math operators
 *
 * read more about writing tests at https://api.cmocka.org/group__cmocka__exec.html
 */


/* loads binary file for mathematical operations test */
static int setup_math_tests(void **state)
{
	*state = init_era();

	return 0;
}

static int teardown_math_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	free_era(era);

	return 0;
}

static void add_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	add(era, 0, 1, F_8_BIT);
	// ADDed = 00000000 00000000 00000000 10111110
	assert_int_equal(era->registers[1], 190);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	add(era, 0, 1, F_16_BIT);
	// ADDed = 00000000 00000000 01000010 10111110
	assert_int_equal(era->registers[1], 17086);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	add(era, 0, 1, F_32_BIT);
	// ADDed = 10111111 00100001 01000010 10111110
	assert_int_equal(era->registers[1], 3206628030);
}

static void add_overflow_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00010100 01010010 01011101 11111111
	era->registers[1] = 340942335;
	add(era, 0, 1, F_8_BIT);
	// ADDed = 00000000 00000000 00000000 00001010
	assert_int_equal(era->registers[1], 10);

	// 00010100 01010010 11111111 11111111
	era->registers[1] = 340983807;
	add(era, 0, 1, F_16_BIT);
	// ADDed = 00000000 00000000 11100101 00001010
	assert_int_equal(era->registers[1], 58634);

	// 11111111 11111111 11111111 11111111
	era->registers[1] = 4294967295;
	add(era, 0, 1, F_32_BIT);
	// ADDed = 10101010 11001110 11100101 00001010
	assert_int_equal(era->registers[1], 2865685770);
}

static void sub_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	sub(era, 0, 1, F_8_BIT);
	// SUBed = 00000000 00000000 00000000 10101000
	assert_int_equal(era->registers[1], 168);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	sub(era, 0, 1, F_16_BIT);
	// SUBed = 00000000 00000000 01111000 10101000
	assert_int_equal(era->registers[1], 30888);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	sub(era, 0, 1, F_32_BIT);
	// SUBed = 01101001 10000011 01111000 10101000
	assert_int_equal(era->registers[1], 1770223784);
}

static void asr_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asr(era, 0, 1, F_8_BIT);
	// ASRed = 00000000 00000000 00000000 00000101
	assert_int_equal(era->registers[1], 5);

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asr(era, 0, 1, F_16_BIT);
	// ASRed = 00000000 00000000 10110010 10000101
	assert_int_equal(era->registers[1], 45701);

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asr(era, 0, 1, F_32_BIT);
	// ASRed = 10010101 01100111 01110010 10000101
	assert_int_equal(era->registers[1], 2506584709);
}

static void asl_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asl(era, 0, 1, F_8_BIT);
	// ASLed = 00000000 00000000 00000000 00010110
	assert_int_equal(era->registers[1], 22);

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asl(era, 0, 1, F_16_BIT);
	// ASLed = 00000000 00000000 11001010 00010110
	assert_int_equal(era->registers[1], 51734);

	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	asl(era, 0, 1, F_32_BIT);
	// ASLed = 11010101 10011101 11001010 00010110
	assert_int_equal(era->registers[1], 3583887894);
}

int main(void)
{

	const struct CMUnitTest math_tests[] = {
		cmocka_unit_test(add_tests),
		cmocka_unit_test(add_overflow_tests),
		cmocka_unit_test(sub_tests),
		cmocka_unit_test(asr_tests),
		cmocka_unit_test(asl_tests)
	};

	return cmocka_run_group_tests_name(
			"Mathematical Operators Tests",
			math_tests,
			setup_math_tests,
			teardown_math_tests
		);
}
