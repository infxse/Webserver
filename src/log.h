#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define DEBUG_MODE 1
// Log in dem stderr wenn debug. vor-formatiert
#if DEBUG_MODE == 1
#define DEBUG_LOG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...) ((void)0)
#endif

#endif