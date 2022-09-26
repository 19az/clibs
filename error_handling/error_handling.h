
/// @file error_handling.h
/// @brief Macros for convinient error monitoring in debug

#include <stdio.h>
#include <stdint.h>

#include "special_macros.h"

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

/// @brief Struct for pointer variable data
typedef struct {
    void   *stk_ptr   = NULL; ///< pointer value
    char   *var_name  = NULL; ///< name of variable
    char   *func_name = NULL; ///< name of func where variable defined
    char   *file      = NULL; ///< name of file where function defined
    size_t  line      = 0;    ///< number of line where this data loads
} VAR_DATA;

#endif /* ERROR_HANDLING_H */

/// @brief Fills VAR_DATA
#define VAR_INFO(var) {var, #var + (#var[0] == '&'), __PRETTY_FUNCTION__, __FILE__, __LINE__}

/// @brief Prints string error message in stderr

#define ERR_REPORT_MSSG(stream, msg) \
fprintf(stream,                      \
        "Error: %s. "                \
        "In line %d "                \
        "in func %s\n",              \
        msg,                         \
        __LINE__,                    \
        __PRETTY_FUNCTION__)

/// @brief Like ERR_REPORT_MSSG but prints multi-char
/// constant err_code instead of string message

#define ERR_REPORT_CODE(stream, code) \
fprintf(stream,                       \
        "Error: %.*s. "               \
        "In line %d "                 \
        "in func %s\n",               \
        (int) sizeof(code),           \
        (const char*) &code,          \
        __LINE__,                     \
        __PRETTY_FUNCTION__)

/// @brief Provides error support mode for functions
///
/// @note for proper work defined variable HEADER is required in header sections

#define ERR_SUPPORT_DECL , ERR_TYPE *err = NULL
#define ERR_SUPPORT_DEFN , ERR_TYPE *err

/// @brief Sets err to given value
#define ERR_SET(new_err) (err) ? *err = new_err : 1

/// @brief Checks condition, updates err value and 
/// (if NDEBUG is not defined) prints error message

#ifdef NDEBUG
    #define ERR_HANDLE_MSSG(stream, cond, new_err, ERR_MSSG) \
    (cond) &&                                                \
    (ERR_SET(new_err))
#else
    #define ERR_HANDLE_MSSG(stream, cond, new_err, ERR_MSSG)     \
    (cond) &&                                                    \
    EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, ERR_MSSG(new_err))) && \
    (ERR_SET(new_err))
#endif

/// @brief Like ERR_HANDLE_MSSG but prints multi-char
/// constant err_code instead of string message

#ifdef NDEBUG
    #define ERR_HANDLE_CODE(stream, cond, new_err, ERR_CODE) \
    (cond) &&                                                \
    (ERR_SET(new_err))
#else
    #define ERR_HANDLE_CODE(stream, cond, new_err, ERR_CODE) \
    (cond) &&                                                \
    EVAL1(DEFER1(ERR_REPORT_CODE)(stream, ERR_CODE(new_err))) &&     \
    (ERR_SET(new_err))
#endif

/// @brief Like ERR_HANDLE_MSSG but suffix version

#ifdef NDEBUG
    #define ERR_HANDLED_MSSG(stream, new_err, ERR_MSSG) \
    && (ERR_SET(new_err))
#else
    #define ERR_HANDLED_MSSG(stream, new_err, ERR_MSSG)      \
    && EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, ERR_MSSG(msg))) \
    && (ERR_SET(new_err))   
#endif

/// @brief Like ERR_HANDLE_CODE but suffix version

#ifdef NDEBUG
    #define ERR_HANDLED_CODE(stream, new_err, ERR_CODE) \
    ERR_HANDLED_MSSG(stream, new_err, "")
#else
    #define ERR_HANDLED_CODE(stream, new_err, ERR_CODE)          \
    && EVAL1(DEFER1(ERR_REPORT_CODE)(stream, ERR_CODE(new_err))) \
    && (ERR_SET(new_err)) 
#endif

/// @brief Checks if err is not 0 and reports its code
#define ERR_CHECK_CODE(stream, err, ERR_CODE)         \
(err) &&                                              \
EVAL1(DEFER1(ERR_REPORT_CODE)(stream, ERR_CODE(err)))

/// @brief Checks if err is not 0 and reports its message
#define ERR_CHECK_MSSG(stream, err, ERR_MSSG)         \
(err) &&                                              \
EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, ERR_MSSG(err)))

/// @brief Checks condition and, if false, prints error message
///
/// @note if NDEBUG is defined then does nothing

#ifdef NDEBUG
    #define ASSERT_MSSG(cond, msg) ((void)0)
#else
    #define ASSERT_MSSG(cond, msg) \
    if (!(cond))                   \
        ERR_REPORT_MSSG(stderr, msg);
#endif

/// @brief Like ASSERT_MSSG but arg msg is optional (#cond by default)
#define ASSERT(cond, ...)                     \
GET_ARG_3( ,   ##__VA_ARGS__,                 \
ASSERT_MSSG(cond, __VA_ARGS__),               \
ASSERT_MSSG(cond, "failed condition: "#cond))

/// @brief Redefinition std assert for compatibility

#ifdef assert
    #undef assert
#endif
#define assert(cond) ASSERT(cond)

/// @brief Suffix version of ASSERT

#ifdef NDEBUG
    #define ASSERTED(stream, msg) || 0
#else
    #define ASSERTED(stream, msg) || ERR_REPORT_MSSG(stream, msg)
#endif
