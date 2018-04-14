#pragma once

#include <stdarg.h>

typedef enum TLLevel {
  TLLevel_DEBUG,
  TLLevel_IO,
  TLLevel_INFO,
  TLLevel_WARNING,
  TLLevel_ERROR,
  TLLevel_IMPORTANT,
  TLLevel_CRITICAL
} TLLevel;

TLLevel tl_log_level;

char* tl_level_chars[7];
char* tl_level_colors[7];
char* tl_bold;
char* tl_reset;
char* tl_creset;

void tl_write(char* name, char* fmt, ...);
void tl_lwrite(TLLevel lvl, char* name, char* fmt, ...);
void tl_vwrite(TLLevel lvl, char* name, char* fmt, va_list args);

void tl_debug(char* name, char* fmt, ...);
void tl_io(char* name, char* fmt, ...);
void tl_info(char* name, char* fmt, ...);
void tl_warning(char* name, char* fmt, ...);
void tl_error(char* name, char* fmt, ...);
void tl_important(char* name, char* fmt, ...);
void tl_critical(char* name, char* fmt, ...);
