
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "../line.cpp"
#include "../../../../unit_testing/unit_testing.h"

//------------------------------------------------------------------------------

const size_t MAXLEN_BUFFER = 100;
struct LineArgs {
    const char *buffer  = NULL;
    const int  *lengths = NULL;
};
