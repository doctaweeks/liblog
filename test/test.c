#include <liblog.h>

#define NAME "liblog-test"
#define LOGFILE "/tmp/liblog-test.log"

int main(int argc, char *argv[]) {
  int logopts = LIBLOG_FLAG_MICROTIMESTAMP | LIBLOG_FLAG_CONSOLE | LIBLOG_FLAG_STDERR;

  log_open(NAME, LOGFILE, logopts);
  log_level(LIBLOG_DEBUG);

  log_info("Info entry. Should go to stdout.");
  log_error("Error entry. Should go to stderr.");

  logopts = LIBLOG_FLAG_MICROTIMESTAMP | LIBLOG_FLAG_CONSOLE;
  log_reopen(NAME, LOGFILE, logopts);

  log_info("Info entry. Should go to stdout.");
  log_error("Error entry. Should go to stdout.");

  log_close();
}
