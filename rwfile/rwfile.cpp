#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "rwfile.h"
#include "../error_handling/error_handling.h"

size_t get_file_size(const char *filename ERR_SUPPORT) {
    ASSERT(filename != NULL);

    (err) ? *err = 0 : 0;

    struct stat st = {};
    if (stat(filename, &st) == -1 ERR_HANDLED(ERR_FILE_STAT_RWFILE, "cannot get file stat"))
        return 0;
    if (st.st_size < 0 ERR_HANDLED(ERR_FILE_SIZE_RWFILE, "bad file size"))
        return 0;

    return (size_t) st.st_size;
}

size_t read_file(const char *filename, char *buffer, size_t size, size_t count ERR_SUPPORT) {
    ASSERT(filename != NULL);
    ASSERT(buffer   != NULL);
    ASSERT(size     != 0);
    if (count == 0)
        return 0;

    (err) ? *err = 0 : 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL ERR_HANDLED(ERR_FILE_OPEN_RWFILE, "cannot open file"))
        return 0;

    size_t bytes_read = fread(buffer, size, count, file);
    bytes_read < count ERR_HANDLED(ERR_FILE_READ_RWFILE, "read objects less than count");

    fclose(file) == EOF ERR_HANDLED(ERR_FILE_CLOSE_RWFILE, "cannot close file");
    return bytes_read;
}

#include "../error_handling/undef_error_handling.h"
