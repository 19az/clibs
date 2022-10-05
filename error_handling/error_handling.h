
/// @file error_handling.h
/// @brief Макросы для удобной обработки и логгирование ошибок

#include <stdio.h>
#include <stdint.h>

#include "special_macros.h"

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

/// @brief Стуктура с информацией о переменной
typedef struct
{
          void*  ptr       = NULL; ///< адрес
    const char*  var_name  = NULL; ///< имя
    const char*  func_name = NULL; ///< фунция создания
    const char*  file      = NULL; ///< файл создания
          size_t line      = 0;    ///< номер строки создания
} VAR_DATA;

#endif /* ERROR_HANDLING_H */

/// @brief Заполняет структуру VAR_DATA информацией
#define VAR_INFO(var)                 \
    VAR_DATA{var,                     \
             #var + (#var[0] == '&'), \
             __PRETTY_FUNCTION__,     \
             __FILE__,                \
             __LINE__}

/// @brief Печатает сообщение об ошибке в некоторый файл

#ifdef NDEBUG
    #define ERR_REPORT_MSSG(stream, msg) ((void)0)
#else
    #define ERR_REPORT_MSSG(stream, msg)    \
        fprintf((stream) ? stream : stderr, \
                "Error: %s\n"               \
                "in file: %s\n"             \
                "in line: %d\n"             \
                "in func %s;\n\n",          \
                msg,                        \
                __FILE__,                   \
                __LINE__,                   \
                __PRETTY_FUNCTION__)
#endif

/// @brief Добавляет фунцием возможность возвращения кода ошибки(объявление)
#define ERR_SUPPORT_DECL , ERR_TYPE *err = NULL

/// @brief Добавляет фунцием возможность возвращения кода ошибки(определение)
#define ERR_SUPPORT_DEFN , ERR_TYPE *err

/// @brief Sets err to given value
#define ERR_SET(new_err) (err) ? *err |= new_err : 1

/// @brief Проверяет условие cond, обновляет переменную ошибки err
/// значением new_err и печатет сообщение об ошибке в некоторый файл
#define ERR_HANDLE_MSSG(stream, cond, new_err)                       \
    if (cond)                                                        \
    {                                                                \
        EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, CAT(new_err, _MSSG))); \
        ERR_SET(new_err);                                            \
    }

/// @brief Суффиксная версия ERR_HANDLE_MSSG
#define ERR_HANDLED_MSSG(stream, new_err)                          \
    && EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, CAT(new_err, _MSSG))) \
    && (ERR_SET(new_err))   

/// @brief Проверяет переменную ошибки err на содержание кода compare_err
/// и, если да, печатает сообщение об ошибке в некоторый поток
#define ERR_CHECK_MSSG(stream, check_err, compare_err)              \
    (check_err & compare_err) &&                                    \
    EVAL1(DEFER1(ERR_REPORT_MSSG)(stream, CAT(compare_err, _MSSG)))

/// @brief Ассерт без выхода из программы

#ifdef NDEBUG
    #define ASSERT_MSSG(cond, msg) ((void)0)
#else
    #define ASSERT_MSSG(cond, msg)                 \
        if (!(cond)) ERR_REPORT_MSSG(stderr, msg);
#endif

/// @brief "Перегрузка" ассерта от количества аргументов: проверяется
/// cond и, если cond ложно, то печатается либо переданная строка msg,
/// либо cond в види строки
#define ASSERT(cond, ...)                         \
    GET_ARG_3( ,   ## __VA_ARGS__,                \
    ASSERT_MSSG(cond, __VA_ARGS__),               \
    ASSERT_MSSG(cond, "failed condition: "#cond))

/// @brief Переопределение стандартного ассерта для совместимсти

#ifdef assert
    #undef assert
#endif
#define assert(cond) ASSERT(cond)

/// @brief Суффиксная версия ассерта

#ifdef NDEBUG
    #define ASSERTED(stream, msg) || 0
#else
    #define ASSERTED(stream, msg) || ERR_REPORT_MSSG(stream, msg)
#endif

/// @brief Печатает сообщение в логфайл с текущими функцией, файлом и строкой 

#ifdef NDEBUG
    #define DUMP(logfile) ((void) 0)
#else
    #define DUMP(logfile)                     \
        fprintf((logfile) ? logfile : stderr, \
                "%s at %s(%d):\n",            \
                __PRETTY_FUNCTION__,          \
                __FILE__,                     \
                __LINE__);                    \
                                              \
        fflush(logfile);
#endif

