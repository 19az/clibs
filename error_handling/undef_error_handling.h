
#undef ERR_REPORT
#undef ERR_SUPPORT
#undef ERR_HANDLE
#undef ERR_HANDLED

#undef ASSERT
#undef assert
#define assert old_assert
#undef asserted

#include "undef_special_macros.h"
