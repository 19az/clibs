
#include <string.h>

#include "text/text.h"
#include "unit_testing/unit_testing.h"

#include "error_handling/error_handling.h"

//text-decl---------------------------------------------------------------------

const size_t MAXLEN_TEXT = 10;

size_t get_one_test_text(void *voidptr_test, const char *buffer);

int run_one_test_text(void *voidptr_test);

void failed_test_report_text(const void *voidptr_test);

void *parse_buffer_char(char *buffer, size_t *n_lines);

void print_char_stream(FILE *stream, const void *part);

const Part partition_char = 
{
    1,
    parse_buffer_char,
    print_char_stream
};

//main--------------------------------------------------------------------------

int main() {
    unit_test("construct, print and destruct from text",
              "text_test.txt",
              sizeof(char[MAXLEN_TEXT]),
              get_one_test_text,
              run_one_test_text,
              failed_test_report_text);

    return 0;
}

//text-def----------------------------------------------------------------------

void *parse_buffer_char(char *buffer, size_t *n_chars) {
    ASSERT(buffer != NULL);
    ASSERT(n_chars != NULL);

    *n_chars = strlen(buffer);

    return strdup(buffer);
}

void print_char_stream(FILE *stream, const void *ch) {
    ASSERT(stream != NULL);
    ASSERT(ch != NULL);

    fputc(*(const char*) ch, stream);
    fputc('\n', stream);
}

size_t get_one_test_text(void *voidptr_test, const char *buffer) {
    ASSERT(voidptr_test != NULL);
    ASSERT(buffer       != NULL);

    const char **test = (const char**) voidptr_test;
    *test = buffer;

    return strlen(buffer) + 1;
}

int run_one_test_text(void *voidptr_test) {
    ASSERT(voidptr_test != NULL);

    const char **test = (const char**) voidptr_test;

    Text *text = construct_text_file(*test, &partition_char);
    putchar('\n');
    print_all_parts_stream(stdout, text);
    putchar('\n');

    destruct_text(text);
    return 1;
}

void failed_test_report_text(const void *voidptr_test) {
    ASSERT(voidptr_test != NULL);
}

