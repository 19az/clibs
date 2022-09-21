#ifndef RWFILE_ERRORS_H
#define RWFILE_ERRORS_H

/// @file rwfile_errors.h
/// @brief Errors which may occur during executing
/// rwfile functions

#include <stdint.h>

#include "../error_handling/special_macros.h"

#define ERR_TYPE_RWFILE uint64_t
#define CODE_FROM_ERR_RWFILE(err) err
#define MSSG_FROM_ERR_RWFILE(err) "bad error"

/// Return codes for rwfile lib
const ERR_TYPE_RWFILE ERR_FILE_STAT_RWFILE =
MULTI_CHAR_CONST_8('R','W','F',' ','S','T','A','T');

const ERR_TYPE_RWFILE ERR_FILE_SIZE_RWFILE =
MULTI_CHAR_CONST_8('R','W','F',' ','S','I','Z','E');
                                                    
const ERR_TYPE_RWFILE ERR_FILE_OPEN_RWFILE =
MULTI_CHAR_CONST_8('R','W','F',' ','O','P','E','N');

const ERR_TYPE_RWFILE ERR_FILE_READ_RWFILE =
MULTI_CHAR_CONST_8('R','W','F',' ','R','E','A','D');

const ERR_TYPE_RWFILE ERR_FILE_CLOS_RWFILE =
MULTI_CHAR_CONST_8('R','W','F',' ','C','L','O','S');

const ERR_TYPE_RWFILE ERR_MEM_ALLOC_RWFILE = 
MULTI_CHAR_CONST_8('R','W','F',' ','A','L','O','C');

#include "../error_handling/undef_special_macros.h"

#endif /* RWFILE_ERRORS_H */
