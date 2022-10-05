
#include <stdio.h>

#define STACK_CPP
#include "stack_dump.h"

void StackDump_(FILE* logfile, const Stack* stk)
{
    if (logfile == NULL) logfile = stderr;

    if (stk == NULL)
    {
        fprintf(logfile, "given NULL ptr in stk\n");
        
        return;
    }

    fprintf(logfile,
            "Stack [%p] \"%s\" at %s at %s(%lu):\n",
            stk,
            stk->var_data.var_name,
            stk->var_data.func_name,
            stk->var_data.file,
            stk->var_data.line);

    fprintf(logfile, "{\n");

#ifdef CANARY_PROTECT
    fprintf(logfile, "left struct canary:  ");
    FPRINTF_CANARY_STACK(logfile, &(stk->l_canary));

    fprintf(logfile, "right struct canary: ");
    FPRINTF_CANARY_STACK(logfile, &(stk->r_canary));
#endif

#ifdef HASH_PROTECT
    HASH_TYPE_STACK hash = stk->hash_struct_value;
    
    fprintf(logfile, "struct hash value: ");
    FPRINTF_HASH_STACK(logfile, &hash);

    hash = GetHashStructStack_(stk);

    fprintf(logfile, "real struct hash:  ");
    FPRINTF_HASH_STACK(logfile, &hash)
#endif

    fprintf(logfile,
            "data [%p]\n"
            "size     = %lx\n"
            "capacity = %lx\n",
            stk->data,
            stk->size,
            stk->capacity);

    StackDumpElems_(logfile, stk);

    fprintf(logfile, "}\n\n");

    fflush(logfile);
}

void StackDumpElems_(FILE* logfile, const Stack* stk)
{    
    ASSERT(stk     != NULL);

    if (logfile == NULL) logfile = stderr;

    fprintf(logfile, "\t{\n");

    if (stk->data == NULL ||
        stk->data == POISON_ELEM_T_PTR_STACK)
    {
        fprintf(logfile, "\tBad data ptr\n\t}\n");

        return;
    }


#ifdef CANARY_PROTECT
    fprintf(logfile, "\tleft  data canary: ");
    FPRINTF_CANARY_STACK(logfile, L_CANARY_PTR_DATA);
#endif

#ifdef HASH_PROTECT
    HASH_TYPE_STACK hash = stk->hash_data_value;

    fprintf(logfile, "\tdata hash value: ");
    FPRINTF_HASH_STACK(logfile, &hash);
        
    hash = GetHashDataStack_(stk);

    fprintf(logfile, "\treal data hash:  ");
    FPRINTF_HASH_STACK(logfile, &hash);
#endif

    for (size_t index = 0; index < stk->capacity; index++)
    {
        fprintf(logfile,
                "\t%c [%2lu] = ",
                (index < stk->size) ? '*' : ' ',
                index + 1);

        FPRINTF_ELEM_T_STACK(logfile, stk->data + index);
    }

#ifdef CANARY_PROTECT
    fprintf(logfile, "\tright data canary: ");
    FPRINTF_CANARY_STACK(logfile, R_CANARY_PTR_DATA);
#endif

    fprintf(logfile, "\t}\n");
}
