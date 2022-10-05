
/// @file stack.h
///
/// @brief Структура данных стек и функции для работы с ним

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "settings/stack_settings.h"
#define ERR_TYPE ERR_TYPE_STACK
#include "../error_handling/error_handling.h"

struct Stack
{
#ifdef CANARY_PROTECT
    CANARY_STACK l_canary = POISON_CANARY_STACK;
#endif

#ifdef HASH_PROTECT
    HASH_TYPE_STACK hash_struct_value = 0;
    HASH_TYPE_STACK hash_data_value   = 0;
#endif

    Elem_t*      data     = POISON_ELEM_T_PTR_STACK;

    size_t       size     = POISON_SIZE_T_STACK;
    size_t       capacity = POISON_SIZE_T_STACK;
    
#ifndef NDEBUG
    VAR_DATA var_data = {};
#endif

#ifdef CANARY_PROTECT
    CANARY_STACK r_canary = POISON_CANARY_STACK;
#endif
};

#include "dump/stack_dump.h"
#include "error/stack_error.h"
#include "resize/stack_resize.h"

#ifdef HASH_PROTECT
    #include "hash/stack_hash.h"
#endif

/// @brief Конструктор стека, принимающий размер,
/// который должен вмещать стек
///
/// @param stk указатель на стек
/// @param[in] size желаемый размер
///
/// @note Есть режим возврата ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
void StackCtor_(Stack* stk, size_t size ERR_SUPPORT_DECL);

/// @brief Позволяет запоминать информацию о переменной стека

#ifdef NDEBUG
    #define StackCtor(stk, size) StackCtor_(stk, size)
#else
    #define StackCtor(stk, size)           \
        (stk)->var_data = VAR_INFO(stk);   \
                                           \
        StackCtor_(stk, size);

#endif

/// @brief Деструктор стека
///
/// @param stk указатель на стек
///
/// @note Есть режим возврата ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
void StackDtor(Stack* stk ERR_SUPPORT_DECL);

/// @brief Добавляет новый элемент в стек
///
/// @param stk указатель на стек
/// @param[in] elem добавляемый элемент
///
/// @note Есть режим возврата ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
void StackPush(Stack* stk, Elem_t elem ERR_SUPPORT_DECL);

/// @brief Удаляет последний элемент из стека и возвращает его
///
/// @param stk указатель на стек
///
/// @return удаленный элемент типа Elem_t
///
/// @note Есть режим возврата ошибок ERR_SUPPORT
///
/// @see ERR_SUPPORT_DECL
Elem_t StackPop(Stack* stk ERR_SUPPORT_DECL);

#ifndef STACK_CPP
    #undef ERR_TYPE
#endif

#endif /* STACK_H */
