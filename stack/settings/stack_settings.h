
/// @file stack_settings.h
///
/// @brief Внутренние настройки стека

#include <stdio.h>

#include "stack_elem_t.h" ///< Файл, изменяемый пользователем
                          ///  перед использованием стека

FILE* const LOGFILE = fopen(logfilename, "w");

#include "stack_poison_settings.h"
#include "stack_error_settings.h"

#ifdef CANARY_PROTECT
    #include "stack_canary_settings.h"
#endif

#ifdef HASH_PROTECT
    #include "stack_hash_settings.h"
#endif

