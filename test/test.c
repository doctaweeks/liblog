#include <liblog.h>

#define NAME "sharpd"
#define LOGFILE "/tmp/liblog-test.log"

int main(int argc, char *argv[]) {
  int logopts = LIBLOG_FLAG_MICROTIMESTAMP | LIBLOG_FLAG_CONSOLE;
  
  log_open(NAME, LOGFILE, logopts);
  log_level(LIBLOG_DEBUG);
  
  log_info("Info entry.");
  log_error("Error entry.");

  log_close();
}
