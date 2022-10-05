
/// @brief Позволяет добавить в StackResizeDump_() дамп информацию
/// о месте вызова дампа

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
    #define StackResizeDump(logfile, stk) ((void) 0)
#else
    #define StackResizeDump(logfile, stk)         \
        DUMP(logfile);                            \
                                                  \
        StackResizeDump_(logfile, stk, new_size);
#endif

const double CONST_CAPACITY = 8;    ///< константный размер массива
                                    ///  для стекаStackResize_()
const double EXP_CAPACITY   = 2;    ///< экспонента увеличения массива
                                    ///  для StackResize_()
const double HYST_CAPACITY  = 0.3;  ///< значение "гистеризеса"
                                    ///  для StackResize_()

void StackResize_(Stack* stk, size_t new_size ERR_SUPPORT_DEFN)
{
    ASSERT(stk != NULL);

    if (new_size < 1)
    {
        new_size = 1;
    }

    int is_increase_size = (new_size >= stk->size);

    if (is_increase_size && (new_size <= stk->capacity)) return;
    
    const double new_size_d    = (double) new_size;
    const double log_norm_size = log2(new_size_d / CONST_CAPACITY);
    const double log_exp       = log2(EXP_CAPACITY);
          double r_size_exp    = ceil(log_norm_size / log_exp);

    if (r_size_exp < 0) r_size_exp = 0;

    const double r_size_point = CONST_CAPACITY * pow(EXP_CAPACITY, r_size_exp);
    const double l_size_point = r_size_point / EXP_CAPACITY;

    ASSERT(r_size_point > l_size_point);

    size_t new_capacity = stk->capacity;
    
    if (is_increase_size)
    {
        new_capacity = (size_t) r_size_point;
        ASSERT(new_capacity >= stk->capacity);
    }
    else
    {
        if (( (r_size_point - new_size_d) /
              (r_size_point - l_size_point)) > HYST_CAPACITY)
        {
            new_capacity = (size_t) r_size_point; 
        }
        ASSERT(new_capacity <= stk->capacity);
    }
    ASSERT(new_capacity >= (size_t) CONST_CAPACITY);
    
    if (new_capacity != stk->capacity)
    {
        stk->capacity = new_capacity;
 
#ifdef CANARY_PROTECT
        CANARY_STACK* data = (CANARY_STACK*) stk->data;
        data = (data) ? data - 1 : data;

        data = (CANARY_STACK*) reallocarray(data,
                                            new_capacity * sizeof(Elem_t) +
                                            2            * sizeof(CANARY_STACK),
                                            1);
        
        stk->data = (Elem_t*) (data + 1);
       
        *L_CANARY_PTR_DATA = POISON_CANARY_STACK;
        *R_CANARY_PTR_DATA = POISON_CANARY_STACK;
#else
        stk->data = (Elem_t*) reallocarray(stk->data,
                                           new_capacity,
                                           sizeof(Elem_t));
#endif
    }

    if (stk->data == NULL
        ERR_HANDLED_MSSG(LOGFILE, ERR_REALLOC_STACK))
    {
        StackResizeDump(LOGFILE, stk);

        return;
    }

#ifdef POISON_ELEM_T_PROTECT
    for (size_t index = stk->size; index < stk->capacity; index++)
    {
        stk->data[index] = POISON_ELEM_T_STACK;
    }
#endif
}

void StackResizeDump_(FILE* logfile, const Stack* stk, size_t new_size)
{
    ASSERT(stk     != NULL);

    if (logfile == NULL) logfile = stderr;

    fprintf(logfile,
            "Resize. Params: stk = %p new_size = %lu\n",
            stk, new_size);
    fflush(logfile);

    StackDump(logfile, stk);
}

#undef StackDumpResize

