// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#ifdef VERBOSE_MODE
  #define LOG_DEBUG(...) do { fprintf(stderr, "[DEBUG] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while(0)
  #define LOG_TRACE(...) do { fprintf(stderr, "[TRACE] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while(0)
#else
  #define LOG_DEBUG(...) do {} while(0)
  #define LOG_TRACE(...) do {} while(0)
#endif

extern int verbose_mode;
#define LOG_ERROR(...) do { fprintf(stderr, "[ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while(0)

#endif
