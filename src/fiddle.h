#ifndef FIDDLE_H_
#define FIDDLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char bool;
#define true (1)
#define false (0)

typedef unsigned char uchar;
typedef unsigned int uint;

void _panic(const char *f, const uint l, char *msg);
#define PANIC(msg) _panic(__FILE__, __LINE__, (msg))

void _checkFail(const char *f, const uint l, char *c);
#ifdef DEBUG
#define CHECK(c) if (!(c)) {_checkFail(__FILE__,__LINE__,(#c));}
#else
#define CHECK(c)
#endif

#define DEFAULT_STRLEN (65)

#endif // FIDDLE_H_
