#pragma once

#include <stdlib.h>

#define DEBUG 1
#if DEBUG
#define DEBUG_PRINT(format, ...) printf("%d: %s | " format " \n", __LINE__, __FILE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

int rand_range(const int min, const int max);