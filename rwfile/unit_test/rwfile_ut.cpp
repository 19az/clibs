
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rwfile.h"
#include "../../strings/strings.h"
#include "../../unit_testing/colorful_text.h"

const size_t n_tests = 4;
const char  *files[]    = {"testfiles/empty",
                           "testfiles/a",
                           "testfiles/abc",
                           "testfiles/file_does_not_exist" /* ,
                           "testfiles/huge" */};
const size_t filesize[] = {0,
                           2,
                           4,
                           0 /*,
                           (size_t) 8 * 1024 * 1024 * 1024 */};
const char  *filedata[] = {"",
                           "a\n",
                           "abc\n",
                           "" /* ,
                           "" */};
const int    read_res[] = {1,
                           1,
                           1,
                           0 /* ,
                           0 */};

const int MAXBUFFERSIZE = 1e2;

void get_file_size_ut();

void read_file_ut();

int main() {
    get_file_size_ut();
    read_file_ut();

    return 0;
}

void get_file_size_ut() {
    YELLOW(printf("Unit test for get_file_size() started\n"););
    for (size_t i = 0; i < n_tests; i++) {
        YELLOW(printf("Test # %lu:\n", i + 1);)
        size_t result = get_file_size(files[i]);
        if (result == filesize[i]) {
            GREEN(printf("OK\n");)
        } else {
            RED(printf("Failed\n");)
            printf("filename: %s\n"
                   "filesize(exp): %lu\n"
                   "filesize(res): %lu\n",
                   files[i], filesize[i], result);
        }
    }
    YELLOW(printf("Unit test is over\n\n"););
}

void read_file_ut() {
    YELLOW(printf("Unit test for read_file() started\n"););
    for (size_t i = 0; i < n_tests; i++) {
        YELLOW(printf("Test # %lu:\n", i + 1);)
        char *buffer = (char*) read_whole_file(files[i], sizeof(char));
        if ((buffer != NULL) == read_res[i]) {
            if (buffer == NULL || strcmp(buffer, filedata[i]) == 0) {
                GREEN(printf("OK\n");)
            } else {
                RED(printf("Failed\n");)
                printf("filename %s\n"
                       "filedata(exp): %s\n"
                       "filedata(res): %s\n",
                       files[i], filedata[i], buffer);
            }
        } else {
            RED(printf("Failed\n");)
            printf("filename: %s\n"
                   "read result(exp): %d\n"
                   "read result(res): %d\n",
                   files[i], read_res[i], buffer != NULL);
        }

        free(buffer);
    }
    YELLOW(printf("Unit test is over\n\n"););
}
