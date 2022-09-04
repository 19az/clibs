#include <stdio.h>

#include "rwfile_ut.h"
#include "../rwfile.h"
#include "../../strings/strings.h"
#include "../../unit_testing/colorful_text.h"

void get_file_size_ut() {
    YELLOW(printf("Unit test for get_file_size() started\n"););
    for (size_t i = 0; i < nTests; i++) {
        YELLOW(printf("Test # %lu:\n", i);)
        int result = get_file_size(files[i]);
        if (result == filesize[i]) {
            GREEN(printf("OK\n");)
        } else {
            RED(printf("Failed\n");)
            printf("filename: %s\n"
                   "filesize(exp): %d\n"
                   "filesize(res): %d\n",
                   files[i], filesize[i], result);
        }
    }
    YELLOW(printf("Unit test is over\n\n"););
}

const int MAXBUFFERSIZE = 1e2;

void read_file_ut() {
    YELLOW(printf("Unit test for read_file() started\n"););
    for (size_t i = 0; i < nTests; i++) {
        YELLOW(printf("Test # %lu:\n", i);)
        char buffer[MAXBUFFERSIZE] = {};
        int result = read_file(files[i], buffer, (size_t) filesize[i]);
        if (result == filesize[i]) {
            if (my_strcmp(buffer, filedata[i]) == 0) {
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
                   "filesize(exp): %d\n"
                   "filesize(res): %d\n",
                   files[i], filesize[i], result);
        }
    }
    YELLOW(printf("Unit test is over\n\n"););
}

int main() {
    get_file_size_ut();
    read_file_ut();

    return 0;
}
