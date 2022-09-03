#ifndef RWFILE_H
#define RWFILE_H

/// @file rwfile.h

/// Return codes for rwfile.h
enum retcodes_rwfile_h 
{ 
ERR_FILE_OPEN_RWFILE = -1, ///< file openning error
ERR_FILE_STAT_RWFILE = -2, ///< get file stat error
ERR_ARGS_NULL_RWFILE = -3  ///< some given args are NULL
};

/// @brief Gets file size in bytes
///
/// @param[in] filename name of file
///
/// @return size of file in bytes on success,
/// ERR_FILE_STAT_RWFILE(-2) on getting stat error,
/// ERR_ARGS_NULL_RWFILE(-3) if filename == NULL
int get_file_size(const char *filename);

/// @brief Reads data from file into buffer
///
/// @param[in] filename name of file which read from
/// @param[out] buffer buffer where text store to
/// @param[out] nSymbols number of symbols to read
///
/// @return number of bytes read on success,
/// ERR_FILE_OPEN_RWFILE(-1) on file openning error,
/// ERR_ARGS_NULL_RWFILE(-3) if filename == NULL or buffer == NULL
int read_file(const char *filename, char *buffer, size_t nSymbols);

#endif /* RWFILE_H */
