#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "erric_interpreter.h"

// read more at https://api.cmocka.org/group__cmocka__exec.html

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state)
{
	(void) state; /* unused */
}


/* loads binary file for mathematical operations test */
static void setup_math_test(void **state)
{
	// todo

}

static int teardown_math_test(void **state)
{
	// todo

	return 0;
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(null_test_success),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
