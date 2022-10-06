
#include <stdlib.h>

#define STACK_CPP
#include "error.h"

#include "../hash/hash.h"

/// @brief Проверяет условие ошибки, если оно истинно,
/// пишет сообщение об ошибке в LOGFILE (если не NDEBUG)
/// и добавляет код ошибки в возращаемое значение
#define ERR_HANDLE_MSSG_STACK(cond, err) \
    if ((cond)                           \
        ERR_HANDLED_MSSG(LOGFILE, err))  \
    {                                    \
        ret_err |= err;                  \
    }

static ERR_TYPE_STACK StackErrorElems_(const Stack* stk ERR_SUPPORT_DEFN);
    
ERR_TYPE_STACK StackError_(const Stack* stk ERR_SUPPORT_DEFN)
{
    ERR_TYPE_STACK ret_err = 0;

    if (stk == NULL)
    {
        ret_err |= ERR_BAD_STACK_PTR_STACK;
       
        ERR_SET(ret_err);
        ERR_REPORT_MSSG(LOGFILE, "null pointer given in stk");
   
        return ret_err;
    }

    const Elem_t* data = stk->data;
   
    const size_t size     = stk->size;
    const size_t capacity = stk->capacity;

#ifdef HASH_PROTECT
    ERR_HANDLE_MSSG_STACK(
        GetHashStructStack_(stk) != stk->hash_struct_value,
        ERR_HASH_STRUCT_STACK);
#endif

#ifdef CANARY_PROTECT

    const CANARY_STACK l_canary_struct = stk->l_canary;
    const CANARY_STACK r_canary_struct = stk->r_canary;

    ERR_HANDLE_MSSG_STACK(
        l_canary_struct != POISON_CANARY_STACK ||
        r_canary_struct != POISON_CANARY_STACK,
        ERR_CANARY_STRUCT_STACK);
        
#endif
    
    ERR_HANDLE_MSSG_STACK(
        size > capacity,
        ERR_SIZE_GR_CAP_STACK);

    ERR_HANDLE_MSSG_STACK(
        size == POISON_SIZE_T_STACK,
        ERR_SIZE_POIS_STACK);
    
    ERR_HANDLE_MSSG_STACK(
        capacity == POISON_SIZE_T_STACK,
        ERR_CAP_POIS_STACK);

    if ((data == NULL ||
        data == POISON_ELEM_T_PTR_STACK)
        ERR_HANDLED_MSSG(LOGFILE, ERR_BAD_DATA_PTR_STACK))
    {
        ret_err |= ERR_BAD_DATA_PTR_STACK;
    }
    else
    {

#ifdef HASH_PROTECT
        ERR_HANDLE_MSSG_STACK(
            GetHashDataStack_(stk) != stk->hash_data_value,
            ERR_HASH_DATA_STACK);
#endif

        ret_err |= StackErrorElems_(stk, (err) ? err : NULL);
    }

    return  ret_err;
}

static ERR_TYPE_STACK StackErrorElems_(const Stack* stk ERR_SUPPORT_DEFN [[maybe_unused]]) // Ничего не делает, если нет
                                                                                           // ни POISON_PROTECT,
                                                                                           // ни CANARY_PROTECT
{
    ASSERT(stk != NULL);

    ERR_TYPE_STACK ret_err = 0;

    const Elem_t* data = stk->data;
   
    const size_t size     = stk->size;
    const size_t capacity = stk->capacity;

#ifdef CANARY_PROTECT
    ERR_HANDLE_MSSG_STACK(
        *L_CANARY_PTR_DATA != POISON_CANARY_STACK ||
        *R_CANARY_PTR_DATA != POISON_CANARY_STACK,
        ERR_CANARY_DATA_STACK);
#endif

    ASSERT(data != NULL &&
           data != POISON_ELEM_T_PTR_STACK);

    ASSERT(capacity >= size);

#ifdef POISON_ELEM_T_PROTECT
    for (size_t index = size; index < capacity; index++)
    {
        if (data[index] != POISON_ELEM_T_STACK
            ERR_HANDLED_MSSG(LOGFILE, ERR_ELEM_GR_SIZE_USED_STACK))
        {
            ret_err |= ERR_ELEM_GR_SIZE_USED_STACK;

            break;
        }
    }
#endif

    return ret_err;
}

