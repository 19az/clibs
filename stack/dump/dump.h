
/// @file stack_dump.h
///
/// @brief Дамп стека в логфайл

#ifndef STACK_DUMP_H
#define STACK_DUMP_H

#include "stack/stack.h"

/// @brief Делает дамп полей структуры стека в логфайл
///
/// @param logfile поток, в который печатать дамп
/// @param[in] stk указатель на стек
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататся в stderr
void StackDump_(FILE* logfile, const Stack* stk);

/// @brief Позволяет добавть в дамп информацию о месте вызова дампа

#ifdef NDEBUG
    #define StackDump(logfile, stk) ((void) 0)
#else
    #define StackDump(logfile, stk) \
        DUMP(logfile);              \
                                    \
        StackDump_(logfile, stk);

#endif

#endif /* STACK_DUMP_H */

