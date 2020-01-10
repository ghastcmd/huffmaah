#define nullptr NULL

#define logerr(msg) {\
    int line = __LINE__ - 3;\
    printf("\x1b[94m%s:%i\x1b[0m$ @%s > %s: \x1b[31m%s\n\x1b[0m",\
    __FILE__, line, __func__, msg, strerror(errno));\
}

#define FLAG 0x8f000000