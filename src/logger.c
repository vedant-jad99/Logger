#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

//Global variables to keep track of log files.
static int LOG_LEVEL = OFF;
static const char* log_filename = DEFAULT_LOG_PATH;
static bool write_to_file = false;

static const char* log_level_strings[] = {
	" OFF ",
	" [DEBUG] ",
	" [INFO] ",
	" [WARNING] ",
	" [ERROR] ",
};

const char* colors[] = {
	"\x1B[0m",
	"\x1B[34m",
	"\x1B[32m",
	"\x1B[33m",
	"\x1B[31m",
};

/**
 * @brief Function to get the current date and time and writeto log file.
 *
 * @params[in] fptr File pointer to the log file.
 *
 * @retval None.
 */
static void get_datetime(FILE *fptr) {
	time_t t = time(NULL);
	struct tm *tm  = localtime(&t);
	const char *d_time = asctime(tm);
	const char *datetime = strchr(d_time, '\n');
	int length = datetime - d_time;

	char *modified_date = malloc(length + 1);	
	strncpy(modified_date, d_time, length);
	modified_date[length] = '\0';
	fprintf(fptr, "%s ", modified_date); 

	free(modified_date);
}

/**
 * @brief Function to write the log level to the log file.
 *
 * @params[in] level Log level.
 * @params[in] fptr File pointer to the log file.
 *
 * @retval None
 */
static void log_msg(LOGGING_LEVELS level, FILE *fptr) {
	get_datetime(fptr);
	if(fptr == stderr) {
		fprintf(fptr, "%s%s%s", colors[level], log_level_strings[level], colors[RESET]);
	}
	else {
		fprintf(fptr, "%s", log_level_strings[level]);
	}
}

void log_func(LOGGING_LEVELS level, const char *frmt, ...) {
	if(LOG_LEVEL > level) {
		return;
	}

	FILE *fptr = stderr;
	if(write_to_file) {
		fptr = fopen(log_filename, "a");
		if(NULL == fptr) {
			fprintf(stderr, "%sError:%s File not existing or Permission denied\nExiting the program with status 1.\n", colors[ERROR], colors[RESET]);
			exit(1);
		}
	}

	log_msg(level, fptr);
	
	char *format = strdup(frmt);
	strcat(format, "\n");
	va_list argp;
	va_start(argp, frmt);
	vfprintf(fptr, format, argp);
	va_end(argp);

	if(fptr != stderr) {
		fclose(fptr);
	}
	free(format);
}

void init_logger(LOGGING_LEVELS level, const char* filename, bool to_file) {
	if(LOG_LEVEL > OFF) {
		fprintf(stderr, "%sError:%s Logger already initialised in the project\nExiting the program with status 1.\n", colors[ERROR], colors[RESET]);
		exit(1);
	}

	LOG_LEVEL = level;
	if(NULL != filename) {
		log_filename = filename;
	}
	write_to_file = to_file;
}

