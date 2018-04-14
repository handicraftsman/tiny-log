#include "tiny-log.h"

#define _GNU_SOURCE

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

TLLevel tl_log_level = TLLevel_INFO;

char* tl_level_chars[] = {"DBG", " IO", "INF", "WRN", "ERR", "IMP", "CRT"};
char* tl_level_colors[] = {"\x1b[32m", "\x1b[36m", "\x1b[34m", "\x1b[33m", "\x1b[31m", "\x1b[37m", "\x1b[35m"};
char* tl_bold = "\x1b[1m";
char* tl_reset = "\x1b[0m";
char* tl_creset = "\x1b[39m";

void tl_write(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(tl_log_level, name, fmt, args);
  va_end(args);
}

void tl_lwrite(TLLevel lvl, char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(lvl, name, fmt, args);
  va_end(args);
}

static void write_to_log(
  FILE*   f,
  TLLevel lvl,
  char*   timestr,
  char*   name,
  char*   msg,
  bool    colored
) {
  if (colored) {
    fprintf(
      f,
      "%s%s[%s%s%s | %s%s%s] %s%s%s%s> %s%s\n",
      tl_bold,
      tl_level_colors[lvl],
      tl_creset,
      timestr,
      tl_level_colors[lvl],
      tl_creset,
      tl_level_chars[lvl],
      tl_level_colors[lvl],
      tl_reset,
      name,
      tl_bold,
      tl_level_colors[lvl],
      tl_reset,
      msg
    );
  } else {
    fprintf(f, "[%s | %s] %s> %s\n", timestr, tl_level_chars[lvl], name, msg);
  }
}

void tl_vwrite(TLLevel lvl, char* name, char* fmt, va_list args) {
  if (lvl < tl_log_level) return;
  
  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo = localtime(&rawtime);
  char* timestr = asctime(timeinfo);
  timestr[strlen(timestr)-1] = '\0';
  
  char* msg;
  vasprintf(&msg, fmt, args);  
  
  write_to_log(stderr, lvl, timestr, name, msg, true);

  free(msg);  
}

void tl_debug(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_DEBUG, name, fmt, args);
  va_end(args);
}

void tl_io(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_IO, name, fmt, args);
  va_end(args);
}

void tl_info(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_INFO, name, fmt, args);
  va_end(args);
}

void tl_warning(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_WARNING, name, fmt, args);
  va_end(args);
}

void tl_error(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_ERROR, name, fmt, args);
  va_end(args);
}

void tl_important(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_IMPORTANT, name, fmt, args);
  va_end(args);
}

void tl_critical(char* name, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  tl_vwrite(TLLevel_CRITICAL, name, fmt, args);
  va_end(args);
}
