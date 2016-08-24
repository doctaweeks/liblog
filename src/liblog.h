#ifndef LIBLOG_H_
#define LIBLOG_H_

#include <stdbool.h>
#include <stdarg.h>

#define LIBLOG_FLAG_SYSLOG		1
#define LIBLOG_FLAG_FILE		2
#define LIBLOG_FLAG_CONSOLE		4
#define LIBLOG_FLAG_TIMESTAMP		8
#define LIBLOG_FLAG_MICROTIMESTAMP	16
#define LIBLOG_FLAG_ERROR_TO_STDERR	32

enum log_level {
	LIBLOG_ERROR,
	LIBLOG_WARN,
	LIBLOG_INFO,
	LIBLOG_DEBUG
};

void log_open(const char *restrict name, const char *restrict file, int flags);
void log_reopen(const char *restrict name, const char *restrict file, int flags);
void log_close(void);

void log_level(enum log_level level);

void log_error(const char *format, ...);
void log_warn(const char *format, ...);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);

void log_verror(const char *format, va_list ap);
void log_vwarn(const char *format, va_list ap);
void log_vinfo(const char *format, va_list ap);
void log_vdebug(const char *format, va_list ap);

#endif
