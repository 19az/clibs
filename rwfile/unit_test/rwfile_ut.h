
const size_t nTests = 4;
const char *files[]    = {"testfiles/empty", "testfiles/a", "testfiles/abc", NULL};
const int filesize[]   = {                0,             2,               4,   -3};
const char* filedata[] = {               "",            "a\n",      "abc\n",   ""};

/// @brief Unit test function for get_file_size()
void get_file_size_ut();

/// @brief Unit test function for read_file()
void read_file_ut();
