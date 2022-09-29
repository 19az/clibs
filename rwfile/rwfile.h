#ifndef RWFILE_H
#define RWFILE_H

/// @file rwfile.h
/// @brief Functions for input/output files

#include "rwfile_errors.h"
#define ERR_TYPE ERR_TYPE_RWFILE
#include "../error_handling/error_handling.h"

/// @brief Gets file size in bytes
///
/// @param[in] filename name of file
/// @param[out] err if not NULL
/// there would be stored error from ERR_SUPPORT
///
/// @return size of file in bytes
///
/// @note uses ERR_SUPPORT, possible errors:
/// ERR_FILE_STAT_RWFILE,
/// ERR_FILE_SIZE_RWFILE
///
/// @note err = NULL by dafault
///
/// @see ERR_SUPPORT, ASSERT, ERR_HANDLED
size_t get_file_size(const char* filename ERR_SUPPORT_DECL);

/// @brief Reads whole from file into buffer
///
/// @param[in] filename name of file which read from
/// @param[in] size size of each object to read
/// @param[out] count if not NULL 
/// there would be storednumber of read bytes
/// @param[out] err if not NULL
/// there would be stored error from ERR_SUPPORT
///
/// @return buffer in dynamic memory with data from file
///
/// @note uses ERR_SUPPORT, possible errors:
/// ERR_FILE_STAT_RWFILE,
/// ERR_FILE_SIZE_RWFILE,
/// ERR_FILE_OPEN_RWFILE,
/// ERR_FILE_READ_RWFILE,
/// ERR_FILE_CLOS_RWFILE,
/// ERR_MEM_ALLOC_RWFILE
///
/// @note adds 0 element to the end of buffer,
/// count = NULL and err = NULL by default
///
/// @see ERR_SUPPORT, ASSERT, ERR_HANDLED
void *read_whole_file(const char*   filename,
                            size_t  size,
                            size_t* count = NULL
                            ERR_SUPPORT_DECL);

#include "../error_handling/undef_error_handling.h"
#ifndef RWFILE_CPP
    #undef ERR_TYPE
#endif

#endif /* RWFILE_H */
