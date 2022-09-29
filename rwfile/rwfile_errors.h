#ifndef RWFILE_ERRORS_H
#define RWFILE_ERRORS_H

/// @file rwfile_errors.h
/// @brief Errors which may occur during executing
/// rwfile functions

#include <stdint.h>

#include "../error_handling/special_macros.h"

#define ERR_TYPE_RWFILE uint64_t

/// Return codes for rwfile lib
enum errors_rwfile : ERR_TYPE_RWFILE 
{
    ERR_FILE_STAT_RWFILE = 1,      ///< cannot get file stat
    ERR_FILE_SIZE_RWFILE = 1 << 1, ///< bad size of the file
    ERR_FILE_OPEN_RWFILE = 1 << 2, ///< cannot open file
    ERR_FILE_READ_RWFILE = 1 << 3, ///< cannot read file
    ERR_FILE_CLOS_RWFILE = 1 << 4, ///< cannot close file
    ERR_MEM_ALLOC_RWFILE = 1 << 5  ///< error during malloc
};

#define ERR_FILE_STAT_RWFILE_MSSG "cannot get file stat"
#define ERR_FILE_SIZE_RWFILE_MSSG "bad file size in stat"
#define ERR_FILE_OPEN_RWFILE_MSSG "cannot open file"
#define ERR_FILE_READ_RWFILE_MSSG "cannot read file"
#define ERR_FILE_CLOS_RWFILE_MSSG "cannot close file"
#define ERR_MEM_ALLOC_RWFILE_MSSG "error during calloc"

#include "../error_handling/undef_special_macros.h"

#endif /* RWFILE_ERRORS_H */
