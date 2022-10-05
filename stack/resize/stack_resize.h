
/// @file stack_resize.h
///
/// @brief StackResize_() функция для изменения вместимости массива стека

#ifndef STACK_RESIZE_H
#define STACK_RESIZE_H

#include "../stack.h"

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

/// @brief Пишет дамп сообщение в логфайл с информацией о стеке
/// и параметрами функции StackResize_()
///
/// @param[in] logfile указатель на структуру FILE логфайла
/// @param[in] stk указатель на стек
/// @param[in] new_size new_size аргумент функции StackResize_()
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататься в stderr
void StackResizeDump_(FILE* logfile, const Stack* stk, size_t new_size);

#endif /* STACK_RESIZE_H */

