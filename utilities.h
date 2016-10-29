#ifndef UTILITIES_H
#define UTILITIES_H

#include "vector.h"

struct vector *strsplit(char *str, const char *sep);
void remove_newline(char *str);

#endif
