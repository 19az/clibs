
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define RWFILE_CPP 
#include "rwfile.h"

#include "error_handling/error_handling.h"

#define get_file_stat(filename, stat_varname, ret_value) \
    ASSERT(filename  != NULL);                           \
    ASSERT(*filename != '\0');                           \
                                                         \
    struct stat stat_varname = {};                       \
                                                         \
    if (stat(filename, &stat_varname) == -1              \
        ERR_HANDLED_MSSG                                 \
        (                                                \
            stderr,                                      \
            ERR_FILE_STAT_RWFILE                         \
        )                                                \
       )                                                 \
        return ret_value;

size_t get_file_size(const char* filename ERR_SUPPORT_DEFN)
{
    ASSERT(filename  != NULL);
    ASSERT(*filename != '\0');

    get_file_stat(filename, file_stat, 0);

    if (file_stat.st_size < 0
        ERR_HANDLED_MSSG
        (
             stderr,
             ERR_FILE_SIZE_RWFILE
        )
       )
        return 0;

    return (size_t) file_stat.st_size;
}

struct timespec get_file_time_last_modification(const char* filename ERR_SUPPORT_DEFN)
{
    ASSERT(filename != NULL);
    ASSERT(*filename != '\0');

    get_file_stat(filename, file_stat, timespec{});

    return file_stat.st_mtim;
}

void* read_whole_file(const char*   filename,
                            size_t  size,
                            size_t* count /* = NULL */
                            ERR_SUPPORT_DEFN)
{
    ASSERT(filename  != NULL);
    ASSERT(*filename != '\0');

    ASSERT(size != 0);
    
    size_t file_size  = get_file_size(filename, err);

    if (file_size == 0
        ERR_HANDLED_MSSG
        (
            stderr,
            ERR_EMPTY_FILE_RWFILE
        )
       )
        return NULL;

    FILE *file = fopen(filename, "r");

    if (file == NULL
        ERR_HANDLED_MSSG
        (
            stderr,
            ERR_FILE_OPEN_RWFILE
        )
       )
        return NULL;

    void *buffer = calloc(file_size + 1, size); // ADDS 0 element to the end !!!
                                                
    if (buffer == NULL
        ERR_HANDLED_MSSG
        (
            stderr,
            ERR_MEM_ALLOC_RWFILE
        )
       )
    {
        fclose(file);

        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, file_size, file);

    read_bytes < file_size
        ERR_HANDLED_MSSG
        (
            stderr,
            ERR_FILE_READ_RWFILE
        );
    
    (count) ? *count = read_bytes : 0;

    fclose(file) == EOF
        ERR_HANDLED_MSSG
        (
            stderr,
            ERR_FILE_CLOSE_RWFILE
        );

    return buffer;
}

