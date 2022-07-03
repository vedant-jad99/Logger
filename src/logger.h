#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>
#include <stdbool.h>
#define DEFAULT_LOG_PATH "/var/log/logger.log"
#define RESET 0

typedef enum {
	OFF,
	DEBUG,
	INFO,
	WARNING,
	ERROR
} LOGGING_LEVELS;

/**
 * @brief Function to initialize the logger.
 *
 * @params[in] level Log level.
 * @params[in] filename Path to the log file.
 * @params[in] to_file Boolean variable to allow writing to file or to stderr stream.
 *
 * @retval None.
 */
void init_logger(LOGGING_LEVELS, const char *, bool);

/**
 * @brief Function to write the message to the log file.
 *
 * @params[in] level Log level.
 * @params[in] frmt Format message.
 * @params[in] ... Variable arguments.
 *
 * @retval None.
 */
void log_func(LOGGING_LEVELS level, const char *filename, const size_t line, const char *frmt, ...);

#define log_debug(...) log_func(DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_func(INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_func(WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_func(ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif
