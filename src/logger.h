#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include "commons.h"
#include "parser/types.h"

#ifdef DEBUG
#define LOG_DEBUG(...)                                                         \
  do {                                                                         \
    fprintf(stderr, "[DEBUG] ");                                               \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  } while (0)
#else
#define LOG_DEBUG(...)                                                         \
  do {                                                                         \
  } while (0)
#endif

#ifdef VEROBOSE_MODE
#define LOG_TRACE(...)                                                         \
  do {                                                                         \
    fprintf(stderr, "[TRACE] ");                                               \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  } while (0)
#else
#define LOG_TRACE(...)                                                         \
  do {                                                                         \
  } while (0)
#endif

#define LOG_ERROR(...)                                                         \
  do {                                                                         \
    fprintf(stderr, "[ERROR] ");                                               \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  } while (0)

void yyerror_internal(const char *msg, SourceLocation loc);

void yyerror(const char *msg);

#define yyerrorf(msg, ...) yyerror_internal_format(msg, ##__VA_ARGS__, yylloc)

void yyerror_internal_format(SourceLocation loc, const char *fmt, ...);

#endif
