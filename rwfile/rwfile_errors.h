#ifndef RWFILE_ERRORS_H
#define RWFILE_ERRORS_H

/// @file rwfile_errors.h
/// @brief Описание ошибок rwfile.h

#include <stdint.h>

#define ERR_TYPE_RWFILE uint64_t

/// Errors that might occur in rwfile
enum errors_rwfile : ERR_TYPE_RWFILE 
{
        ERR_FILE_STAT_RWFILE  = 1,      ///< cannot get file stat
#define ERR_FILE_STAT_RWFILE_MSSG           "cannot get file stat"

        ERR_FILE_SIZE_RWFILE  = 1 << 1, ///< bad size of the file
#define ERR_FILE_SIZE_RWFILE_MSSG           "bad file size in stat"
        
        ERR_FILE_OPEN_RWFILE  = 1 << 2, ///< cannot open file
#define ERR_FILE_OPEN_RWFILE_MSSG           "cannot open file"
        
        ERR_FILE_READ_RWFILE  = 1 << 3, ///< cannot read file
#define ERR_FILE_READ_RWFILE_MSSG           "cannot read file"
        
        ERR_FILE_CLOSE_RWFILE = 1 << 4, ///< cannot close file
#define ERR_FILE_CLOSE_RWFILE_MSSG          "cannot close file"
        
        ERR_MEM_ALLOC_RWFILE  = 1 << 5, ///< error during malloc
#define ERR_MEM_ALLOC_RWFILE_MSSG           "error during calloc"
        
        ERR_EMPTY_FILE_RWFILE = 1 << 6  ///< empty file
#define ERR_EMPTY_FILE_RWFILE_MSSG          "empty file"
};

#endif /* RWFILE_ERRORS_H */
