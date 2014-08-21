#ifndef _LOGGER_H_
#define _LOGGER_H_

enum log_level {
	AUDIOLOG_ERROR,
	AUDIOLOG_WARN,
	AUDIOLOG_INFO,
	AUDIOLOG_DEBUG
};

void log_open(const char *name, bool syslog, const char *file, bool console);
void log_reopen(const char *name, bool syslog, const char *file, bool console);
void log_close(void);

//void logger(enum log_level level, const char *format, ...);

void log_error(const char *format, ...);
void log_warn(const char *format, ...);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);

#endif
