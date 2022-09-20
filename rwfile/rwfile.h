#ifndef RWFILE_H
#define RWFILE_H
#define HEADER

#include "../error_handling/error_handling.h"

/// Return codes for rwfile lib
enum errcodes_rwfile
{
ERR_FILE_STAT_RWFILE  = 1,      ///< error during getting file stat
ERR_FILE_SIZE_RWFILE  = 1 << 1, ///< bad file size
ERR_FILE_OPEN_RWFILE  = 1 << 2, ///< error during openning file
ERR_FILE_READ_RWFILE  = 1 << 3, ///< error during reading file
ERR_FILE_CLOSE_RWFILE = 1 << 4  ///< error during closing file
};

/// @file rwfile.h

/// @brief Gets file size in bytes
///
/// @param[in] filename name of file
///
/// @return size of file in bytes
///
/// @note uses ERR_SUPPORT, possible errors:
/// ERR_FILE_STAT_RWFILE,
/// ERR_FILE_SIZE_RWFILE
///
/// @see ERR_SUPPORT, ASSERT, ERR_HANDLED
size_t get_file_size(const char *filename ERR_SUPPORT);

/// @brief Reads text from file into buffer
///
/// @param[in] filename name of file which read from
/// @param[out] buffer buffer where text store to
/// @param[in] size  size of each object to read
/// @param[in] count number of objects to read
///
/// @return number of read bytes
///
/// @note uses ERR_SUPPORT, possible errors:
/// ERR_FILE_OPEN_RWFILE,
/// ERR_FILE_READ_RWFILE,
/// ERR_FILE_CLOSE_RWFILE
///
/// @see ERR_SUPPORT, ASSERT, ERR_HANDLED
size_t read_file(const char *filename, char *buffer, size_t size, size_t count ERR_SUPPORT);

#include "../error_handling/undef_error_handling.h"

#undef HEADER
#endif /* RWFILE_H */
