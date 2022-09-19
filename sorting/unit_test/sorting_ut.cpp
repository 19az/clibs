
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../sorting.h"
#include "../../unit_testing/unit_testing.h"

#include "../../error_handling/error_handling.h"

//swap-dec---------------------------------------------------------------------

const size_t MAXLEN_SWAP = 20;
struct SwapArgs {
    size_t size = 0;
    char a     [MAXLEN_SWAP] = {};
    char b     [MAXLEN_SWAP] = {};
    char a_swap[MAXLEN_SWAP] = {};
    char b_swap[MAXLEN_SWAP] = {};
};

size_t       get_one_test_swap(      void *voidptr_test, const char *buffer);
int          run_one_test_swap(      void *voidptr_test);
void   failed_test_report_swap(const void *voidptr_test);

//reverse-dec------------------------------------------------------------------

const size_t MAXLEN_REVERSE = 20;
struct ReverseArgs {
    size_t count = 0;
    size_t size  = 0;
    char arr     [MAXLEN_REVERSE] = {};
    char expected[MAXLEN_REVERSE] = {};
    char result  [MAXLEN_REVERSE] = {};
};

size_t       get_one_test_reverse(      void *voidptr_test, const char *buffer);
int          run_one_test_reverse(      void *voidptr_test);
void   failed_test_report_reverse(const void *voidptr_test);

//sorting-dec-------------------------------------------------------------------

const size_t MAXLEN_SORTING = 20;
struct SortingArgs {
    size_t count = 0;
    size_t size  = 0;
    char arr     [MAXLEN_SORTING] = {};
    char expected[MAXLEN_SORTING] = {};
    char result  [MAXLEN_SORTING] = {};
};

size_t       get_one_test_sorting(      void *voidptr_test, const char *buffer);
int          comp_char           (const void *a,            const void *b);
int          run_one_test_sorting(      void *voidptr_test, void (*sorting)(void*,
                                                                            size_t,
                                                                            size_t,
                                                                            int (*)(const void*, const void*)));
int          run_one_test_bubble (      void *voidptr_test);
int          run_one_test_quick  (      void *voidptr_test);
void   failed_test_report_sorting(const void *voidptr_test);

int main() {
    unit_test("swap",
              "swap_tests.txt",
              sizeof(SwapArgs),
              get_one_test_swap,
              run_one_test_swap,
              failed_test_report_swap);

    unit_test("reverse",
              "ro_tests.txt",
              sizeof(ReverseArgs),
              get_one_test_reverse,
              run_one_test_reverse,
              failed_test_report_reverse);

    unit_test("bubble_sort",
              "sorting_tests.txt",
              sizeof(SortingArgs),
              get_one_test_sorting,
              run_one_test_bubble,
              failed_test_report_sorting);

    unit_test("quick_sort",
              "sorting_tests.txt",
              sizeof(SortingArgs),
              get_one_test_sorting,
              run_one_test_quick,
              failed_test_report_sorting);

    return 0;
}

//swap-def------------------------------------------------------------------------

size_t get_one_test_swap(void *voidptr_test, const char *buffer) {
    SwapArgs *test = (SwapArgs*) voidptr_test;

    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%lu %s %s %n",
                        &test->size,
                        test->a,
                        test->b,
                        &bytes_read);
    ASSERT(result == 3 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    return (size_t) bytes_read;
}

int run_one_test_swap(void *voidptr_test) {
    SwapArgs *test = (SwapArgs*) voidptr_test;

    memcpy(test->a_swap, test->a, MAXLEN_SWAP);
    memcpy(test->b_swap, test->b, MAXLEN_SWAP);
    swap_objects(test->a_swap, test->b_swap, test->size);
    return (!memcmp(test->a_swap, test->b, test->size) &&
            !memcmp(test->b_swap, test->a, test->size));
}

void failed_test_report_swap(const void *voidptr_test) {
    const SwapArgs *test = (const SwapArgs*) voidptr_test;

    printf("swap size      = %lu\n"
           "1st object     = %s\n"
           "2nd object     = %s\n"
           "1st after swap = %s\n"
           "2nd after swap = %s\n",
           test->size,
           test->a,
           test->b,
           test->a_swap,
           test->b_swap);
}

//reverse-def------------------------------------------------------------------

size_t get_one_test_reverse(void *voidptr_test, const char *buffer) {
    ReverseArgs *test = (ReverseArgs*) voidptr_test;

    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%lu %lu %s %s %n",
                        &test->count,
                        &test->size,
                        test->arr,
                        test->expected,
                        &bytes_read);
    ASSERT(result == 4 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    return (size_t) bytes_read;
}

int run_one_test_reverse(void *voidptr_test) {
    ReverseArgs *test = (ReverseArgs*) voidptr_test;
    
    memcpy(test->result, test->arr, MAXLEN_REVERSE);
    reverse_order(test->result, test->count, test->size);
    return !memcmp(test->result, test->expected, MAXLEN_REVERSE);
}

void failed_test_report_reverse(const void *voidptr_test) {
    const ReverseArgs *test = (const ReverseArgs*) voidptr_test;

    printf("count    = %lu\n"
           "size     = %lu\n"
           "array    = %s\n"
           "expected = %s\n"
           "result   = %s\n",
           test->count,
           test->size,
           test->arr,
           test->expected,
           test->result);
}

//sorting-def-------------------------------------------------------------------

size_t get_one_test_sorting(void *voidptr_test, const char *buffer) {
    SortingArgs *test = (SortingArgs*) voidptr_test;

    int bytes_read = 0;
    int result = sscanf(buffer,
                        "%lu %lu %s %s %n",
                        &test->count,
                        &test->size,
                        test->arr,
                        test->expected,
                        &bytes_read);
    ASSERT(result == 4 || result == EOF, "cannot read all arguments");
    if (result == EOF) return 0;

    return (size_t) bytes_read;
}

int comp_char(const void *a, const void *b) {
    return *(const char*)a - *(const char*)b;
}

int run_one_test_sorting(void *voidptr_test, void (*sort)(void*,
                                                          size_t,
                                                          size_t,
                                                          int (*)(const void*, const void*))) {
    SortingArgs *test = (SortingArgs*) voidptr_test;
    
    memcpy(test->result, test->arr, MAXLEN_SORTING);
    sort(test->result, test->count, test->size, comp_char);
    return !memcmp(test->result, test->expected, MAXLEN_SORTING);
}

int run_one_test_bubble(void *voidptr_test) {
    return run_one_test_sorting(voidptr_test, bubble_sort);
}

int run_one_test_quick(void *voidptr_test) {
    return run_one_test_sorting(voidptr_test, quick_sort);
}

void failed_test_report_sorting(const void *voidptr_test) {
    const SortingArgs *test = (const SortingArgs*) voidptr_test;

    printf("count    = %lu\n"
           "size     = %lu\n"
           "array    = %s\n"
           "expected = %s\n"
           "result   = %s\n",
           test->count,
           test->size,
           test->arr,
           test->expected,
           test->result);
}

#include "../../error_handling/undef_error_handling.h"
