
/// @file stack_dump.h
///
/// @brief Дамп стека в логфайл

#ifndef STACK_DUMP_H
#define STACK_DUMP_H

#include "../stack.h"

/// @brief Делает дамп полей структуры стека в логфайл
///
/// @param logfile поток, в который печатать дамп
/// @param[in] stk указатель на стек
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататся в stderr
void StackDump_(FILE* logfile, const Stack* stk);

/// @brief Делает дамп элементов стека в логфайл
///
/// @param logfile поток, в который печатать дамп
/// @param[in] stk указатель на стек
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататся в stderr
void StackDumpElems_(FILE* logfile, const Stack* stk);

#endif /* STACK_DUMP_H */

