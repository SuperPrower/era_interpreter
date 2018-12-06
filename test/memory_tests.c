#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "era_interpreter.h"
#include "memory_operators.h"

static int setup_memory_tests(void **state)
{
	*state = init_era();

	return 0;
}

static int teardown_memory_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	free_era(era);

	return 0;
}

static void ld_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	sword_t ret;

	write_lword(era, 0, 2865685771);
	era->registers[0] = 0;
	era->registers[1] = 10;
	ret = ld(era, 0, 1, F_32_BIT);
	assert_int_equal(era->registers[1], 2865685771);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// Negative test: wrong command format
	ret = ld(era, 0, 1, F_8_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = ld(era, 0, 100, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_REGISTER);

	// Negative test: memory out of bounds
	era->registers[0] = era->memory_size + 1;
	ret = ld(era, 0, 1, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_MEMORY_OUT_OF_BOUNDS);
}

static void lda_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	sword_t ret;

	write_lword(era, 0, 2865685771);
	write_lword(era, 1, 48706037);
	era->registers[PC] = 1;
	era->registers[0] = 292236222;
	era->registers[1] = 10;
	ret = lda(era, 0, 1, F_8_BIT);
	assert_int_equal(era->registers[1], 340942259);
	assert_int_equal(era->registers[PC], 3);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// Negative test: wrong command format
	ret = lda(era, 0, 0, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = lda(era, 100, 100, F_8_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_REGISTER);
}

static void ldc_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	sword_t ret;

	era->registers[0] = 292236222;
	ldc(era, 31, 0, F_32_BIT);
	assert_int_equal(era->registers[0], 31);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// Negative test: wrong command format
	ret = ldc(era, 0, 5, F_16_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = ldc(era, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_REGISTER);
}

static void st_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	sword_t ret;

	era->registers[0] = 292236222;
	era->registers[1] = 54;
	ret = st(era, 0, 1, F_32_BIT);
	assert_int_equal(read_lword(era, 54), 292236222);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// Negative test: wrong command format
	ret = st(era, 0, 5, F_16_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_FORMAT);

	// Negative test: bad registers
	ret = st(era, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_REGISTER);

	// Negative test: memory out of bounds
	era->registers[0] = era->memory_size + 1;
	ret = st(era, 0, 0, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_MEMORY_OUT_OF_BOUNDS);
}

static void mov_tests(void **state)
{
	struct era_t * era = (struct era_t *) *state;
	sword_t ret;

	// 10101010 11001110 11100101 00001011
	era->registers[0] = 2865685771;

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	ret = mov(era, 0, 1, F_8_BIT);
	// MOVed = // 00010100 01010010 01011101 00001011
	assert_int_equal(era->registers[1], 340942091);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	ret = mov(era, 0, 1, F_16_BIT);
	// MOVed = // 00010100 01010010 11100101 00001011
	assert_int_equal(era->registers[1], 340976907);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// 00010100 01010010 01011101 10110011
	era->registers[1] = 340942259;
	ret = mov(era, 0, 1, F_32_BIT);
	// MOVed = // 10101010 11001110 11100101 00001011
	assert_int_equal(era->registers[1], 2865685771);
	assert_int_equal(ret, ERA_STATUS_NONE);

	// Negative test: bad registers
	ret = mov(era, 100, 100, F_32_BIT);
	assert_int_equal(ret, ERA_STATUS_WRONG_REGISTER);
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
