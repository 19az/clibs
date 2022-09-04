
/// Read one block of args for test from buffer
///
/// @param[out] voidptr_test void pointer to the place
/// where store test data
/// @param[in] buffer text buffer
///
/// @return number of read bytes
int get_one_test_buf(void *voidptr_test, const char *buffer);

/// @brief Checks if given number is equal to 42
///
/// @param[in] data void pointer to the number
///
/// @return 1 if given number is equal to 42,
/// 0 otherwise
char run_test(void *data);

/// @brief Prints to the stdout given number
/// and then prints "ans = 42\n"
///
/// @param[in] data void pointer to the number
void failed_test_report(const void *data);
