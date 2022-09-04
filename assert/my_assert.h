#include <stdio.h>

#ifdef NDEBUG
#define ASSERT(condition) ((void)0)
#else
#define ASSERT(condition)        \
if (!(condition)) {              \
    printf("Error in %s "        \
           "in line %d "         \
           "in func %s\n",       \
           #condition,           \
           __LINE__,             \
           __PRETTY_FUNCTION__); \
}
#endif
