#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "messages.h"

void Error(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  fprintf(stderr, "Fatal error: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

void Warning(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  fprintf(stderr, "Warning: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
  va_end(args);
}

void Message(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  fprintf(stderr, "- ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");
  va_end(args);
}


void Progress(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  fprintf(stderr, "* ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "...\n");
  va_end(args);
}


void Info(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}
