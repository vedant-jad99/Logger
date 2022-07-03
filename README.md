# Logger
Simple C logging library.

## Usage

logger.c and logger.h should be included in the project. The logger first needs to be initialized in the program.

### Initialization:

```
init_logger(LOGGING_LEVEL, filename, write_to_file);
```

### Logging

To log any message, there are 4 macros provided:

- log_debug(...)
- log_info(...)
- log_warn(...)
- log_error(...)
