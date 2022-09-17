
/// @file error_handling.h
/// @brief Macros for convinient error monitoring in debug

#include <stdio.h>

#include "special_macros.h"

/// @brief Prints error message in stderr

#define ERR_REPORT_MSG(msg)  \
fprintf(stderr,              \
        "Error in %s "       \
        "in line %d "        \
        "in func %s\n",      \
        msg,                 \
        __LINE__,            \
        __PRETTY_FUNCTION__)

/// @brief Print error message(if given) in stderr,
/// otherwise prints standert message("smth")

#define ERR_REPORT(...)      \
GET_ARG_3( , ##__VA_ARGS__,  \
ERR_REPORT_MSG(__VA_ARGS__), \
ERR_REPORT_MSG("smth")) 

/// @brief Provides error support mode for functions
///
/// @note for proper work defined variable HEADER is required in header sections

#ifdef HEADER
    #define ERR_SUPPORT , int *err = NULL
#else
    #define ERR_SUPPORT , int *err
#endif

/// @brief Checks condition, updates err value and 
/// (if NDEBUG is not defined) prints error message

#ifdef NDEBUG
    #define ERR_HANDLE_MSG(cond, err_code, msg) \
    if (cond && err)                            \
        *err += err_code;
#else
    #define ERR_HANDLE_MSG(cond, err_code, msg) \
    if (cond) {                                 \
        (err) ? *err += err_code : 0;           \
        ERR_REPORT(msg);                        \
    }
#endif

/// @brief Check condition, updates err value and
/// (if NDEBUG is not defined) prints error message if given,
/// otherwise prints condition
#define ERR_HANDLE(cond, err_code, ...)      \
GET_ARG_3(                 , ##__VA_ARGS__,  \
ERR_HANDLE_MSG(cond, err_code, __VA_ARGS__), \
ERR_HANDLE_MSG(cond, err_code, #cond))

/// @brief Like ERR_HANDLE_MSG but suffix version

#ifdef NDEBUG
    #define ERR_HANDLED_MSG(err_code, msg) && ((err) ? *err += err_code : 1)
#else
    #define ERR_HANDLED_MSG(err_code, msg) && ((err) ? *err += err_code : 1) \
                                       && (ERR_REPORT(msg) || 1)
#endif

/// @brief Like ERR_HANDLED_MSG but arg msg is optional (#cond by default)
#define ERR_HANDLED(err_code, ...)      \
GET_ARG_3(           , ## __VA_ARGS__,  \
ERR_HANDLED_MSG(err_code, __VA_ARGS__), \
ERR_HANDLED_MSG(err_code, "smth"))

/// @brief Checks condition and, if false, prints error message
///
/// @note if NDEBUG is defined then does nothing

#ifdef NDEBUG
    #define ASSERT_MSG(cond, msg) ((void)0)
#else
    #define ASSERT_MSG(cond, msg) \
    if (!(cond))                  \
        ERR_REPORT(msg);
#endif

/// @brief Like ASSERT_MSG but arg msg is optional (#cond by default)
#define ASSERT(cond, ...)                    \
GET_ARG_3(   , ##__VA_ARGS__,                \
ASSERT_MSG(cond, __VA_ARGS__),               \
ASSERT_MSG(cond, "failed condition: "#cond))

/// @brief Redefinition std assert for compatibility

#ifdef assert
    #define old_assert assert
    #undef assert
#endif
#define assert(cond) ASSERT(cond, "failed condition: "#cond)

/// @brief Suffix version of ASSERT

#ifdef NDEBUG
    #define ASSERTED(msg) || 0
#else
    #define ASSERTED(msg) || ERR_REPORT(msg)
#endif

