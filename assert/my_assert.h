#include <assert.h>
#include <stdio.h>

#define ASSERT(condition)        \
if (!(condition)) {              \
    printf("Error in %s "        \
           "in line %d "         \
           "in func %s\n",       \
           #condition,           \
           __LINE__,             \
           __PRETTY_FUNCTION__); \
}                                \
assert((condition));
