
#define STACK_CPP
#include "stack.h"

#include "../error_handling/error_handling.h"

#ifdef NDEBUG
    #define STACK_DUMP(stk) ((void)0)
#else
    #define STACK_DUMP(stk)                                            \
        DEBUG_DATA dd = stk->debug_data;                               \
        fprintf(dd.logfile,                                            \
                "%s at %s\(%d\):\n"                                    \
                "Stack [%p] \"%s\" at %s at %s\(%d\):\n"               \
                "{\n"                                                  \
                "data [%p]\n"                                          \
                "size     = %lu\n"                                     \
                "capacity = %lu\n"                                     \
                "\t{\n",                                               \
                __PRETTY_FUNCTION__, __FILE__, __LINE__,               \
                (Stack*) dd.stk_ptr, dd.var_name,                      \
                dd.func_name, dd.file, dd.line,                        \
                stk->data, stack->size, stack->capacity);              \
        fflush(dd.logfile);                                            \
                                                                       \
        for (size_t index = 0; index <= stk->capacity; index++) {      \
            fprintf(dd.logfile, "\t%c [%d] = ",                        \
                                (index < size) ? '*' : ' ',            \
                                index + 1);                            \
            fprintf_elem_t(dd.logfile, data[index]);                   \
            fprintf(dd.logfile, "\n");                                 \
            fflush(dd.logfile);                                        \
        }                                                              \
        fprintf(dd.logfile, "\t}\n}\n");                               \
        fflush(dd.logfile);
#endif

#define STACK_ERR_START(stk)                                  \
    ERR_TYPE_STACK verificator_err =                          \
        (STACK_DUMP(stk), check_hash(stk),  StackError(stk)); \
    (err) ? err |= verificator_err : 0;

#define STACK_ERR_FINISH(stk)                                                \
    verificator_err = (STACK_DUMP(stk), update_hash(stk),  StackError(stk)); \
    (err) ? err |= verificator_err : 0;

ERR_TYPE_STACK StackError(Stack *stk) {
    ERR_TYPE_STACK err = 0;
    err |= (stk->data     == NULL)                ? ERR_DATA_NULL_STACK : 0;
    err |= (stk->size     >  capacity)            ? ERR_SIZE_CAPC_STACK : 0;
    err |= (stk->size     == POISON_STACK_SIZE_T) ? ERR_SIZE_POIS_STACK : 0;
    err |= (stk->capacity == POISON_STACK_SIZE_T) ? ERR_CAPC_POIS_STACK : 0;

    // TO DO: add canaries

    return err;
}

void StackCtor_(Stack *stk, size_t size ERR_SUPPORT_DECL) {
    STACK_ERR_START(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }

#ifdef CANARY_PROTECT
    // TO DO: add canaries
#else
    stk->data = (Elem_t*) calloc(size, sizeof(Elem_t));
    if (stk->data == NULL ERR_HANDLED_MSSG(stk->debug_data.logfile,
                                           ERR_CALLOC_STACK,
                                           /* TO DO: add mssg from err */)) {
        return;
    }
#endif
    stk->capacity = size;

    STACK_ERR_FINISH(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }
}

void StackDtor_(Stack *stk ERR_SUPPORT_DECL) {
    STACK_ERR_START(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }

#ifdef CANARY_PROTECT
    // TO DO: add canaries
#else
    free(stk->data);
#endif
    stk->data     = POISON_STACK_FREE_STACK_PTR;
    stk->capacity = POISON_STACK_SIZE_T;
    stk->size     = POISON_STACK_SIZE_T;

    STACK_ERR_FINISH(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }
}

void StackResize_(Stack *stk, size_t new_size ERR_SUPPORT_DECL) {
    STACK_ERR_START(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }

    stk->data = (Elem_t*) reallocarray(stk->data, new_size, sizeof(Elem_t)); // TO DO: better resize strategy
    if (stk->data == NULL ERR_HANDLED_MSSG(stk->debug_data.logfile,
                                           ERR_REALLOC_STACK,
                                           /* TO DO: add mssg from err */)) {
        return;
    }

    STACK_ERR_FINISH(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }
}

void StackPush(Stack *stk, Elem_t elem ERR_SUPPORT_DECL) {
    STACK_ERR_START(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }

    ERR_TYPE_STACK err_resize = 0;
    StackResize_(stk, stk->size + 1, &err_resize);
    if (err_resize) {
        ERR_CHECK_MSSG(stk->debug_data.logfile, err_resize); // TO DO: add mssg from err
        return;
    }
    stk->data[size++] = elem;

    STACK_ERR_FINISH(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return;
    }
}

Elem_t StackPop(Stack *stk ERR_SUPPORT_DECL) {
    STACK_ERR_START(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return; // POISON_ELEM_T ???
    }

    Elem_t ret_value = stk->data[--(stk->size)];
    StackResize_(stk, stk->size); // TO DO: add error handling

    STACK_ERR_FINISH(stk);
    if (verificator_err) {
        STACK_DUMP(stk);
        return; // POISON_ELEM_T ???
    }

    return ret_value;
}

#include "../error_handling/undef_error_handling.h"
