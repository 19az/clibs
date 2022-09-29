
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "stack_errors.h"
#define ERR_TYPE ERR_TYPE_STACK
#include "../error_handling/error_handling.h"

struct Stack {
    Elem_t *data = NULL;
    size_t size     = 0;
    size_t capacity = 0;
#ifndef NDEBUG
    DEBUG_DATA debug_data = {};
#endif
};

#ifndef NDEBUG
/// @brief Dumps stack to log file
///
/// @param stk pointer to the stack
void StackDump(Stack *stk);
#endif

/// @brief Checks if stack is valid
///
/// @param stk pointer to stack to check
///
/// @return 0 if stack is OK, error code otherwise
ERR_TYPE_STACK StackError(Stack *stk);

/// @brief Constructs object of Stack with given size
///
/// @param stk pointer to the object to construct
/// @param[in] size size of constructing stack
void StackCtor_(Stack *stk, size_t size ERR_SUPPORT_DECL);

/// @brief Destructs object of Stack
void StackDtor_(Stack *stk ERR_SUPPORT_DECL);

/// @brief Adds new element to the stack
///
/// @param stk pointer to the stack
/// @param[in] elem element to add
void StackPush(Stack *stk, Elem_t elem ERR_SUPPORT_DECL);

/// @brief Removes last element from the stack and returns it
///
/// @param stk pointer to the stack
///
/// @return removed element
Elem_t StackPop(Stack *stk ERR_SUPPORT_DECL);

#ifdef NDEBUG
    #define StackCtor(stk, size) StackCtor_(stk, size)
#else
    #define StackCtor(stk, size)                           \
        stk->var_data           = VAR_INFO(stk);           \
        stk->DEBUG_DATA.logfile = fopen(logfilename, "w"); \
        StackCtor_(stk, size);
#endif

#ifdef NDEBUG
    #define StackDtor(stk) StackDtor_(stk)
#else
    #define StackDtor(stk)               \
        fclose(stk->debug_data.logfile); \
        StackDtor_(stk);
#endif

#ifndef STACK_CPP
    #undef ERR_TYPE
#endif
#include "../error_handling/undef_error_handling.h"

#endif /* STACK_H */
