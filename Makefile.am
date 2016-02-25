AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/liblog.pc
DISTCLEANFILES = $(pkgconfig_DATA)

include_HEADERS=src/liblog.h

lib_LTLIBRARIES=liblog.la
liblog_la_SOURCES=src/log.c
