#include "utils.h"

int rand_range(const int min, const int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}