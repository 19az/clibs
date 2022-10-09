
/// @file stack_hash.h
///
/// @brief Хэш защита полей и элементов стека

#ifndef STACK_HASH_H
#define STACK_HASH_H

#include "stack/stack.h"

#ifdef HASH_PROTECT

/// @brief Считает хэш структуры стека
///
/// @param[in] stk указатель на стек
HASH_TYPE_STACK GetHashStructStack_(const Stack* stk);

/// @brief Считатет хэш массива стека
///
/// @param[in] stk указатель на стек
HASH_TYPE_STACK GetHashDataStack_(const Stack* stk);

/// @brief Обновление хэша структуры и массива стека
#define UPDATE_HASH_STACK(stk)                         \
    stk->hash_struct_value = GetHashStructStack_(stk); \
    stk->hash_data_value   = GetHashDataStack_  (stk); 

#else /* ! HASH_PROTECT */

#define UPDATE_HASH_STACK(stk) ((void) 0)

#endif /* HASH_PROTECT */

#endif /* STACK_HASH_H */

