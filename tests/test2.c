/**
 * Test to check that init_logger and log_debug work properly.
 */

#include "../src/logger.h"
#include <stdio.h>

void test_init(void) {
	init_logger(INFO);
}

int main() {
	test_init();
	log_debug("Print: %d", DEBUG); //Will not print anything.
	log_info("Print: %d", INFO);
	log_warn("Print: %d", WARNING);
	log_error("Print: %d", ERROR);
	return 0;
}
