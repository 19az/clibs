
#include <stdint.h>

/// @brief Хеш функция использующая gnu-hash алгоритм
///
/// @param[in] start указатель на начало данных
/// @param[in] finish указатель на конец данных
///
/// @return uint32_t значение хеша
uint32_t gnu_hash(const char *start, const char *finish);

