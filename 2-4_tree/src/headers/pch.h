#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <limits.h>

#define logerr(foo) {\
    printf("%s:%s, %i:%s at %s\n", foo, strerror(errno),\
        __LINE__ - 1, __FILE__, __FUNCTION__);\
}

#define logerr_calloc(ptr) {\
    if (!ptr) { logerr("calloc"); return nullptr; };\
}

#define nullptr NULL