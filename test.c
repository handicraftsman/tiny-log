#include "tiny-log.h"

int main() {
  tl_log_level = TLLevel_DEBUG;
  
  char* l = "main";
  tl_write(l, "tl_write()");
  tl_lwrite(TLLevel_INFO, l, "tl_lwrite()");
  
  tl_debug(l, "tl_debug()");
  tl_io(l, "tl_io()");
  tl_info(l, "tl_info()");
  tl_warning(l, "tl_warning()");
  tl_error(l, "tl_error()");
  tl_important(l, "tl_important()");
  tl_critical(l, "tl_critical()");
  
  tl_write(l, "I also support %s", "formatted printing");
  return 0;
}
