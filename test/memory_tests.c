#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"
#include "memory_operators.h"

static int setup_memory_tests(void **state)
{
	*state = init_erric();

	return 0;
}

static int teardown_memory_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	free_erric(erric);

	return 0;
}

static void ld_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	write_lword(erric, 0, 2865685771);
	erric->registers[0] = 0;
	erric->registers[1] = 10;
	ret = ld(erric, 0, 1, F_32_BIT);
	assert_int_equal(erric->registers[1], 2865685771);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative test: wrong command format
	ret = ld(erric, 0, 1, F_8_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = ld(erric, 0, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);

	// Negative test: memory out of bounds
	erric->registers[0] = erric->memory_size + 1;
	ret = ld(erric, 0, 1, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS);
}

static void lda_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	write_lword(erric, 0, 2865685771);
	write_lword(erric, 1, 48706037);
	erric->registers[PC] = 1;
	erric->registers[0] = 292236222;
	erric->registers[1] = 10;
	ret = lda(erric, 0, 1, F_8_BIT);
	assert_int_equal(erric->registers[1], 340942259);
	assert_int_equal(erric->registers[PC], 3);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative test: wrong command format
	ret = lda(erric, 0, 0, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = lda(erric, 100, 100, F_8_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);
}

static void ldc_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	erric->registers[0] = 292236222;
	ldc(erric, 31, 0, F_32_BIT);
	assert_int_equal(erric->registers[0], 31);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative test: wrong command format
	ret = ldc(erric, 0, 5, F_16_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = ldc(erric, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);
}

static void st_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	erric->registers[0] = 292236222;
	erric->registers[1] = 54;
	ret = st(erric, 0, 1, F_32_BIT);
	assert_int_equal(read_lword(erric, 54), 292236222);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative test: wrong command format
	ret = st(erric, 0, 5, F_16_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = st(erric, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);

	// Negative test: memory out of bounds
	erric->registers[0] = erric->memory_size + 1;
	ret = st(erric, 0, 0, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS);
}

static void mov_tests(void **state)
{
	struct erric_t * erric = (struct erric_t *) *state;
	sword_t ret;

	// 10101010 11001110 11100101 00001011
	erric->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	ret = mov(erric, 0, 1, F_8_BIT);
	// MOVed = // 00010100 01010010 01011101 00001011
	assert_int_equal(erric->registers[1], 340942091);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	ret = mov(erric, 0, 1, F_16_BIT);
	// MOVed = // 00010100 01010010 11100101 00001011
	assert_int_equal(erric->registers[1], 340976907);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// 00010100 01010010 01011101 10110011
	erric->registers[1] = 340942259;
	ret = mov(erric, 0, 1, F_32_BIT);
	// MOVed = // 10101010 11001110 11100101 00001011
	assert_int_equal(erric->registers[1], 2865685771);
	assert_int_equal(ret, ERRIC_STATUS_NONE);

	// Negative test: bad registers
	ret = mov(erric, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERRIC_STATUS_WRONG_REGISTER);
}

int main(void)
{

	const struct CMUnitTest memory_tests[] = {
			cmocka_unit_test(ld_tests),
			cmocka_unit_test(lda_tests),
			cmocka_unit_test(ldc_tests),
			cmocka_unit_test(st_tests),
			cmocka_unit_test(mov_tests)
	};

	return cmocka_run_group_tests_name(
			"Memory Operators Tests",
			memory_tests,
			setup_memory_tests,
			teardown_memory_tests
	);
}
