
/// @file stack_error.h
///
/// @brief Проверка стека на валидность

#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#include "../stack.h"

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

/// @brief Проверяет элементы массива стека на валидность
///
/// @param[in] stk указатель на стек
///
/// @return 0 если стек валиден,
/// коды ошибок если стек не валиден
/// (коды ошибок см. в stack_constants.h)
///
/// @note Есть возврат ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
ERR_TYPE_STACK StackErrorElems_(const Stack* stk ERR_SUPPORT_DECL);

#endif /* STACK_ERROR_H */

