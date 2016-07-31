#include "liblog.h"

#include <syslog.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

static FILE *_logfile = NULL;

static enum log_level max = LIBLOG_ERROR;

static int _flags;
#define FLAG_SET(x) ((_flags & x) == x)

static char ts[23];

static void _get_time()
{
	struct timeval tv;
	time_t rawtime;
	struct tm *current_time;
	size_t len;

	gettimeofday(&tv, NULL);
	rawtime = tv.tv_sec;
	current_time = localtime(&rawtime);

	len = strftime(ts, 23, "%b %d %H:%M:%S", current_time);
	if (FLAG_SET(LIBLOG_FLAG_MICROTIMESTAMP))
		sprintf(ts+len, ".%06ld", tv.tv_usec);
}

__attribute__((__format__ (__printf__, 2, 0)))
static void _stream_log(FILE *stream, const char *format, va_list pargs, bool copy)
{
	int ret;

	va_list wargs;

	if (FLAG_SET(LIBLOG_FLAG_TIMESTAMP) || FLAG_SET(LIBLOG_FLAG_MICROTIMESTAMP))
		fprintf(stream, "%s ", ts);

	if (copy) {
		va_copy(wargs, pargs);
		ret = vfprintf(stream, format, wargs);
	} else {
		ret = vfprintf(stream, format, pargs);
	}

	if (ret < 0)
		goto cleanup;
	putc('\n', stream);

cleanup:
	if (copy)
		va_end(wargs);
}

__attribute__((__format__ (__printf__, 2, 0)))
static void _logger(enum log_level level, const char *format, va_list pargs)
{
	if (level > max)
		return;

	int need = FLAG_SET(LIBLOG_FLAG_SYSLOG) + FLAG_SET(LIBLOG_FLAG_CONSOLE) + (FLAG_SET(LIBLOG_FLAG_FILE) && _logfile != NULL);

	if (FLAG_SET(LIBLOG_FLAG_TIMESTAMP) || FLAG_SET(LIBLOG_FLAG_MICROTIMESTAMP))
		_get_time();

	if (FLAG_SET(LIBLOG_FLAG_CONSOLE)) {
	  #ifdef LOG_STDERR
		if (level == LIBLOG_ERROR) {
			_stream_log(stderr, format, pargs, need > 1);
		} else {
			_stream_log(stdout, format, pargs, need > 1);
		}
		#endif
		#ifndef LOG_STDERR
		_stream_log(stdout, format, pargs, need > 1);
		#endif
	}

	if (FLAG_SET(LIBLOG_FLAG_FILE) && _logfile != NULL)
	        _stream_log(_logfile, format, pargs, need > 1);

	if (FLAG_SET(LIBLOG_FLAG_SYSLOG)) {
		vsyslog(LOG_NOTICE, format, pargs);
	}
}

void log_open(const char *restrict name, const char *restrict file, int flags)
{
	_flags = flags;

	if (FLAG_SET(LIBLOG_FLAG_SYSLOG))
		openlog(name, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);

	if (file != NULL) {
		_logfile = fopen(file, "a");
		if (_logfile != NULL)
			setvbuf(_logfile, NULL, _IOLBF, 0);
	}
}

void log_level(enum log_level level)
{
	max = level;
}

void log_reopen(const char *restrict name, const char *restrict file, int flags)
{
	log_close();
	log_open(name, file, flags);
}

void log_close(void)
{
	if (FLAG_SET(LIBLOG_FLAG_SYSLOG))
		closelog();

	if (_logfile != NULL)
		fclose(_logfile);
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

	_logger(LIBLOG_DEBUG, format, ap);

	va_end(ap);
}
__attribute__ ((format (printf, 1, 0)))
void log_vdebug(const char *format, va_list ap)
{
	_logger(LIBLOG_DEBUG, format, ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_info(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(LIBLOG_INFO, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 0)))
void log_vinfo(const char *format, va_list ap)
{
	_logger(LIBLOG_INFO, format, ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_warn(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(LIBLOG_WARN, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 0)))
void log_vwarn(const char *format, va_list ap)
{
	_logger(LIBLOG_WARN, format, ap);
}

__attribute__ ((format (printf, 1, 2)))
void log_error(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	_logger(LIBLOG_ERROR, format, ap);

	va_end(ap);
}

__attribute__ ((format (printf, 1, 0)))
void log_verror(const char *format, va_list ap)
{
	_logger(LIBLOG_ERROR, format, ap);
}
