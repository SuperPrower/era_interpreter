#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"
#include "math_operators.h"

/*
 * Bunch of tests on math operators
 *
 * read more about writing tests at https://api.cmocka.org/group__cmocka__exec.html
 */


/* loads binary file for mathematical operations test */
static int setup_math_tests(void **state)
{
	*state = init_erric();

	return 0;
}

static int teardown_math_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	free_erric(erric);

	return 0;
}

static void add_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	add(erric, 0, 1, F_8_BIT);
	// ADDed = 00000000 00000000 00000000 10111110
	assert_int_equal(erric->registers[1], 190);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	add(erric, 0, 1, F_16_BIT);
	// ADDed = 00000000 00000000 01000010 10111110
	assert_int_equal(erric->registers[1], 17086);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	add(erric, 0, 1, F_32_BIT);
	// ADDed = 10111111 00100001 01000010 10111110
	assert_int_equal(erric->registers[1], 3206628030);
}

static void add_overflow_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00010100 01010010 01011101 11111111
	erric->registers[1] = 340942335;
	add(erric, 0, 1, F_8_BIT);
	// ADDed = 00000000 00000000 00000000 00001010
	assert_int_equal(erric->registers[1], 10);

	// 00010100 01010010 11111111 11111111
	erric->registers[1] = 340983807;
	add(erric, 0, 1, F_16_BIT);
	// ADDed = 00000000 00000000 11100101 00001010
	assert_int_equal(erric->registers[1], 58634);

	// 11111111 11111111 11111111 11111111
	erric->registers[1] = 4294967295;
	add(erric, 0, 1, F_32_BIT);
	// ADDed = 10101010 11001110 11100101 00001010
	assert_int_equal(erric->registers[1], 2865685770);
}

// Not quite possible since internally, values are unsigned
static void add_underflow_tests(void **state)
{
	// In this case, two's complement starts with bit 1 as a sign
	struct erric_t * erric = (struct erric_t *) *state;
	// 00101010 11001110 01100101 00000011
	erric->registers[0] = 718169347;

	// 00010100 01010010 01011101 11110111
	erric->registers[1] = 340942327;
	add(erric, 0, 1, F_8_BIT);
	// ADDed = 00000000 00000000 00000000 11111010
	assert_int_equal(erric->registers[1], 250);

	// 00010100 01010010 11011101 11110111
	erric->registers[1] = 340975095;
	add(erric, 0, 1, F_16_BIT);
	// ADDed = 00000000 00000000 01000010 11111010
	assert_int_equal(erric->registers[1], 17146);

	// 11111111 11111111 11111111 11111111
	erric->registers[1] = 4294967295;
	add(erric, 0, 1, F_32_BIT);
	// ADDed = 00101010 11001110 01100101 00000010
	assert_int_equal(erric->registers[1], 718169346);
}

static void sub_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	sub(erric, 0, 1, F_8_BIT);
	// SUBed = 00000000 00000000 00000000 10101000
	assert_int_equal(erric->registers[1], 168);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	sub(erric, 0, 1, F_16_BIT);
	// SUBed = 00000000 00000000 01111000 10101000
	assert_int_equal(erric->registers[1], 30888);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	sub(erric, 0, 1, F_32_BIT);
	// SUBed = 01101001 10000011 01111000 10101000
	assert_int_equal(erric->registers[1], 1770223784);
}

static void sub_overflow_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101011 01011101 11010010 11100011
	erric->registers[0] = 2875052771;

	// 01110100 01001010 01111010 01100100
	erric->registers[1] = 1951038052;
	sub(erric, 0, 1, F_8_BIT);
	// SUBed = 00000000 00000000 00000000 10000001
	assert_int_equal(erric->registers[1], 129);

	// 01110100 01001010 01111010 01100100
	erric->registers[1] = 1951038052;
	sub(erric, 0, 1, F_16_BIT);
	// SUBed = 00000000 00000000 10100111 10000001
	assert_int_equal(erric->registers[1], 42881);

	// 01110100 01001010 01111010 01100100
	erric->registers[1] = 1951038052;
	sub(erric, 0, 1, F_32_BIT);
	// SUBed = 11001000 11101100 10100111 10000001
	assert_int_equal(erric->registers[1], 3370952577);
}

static void sub_underflow_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 000001000 00010000 01001010 0100010
	erric->registers[0] = 67642658;

	// 00000000 00000000 00000000 00000001
	erric->registers[1] = 1;
	sub(erric, 0, 1, F_8_BIT);
	// SUBed = 00000000 00000000 00000000 11011111
	assert_int_equal(erric->registers[1], 223);

	// 00000000 00000000 00000001 00000001
	erric->registers[1] = 257;
	sub(erric, 0, 1, F_16_BIT);
	// SUBed = 00000000 00000000 11011011 11011111
	assert_int_equal(erric->registers[1], 56287);

	// 00000001 00000001 00000001 00000001
	erric->registers[1] = 16843009;
	sub(erric, 0, 1, F_32_BIT);
	// SUBed = 11111100 11111000 11011011 11011111
	assert_int_equal(erric->registers[1], 4244167647);
}

static void asr_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asr(erric, 0, 1, F_8_BIT);
	// ASRed = 00000000 00000000 00000000 00000101
	assert_int_equal(erric->registers[1], 5);

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asr(erric, 0, 1, F_16_BIT);
	// ASRed = 00000000 00000000 10110010 10000101
	assert_int_equal(erric->registers[1], 45701);

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asr(erric, 0, 1, F_32_BIT);
	// ASRed = 10010101 01100111 01110010 10000101
	assert_int_equal(erric->registers[1], 2506584709);
}

static void asl_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asl(erric, 0, 1, F_8_BIT);
	// ASLed = 00000000 00000000 00000000 00010110
	assert_int_equal(erric->registers[1], 22);

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asl(erric, 0, 1, F_16_BIT);
	// ASLed = 00000000 00000000 11001010 00010110
	assert_int_equal(erric->registers[1], 51734);

	// 00000000 00000000 00000000 00000000
	erric->registers[1] = 0;
	asl(erric, 0, 1, F_32_BIT);
	// ASLed = 11010101 10011101 11001010 00010110
	assert_int_equal(erric->registers[1], 3583887894);
}

int main(void)
{

	const struct CMUnitTest math_tests[] = {
		cmocka_unit_test(add_tests),
		cmocka_unit_test(add_overflow_tests),
		cmocka_unit_test(add_underflow_tests),
		cmocka_unit_test(sub_tests),
		cmocka_unit_test(sub_overflow_tests),
		cmocka_unit_test(sub_underflow_tests),
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
