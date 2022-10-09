
#ifndef RWFILE_H
#define RWFILE_H

/// @file rwfile.h
/// @brief Библиотека функций ввода/вывода в/из файла

#include "rwfile_errors.h"
#define ERR_TYPE ERR_TYPE_RWFILE
#include "error_handling/error_handling.h"

/// @brief Находит размер файла в байтах
///
/// @param[in] filename имя файла
///
/// @return размер файла в байтах
///
/// @note поддерживает ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL, ASSERT, ERR_HANDLED_MSSG
size_t get_file_size(const char* filename ERR_SUPPORT_DECL);

/// @brief Находит время посленего изменения файла
///
/// @param[in] filename имя файла
///
/// @return struct timespec последнего изменения файла
///
/// @note поддерживает ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL, ASSERT, ERR_HANDLED_MSSG
struct timespec get_file_time_last_modification(const char* filename ERR_SUPPORT_DECL);

/// @brief Читает весь файл и возвращает буффер с его содержимым
///
/// @param[in] filename имя файла
/// @param[in] size размер типа данных файла
/// @param[out] count указатель, по которому сохранить размер файла
/// (по умолчанию NULL)
///
/// @return указатель на буффер в динамической памяти с прочитанным
/// содержимым файла
///
/// @note поддерживает ERR_SUPPORT
///
/// @note добавляет нулевой элемент в конец буффера
///
/// @see ERR_SUPPORT_DECL, ASSERT, ERR_HANDLED_MSSG
void *read_whole_file(const char*   filename,
                            size_t  size,
                            size_t* count = NULL
                            ERR_SUPPORT_DECL);

#ifndef RWFILE_CPP
    #undef ERR_TYPE
#endif

#include "error_handling/undef_error_handling.h"

#endif /* RWFILE_H */
