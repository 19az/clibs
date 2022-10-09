
/// @file stack_resize.h
///
/// @brief StackResize_() функция для изменения вместимости массива стека

#ifndef STACK_RESIZE_H
#define STACK_RESIZE_H

#include "stack/stack.h"

/// @brief Изменяет вместимость стека
///
/// @param stk указатель на стек
/// @param[in] new_size количество элементов, которое
/// должен вмешать стек после выполнения функции
///
/// @note Есть вывод ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
void StackResize_(Stack* stk, size_t new_size ERR_SUPPORT_DECL);

#endif /* STACK_RESIZE_H */

