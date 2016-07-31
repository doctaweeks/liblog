AC_INIT([liblog], [0.1.2])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE

LT_INIT

AC_C_RESTRICT
AC_PROG_CC_C99

AC_ARG_ENABLE([log-stderr],
              [AS_HELP_STRING([--disable-log-stderr], [Disable logging errors to stderr])],
              [],
              [AC_DEFINE([LOG_STDERR], [1])])

AC_OUTPUT([Makefile src/liblog.pc])
