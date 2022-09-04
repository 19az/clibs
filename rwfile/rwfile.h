#ifndef RWFILE_H
#define RWFILE_H

/// @file rwfile.h

/// @brief Gets file size in bytes
///
/// @param[in] filename name of file
///
/// @return size of file in bytes on success,
/// -1 on getting stat error
int get_file_size(const char *filename);

/// @brief Reads data from file into buffer
///
/// @param[in] filename name of file which read from
/// @param[out] buffer buffer where text store to
/// @param[out] nSymbols number of symbols to read
///
/// @return number of bytes read on success,
/// -1 on file openning error
int read_file(const char *filename, char *buffer, size_t nSymbols);

#endif /* RWFILE_H */
