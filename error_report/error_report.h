#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

#include <stdio.h>

#define ERROR_REPORT(err_msg) \
fprintf(stderr,               \
        "Error: %s\n"         \
        "in line %d "         \
        "in func %s\n",       \
        #err_msg,             \
        __LINE__,             \
        __PRETTY_FUNCTION__);  

#endif
