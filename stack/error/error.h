
/// @file stack_error.h
///
/// @brief Проверка стека на валидность

#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#include "stack/stack.h"

/// @brief Проверяет на валидность поля структуры стека
/// и элементы массива
///
/// @param[in] stk указатель на стек
///
/// @return 0 если стек валиден,
/// коды ошибок, если стек не валиден
/// (коды ошибок см. в stack_constants.h)
///
/// @note Есть возврат ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
ERR_TYPE_STACK StackError_(const Stack* stk ERR_SUPPORT_DECL);

/// @brief Запуск верификотора
/// и обновление переменной ошибки значением,
/// возвращенным верификатором
#define StackError(logfile, stk)                          \
    (StackError_(stk, (err) ? err : NULL)                 \
        ERR_HANDLED_MSSG(logfile, ERR_VERIFICATOR_STACK))

#endif /* STACK_ERROR_H */

