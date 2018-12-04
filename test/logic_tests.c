#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "era_interpreter.h"
#include "logic_operators.h"

static int setup_logic_tests(void **state)
{
	struct era_t * era = (struct era_t *) malloc(sizeof(struct era_t));
	init_era(era);

	*state = era;

	return 0;
}

static int teardown_logic_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	free_era(era);
	free(era);

	return 0;
}

static void or_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	or(era, 0, 1, F_8_BIT);
	// ORed = 00010100 01010010 01011101 10111011
	assert_int_equal(era->registers[1], 340942267);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	or(era, 0, 1, F_16_BIT);
	// ORed = 00010100 01010010 11111101 10111011
	assert_int_equal(era->registers[1], 340983227);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	or(era, 0, 1, F_32_BIT);
	// ORed = 10111110 11011110 11111101 10111011
	assert_int_equal(era->registers[1], 3202284987);
}

static void and_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	and(era, 0, 1, F_8_BIT);
	// ANDed = 00010100 01010010 01011101 00000011
	assert_int_equal(era->registers[1], 340942083);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	and(era, 0, 1, F_16_BIT);
	// ANDed = 00010100 01010010 01000101 00000011
	assert_int_equal(era->registers[1], 340935939);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	and(era, 0, 1, F_32_BIT);
	// ANDed = 00000000 01000010 01000101 00000011
	assert_int_equal(era->registers[1], 4343043);
}

static void xor_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	xor(era, 0, 1, F_8_BIT);
	// XORed = 00010100 01010010 01011101 10111000
	assert_int_equal(era->registers[1], 340942264);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	xor(era, 0, 1, F_16_BIT);
	// XORed = 00010100 01010010 10111000 10111000
	assert_int_equal(era->registers[1], 340965560);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	xor(era, 0, 1, F_32_BIT);
	// XORed = 10111110 10011100 10111000 10111000
	assert_int_equal(era->registers[1], 3197941944);
}

static void lsl_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsl(era, 0, 1, F_8_BIT);
	// LSLed = 00000000 00000000 00000000 00010110
	assert_int_equal(era->registers[1], 22);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsl(era, 0, 1, F_16_BIT);
	// LSLed = 00000000 00000000 11001010 00010110
	assert_int_equal(era->registers[1], 51734);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsl(era, 0, 1, F_32_BIT);
	// LSLed = 01010101 10011101 11001010 00010110
	assert_int_equal(era->registers[1], 1436404246);
}

static void lsr_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsr(era, 0, 1, F_8_BIT);
	// LSRed = 00000000 00000000 00000000 00000101
	assert_int_equal(era->registers[1], 5);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsr(era, 0, 1, F_16_BIT);
	// LSRed = 00000000 00000000 01110010 10000101
	assert_int_equal(era->registers[1], 29317);

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;
	// 00000000 00000000 00000000 00000000
	era->registers[1] = 0;
	lsr(era, 0, 1, F_32_BIT);
	// LSRed = 01010101 01100111 01110010 10000101
	assert_int_equal(era->registers[1], 1432842885);
}

int main(void)
{

	const struct CMUnitTest logic_tests[] = {
			cmocka_unit_test(or_tests),
			cmocka_unit_test(and_tests),
			cmocka_unit_test(xor_tests),
			cmocka_unit_test(lsl_tests),
			cmocka_unit_test(lsr_tests)
	};

	return cmocka_run_group_tests_name(
			"Logical Operators Tests",
			logic_tests,
			setup_logic_tests,
			teardown_logic_tests
	);
}
