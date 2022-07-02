#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>

typedef enum {
	OFF,
	DEBUG,
	INFO,
	WARNING,
	ERROR
} LOGGING_LEVELS;

void init_logger(LOGGING_LEVELS);

void log_func(LOGGING_LEVELS level, const char *frmt, ...);

#define log_debug(...) log_func(DEBUG, __VA_ARGS__)
#define log_info(...)  log_func(INFO, __VA_ARGS__)
#define log_warn(...)  log_func(WARNING, __VA_ARGS__)
#define log_error(...) log_func(ERROR, __VA_ARGS__)

#endif
