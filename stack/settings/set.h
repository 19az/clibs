
/// @file stack_settings.h
///
/// @brief Внутренние настройки стека

#include <stdio.h>

#include "elem_t/set.h" ///< Файл, настраиваемый пользователем
                        ///  перед использованием стека

FILE* const LOGFILE = fopen(LOGFILENAME, "w");

#ifdef CANARY_PROTECT
    #include "canary/set.h"
#endif

#include "error/set.h"

#ifdef HASH_PROTECT
    #include "hash/set.h"
#endif

#include "poison/set.h"

