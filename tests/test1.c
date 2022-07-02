/**
 * Test to ascertain that logger library is being included correctly
 */

#include <stdio.h>
#include <string.h>
#include "../src/logger.h"

int main() {
	char *string = strdup(log_level_strings[INFO]);
	if(strcmp(string, "INFO") == 0) {
		printf("Test passed.\n");
	}
	else {
		printf("Test failed.\n");
	}
	return 0;
}
