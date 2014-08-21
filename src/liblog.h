#ifndef _LOGGER_H_
#define _LOGGER_H_

enum log_level {
	LIBLOG_ERROR,
	LIBLOG_WARN,
	LIBLOG_INFO,
	LIBLOG_DEBUG
};

void log_open(const char *name, bool syslog, const char *file, bool console);
void log_reopen(const char *name, bool syslog, const char *file, bool console);
void log_close(void);

void log_level(enum log_level level);

void log_error(const char *format, ...);
void log_warn(const char *format, ...);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);

#endif
