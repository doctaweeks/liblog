#include <stdarg.h>
#include <syslog.h>
#include <stdio.h>
#include <stdbool.h>

#include "logger.h"

static bool _syslog;
static bool _console;

__attribute__((__format__ (__printf__, 1, 0)))
static void _console_log(const char *format, va_list args)
{
	int ret;
	ret = vprintf(format, args);
	if (ret < 0 && _syslog) {
		syslog(LOG_NOTICE, "Unable to write to console (%d)", ret);
	}
}


__attribute__((__format__ (__printf__, 2, 0)))
static void _logger(enum log_level level, const char *format, va_list args)
{
	if (_console) {
		_console_log(format, args);
	}

	if (_syslog) {
		vsyslog(LOG_NOTICE, format, args);
	}
}

void log_open(const char *name, bool syslog, const char *file, bool console)
{
	_syslog = syslog;
	_console = console;

	// TODO: file
	if (_syslog) {
		openlog(name, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
	}
}

void log_reopen(const char *name, bool syslog, const char *file, bool console)
{
	log_close();
	log_open(name, syslog, file, console);
}

void log_close(void)
{
	if (_syslog) {
		closelog();
	}
}

/*__attribute__((__format__ (__printf__, 2, 3)))
void logger(enum log_level level, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(level, format, ap);

	va_end(ap);
}*/

__attribute__ ((format (printf, 1, 2)))
void log_debug(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(AUDIOLOG_DEBUG, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_info(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(AUDIOLOG_INFO, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_warn(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(AUDIOLOG_WARN, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_error(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(AUDIOLOG_ERROR, format, ap);

	va_end(ap);
}
