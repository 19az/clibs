
/// @file stack_hash.h
///
/// @brief Хэш защита полей и элементов стека

#ifndef STACK_HASH_H
#define STACK_HASH_H

#include "../stack.h"

/// @brief Посчитать хэш структуры стека
///
/// @param[in] stk указатель на стек
HASH_TYPE_STACK GetHashStructStack_(const Stack* stk);

/// @brief Посчитать хэш массива стека
///
/// @param[in] stk указатель на стек
HASH_TYPE_STACK GetHashDataStack_(const Stack* stk);

#endif /* STACK_HASH_H */

