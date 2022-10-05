
/// @file stack_dump.h
///
/// @brief Дамп стека в логфайл

/// @brief Делает дамп стека в логфайл
///
/// @param logfile поток, в который печатать дамп
/// @param[in] stk указатель на стек
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататся в stderr
void StackDump_(FILE* logfile, const Stack* stk);

/// @brief Dumping stack elements into log file
///
/// @param logfile поток, в который печатать дамп
/// @param[in] stk указатель на стек
///
/// @note Если в logfile передан NULL, то
/// дамп будет печататся в stderr
void StackDumpElems_(FILE* logfile, const Stack* stk);

