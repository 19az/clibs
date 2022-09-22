
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ERR_TYPE_RWFILE_CPP 
#include "rwfile.h"

#include "../error_handling/error_handling.h"

size_t get_file_size(const char *filename ERR_SUPPORT_DEFN) {
    ASSERT(filename != NULL);

    struct stat st = {};
    if ((stat(filename, &st) == -1)
         ERR_HANDLED_CODE(ERR_FILE_STAT_RWFILE,
                          CODE_FROM_ERR_RWFILE))
        return 0;
    if ((st.st_size < 0)
        ERR_HANDLED_CODE(ERR_FILE_SIZE_RWFILE,
                         CODE_FROM_ERR_RWFILE))
        return 0;

    return (size_t) st.st_size;
}

void *read_whole_file(const char   *filename,
                            size_t  size,
                            size_t *count /* = NULL  */
                            ERR_SUPPORT_DEFN) {
    ASSERT(filename != NULL);
    ASSERT(size     != 0);
    
    (count) ? *count = 0 : 0;

    ERR_TYPE_RWFILE err_get_file_size = 0;
    size_t file_size = get_file_size(filename, &err_get_file_size);
    if (ERR_CHECK_CODE(err_get_file_size, CODE_FROM_ERR_RWFILE)) {
        ERR_SET(err_get_file_size);
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL
            ERR_HANDLED_CODE(ERR_FILE_OPEN_RWFILE,
                             CODE_FROM_ERR_RWFILE))
        return NULL;

    void *buffer = calloc(file_size + 1, size); // ADDS 0 element to the end !!!
    if (buffer == NULL
            ERR_HANDLED_CODE(ERR_MEM_ALLOC_RWFILE,
                            CODE_FROM_ERR_RWFILE))
        return NULL;

    size_t read_bytes = fread(buffer, 1, file_size, file);
    (count) ? *count = read_bytes : 0;
    read_bytes < file_size
        ERR_HANDLED_CODE(ERR_FILE_READ_RWFILE,
                         CODE_FROM_ERR_RWFILE);

    fclose(file) == EOF
        ERR_HANDLED_CODE(ERR_FILE_CLOS_RWFILE,
                         CODE_FROM_ERR_RWFILE);
    return buffer;
}

#include "../error_handling/undef_error_handling.h"
