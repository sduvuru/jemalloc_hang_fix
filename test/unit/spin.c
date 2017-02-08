#include "test/jemalloc_test.h"

TEST_BEGIN(test_spin) {
	spin_t spinner;
	spin_init(&spinner);

	for (unsigned i = 0; i < 100; i++) {
		spin_adaptive(&spinner);
	}
}
TEST_END

int
main(void) {
	return test(
	    test_spin);
}
