#define nullptr NULL

#define logerr(msg) {\
    int line = __LINE__ - 3;\
    printf("\x1b[94m%s:%i\x1b[0m$ @%s > %s: \x1b[31m%s\x1b[0m\n",\
    __FILE__, line, __func__, msg, strerror(errno));\
}

#define logerr_n(msg) {\
    int line = __LINE__ - 3;\
    printf("\x1b[94m%s:%i\x1b[0m$ @%s > %s: \x1b[31m%s",\
    __FILE__, line, __func__, msg, strerror(errno));\
}

#define BOC "\x1b[0;30m"
#define RC "\x1b[0;31m"
#define GC "\x1b[0;32m"
#define YC "\x1b[0;33m"
#define BC "\x1b[0;34m"
#define MC "\x1b[0;35m"
#define CC "\x1b[0;36m"
#define WC "\x1b[0;37m"

#define BBOC "\x1b[1;30m"
#define BRC "\x1b[1;31m"
#define BGC "\x1b[1;32m"
#define BYC "\x1b[1;33m"
#define BBC "\x1b[1;34m"
#define BMC "\x1b[1;35m"
#define BCC "\x1b[1;36m"
#define BWC "\x1b[1;37m"

#define ZC "\x1b[0m"

#define FLAG 0x8fff000000000000