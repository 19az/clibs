#include <stdio.h>

#define ERROR_REPORT(error_msg) \
printf("Error: %s "             \
       "in line %d "            \
       "in func %s\n",          \
       error_msg,               \
       __LINE__,                \
       __PRETTY_FUNCTION__);    
