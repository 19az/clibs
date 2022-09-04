#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

#include <stdio.h>

#define ERROR_REPORT(err_msg) \
printf("Error: %s\n"          \
    "in line %d "             \
    "in func %s\n",           \
    #condition,               \
    __LINE__,                 \
    __PRETTY_FUNCTION__);     \
}

#endif
