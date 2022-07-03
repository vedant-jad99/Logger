/**
 * Test to check that init_logger and log_debug work properly.
 */

#include "../src/logger.h"
#include <stdio.h>

void test_init(void) {
	init_logger(INFO, "log.log", true); //Will write to log.log file
	//init_logger(DEBUG, NULL, true); //Will write to the default log path. Needs to be run with sudo.
//	init_logger(DEBUG, NULL, false); //Will output to stderr console.
}

int main() {
	test_init();
	log_debug("Print: %d", DEBUG); //Will not print anything.
	log_info("Print: %d", INFO);
	log_warn("Print: %d", WARNING);
	log_error("Print: %d", ERROR);
	return 0;
}
