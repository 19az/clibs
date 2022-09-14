#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../assert/my_assert.h"
#include "rwfile.h"

int get_file_size(const char *filename) {
    ASSERT(filename != NULL);

    struct stat st = {};
    if (stat(filename, &st) == -1)
        return -1;

    return (int) st.st_size;
}

int read_file(const char *filename, char *buffer, size_t nSymbols /* ERR_SUPPORT */) {
    ASSERT(filename != NULL);
    ASSERT(buffer != NULL);
    if (nSymbols == 0)
        return 0;

    FILE *file = fopen(filename, "r");
    //FILE *file = $( fopen(filename, "r") );   ==>   __do_$ ( fopen(...), "fopen(...)", __LINE__ )
    if (file == NULL)
        return -1;

    int bytes_read = (int) fread(buffer, sizeof(char), nSymbols, file);

    fclose(file);
   // fclose(file) == 0 asserted ("...");


 //|| __assert_fail (__LINE__)


 //|| (err)? *err = ERR_CLOSE_FILE : 0;
    
   
    return bytes_read;
}
