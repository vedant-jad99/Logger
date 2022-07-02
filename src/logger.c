#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <time.h>

static int LOG_LEVEL = 0;

static const char *log_strings(LOGGING_LEVELS level) {
	switch(level) {
		case DEBUG:
			return " [DEBUG] ";
		case INFO:
			return " [INFO] ";
		case WARNING:
			return " [WARNING] ";
		case ERROR:
			return " [ERROR] ";
	}
}	

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
	const char* log_level = log_strings(level);
	fprintf(stderr, log_level);
}

void log_func(LOGGING_LEVELS level, const char *frmt, ...) {
	if(LOG_LEVEL > level) {
		return;
	}
	log_msg(level);
	
	char *format = strdup(frmt);
	strcat(format, "\n");
	va_list argp;
	va_start(argp, format);
	vfprintf(stderr, format, argp);
	va_end(argp);

	free(format);
}

void init_logger(LOGGING_LEVELS level) {
	LOG_LEVEL = level;
}

