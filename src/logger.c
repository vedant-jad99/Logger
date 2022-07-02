#include "logger.h"
#include "logger_utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

static int LOG_LEVEL = 0;

static const char* log_level_strings[] = {
	" OFF ",
	" [DEBUG] ",
	" [INFO] ",
	" [WARNING] ",
	" [ERROR] ",
};

static void get_datetime() {
	time_t t = time(NULL);
	struct tm *tm  = localtime(&t);
	const char *d_time = asctime(tm);
	const char *datetime = strchr(d_time, '\n');
	int length = datetime - d_time;

	char *modified_date = malloc(length + 1);	
	strncpy(modified_date, d_time, length);
	modified_date[length] = '\0';
	fprintf(stderr, "%s ", modified_date); 

	free(modified_date);
}

static void log_msg(LOGGING_LEVELS level) {
	get_datetime();
	switch(level) {
		case ERROR:
			fprintf(stderr, RED "%s" RESET, log_level_strings[level]);
			break;
		case WARNING:
			fprintf(stderr, YELLOW "%s" RESET, log_level_strings[level]);
			break;
		case INFO:
			fprintf(stderr, GREEN "%s" RESET, log_level_strings[level]);
			break;
		case DEBUG:
			fprintf(stderr, BLUE "%s" RESET, log_level_strings[level]);
			break;
	}
}

void log_func(LOGGING_LEVELS level, const char *frmt, ...) {
	if(LOG_LEVEL > level) {
		return;
	}
	log_msg(level);
	
	char *format = strdup(frmt);
	strcat(format, "\n");
	va_list argp;
	va_start(argp, frmt);
	vfprintf(stderr, format, argp);
	va_end(argp);

	free(format);
}

void init_logger(LOGGING_LEVELS level) {
	LOG_LEVEL = level;
}

