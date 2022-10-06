
#include <stdlib.h>

#define UNIT_TESTING_CPP
#include "unit_testing.h"

#include "colorful_text.h"
#include "../rwfile/rwfile.h"
#include "../strings/strings.h"

#include "../error_handling/error_handling.h"

void unit_test(const char* func_name,
               const char* tests_filename,
               size_t      size,
               size_t    (*get_one_test_buf)   (void*, const char*),
               int       (*run_one_test)       (void*),
               void      (*failed_test_report) (const void*))
{
    ASSERT(tests_filename     != NULL);
    ASSERT(size               != 0);
    ASSERT(get_one_test_buf   != NULL);
    ASSERT(run_one_test       != NULL);
    ASSERT(failed_test_report != NULL);

    ERR_TYPE_RWFILE err_read_whole_file = 0;
    char* buffer = (char*) read_whole_file(tests_filename,
                                           sizeof(char),
                                           NULL,
                                           &err_read_whole_file);

    if (err_read_whole_file)
    {
        ERR_REPORT_MSSG(stderr, "error during file reading");
        return;
    }

    size_t n_tests = count_chars_str(buffer, "\n", 1, 1);
    ASSERT(n_tests != 0);

    unsigned char *tests = (unsigned char*) calloc(n_tests, size);
    if (tests == NULL)
    {
        ERR_REPORT_MSSG(stderr, "tests calloc error");
        free(buffer);
        return;
    }

    char* buffer_ptr = buffer;
    for (size_t test = 0; test < n_tests; test++)
    {
        buffer_ptr += get_one_test_buf(tests + size * test, buffer_ptr);
    }

    YELLOW(printf("Unit test for func %s is started\n", func_name);)
    
    char* results = (char*) calloc(n_tests, sizeof(char));
    if (results == NULL) {
        ERR_REPORT_MSSG(stderr, "results calloc error");
        free(tests);
        free(buffer);
        return;
    }
            
    for (size_t test = 0; test < n_tests; test++)
    {
    
        YELLOW(printf("Test # %3lu: ", test + 1);)
    
        char result = (run_one_test(tests + size * test) == 1);
        results[test] = result;
        
        if (result)
        {
        
            GREEN(printf("Ok\n");)
        
        }
        else
        {

            RED(printf("Failed\n");)
            RED(failed_test_report(tests + size * test);)
        
        }
    }

    report(results, n_tests);

    free(results);
    free(tests);
    free(buffer);
    
    YELLOW(printf("Unit test is over\n\n");)

}

void report(const char* results, size_t n_tests)
{
    ASSERT(results, "results is invalid");
    if (n_tests == 0) return;

    char none_failed_tests = 1;
    
    RED(printf("Failed test numbers are: ");)
    
    for (size_t test = 0; test < n_tests; test++)
    {
        if (results[test] == 0)
        {
            none_failed_tests = 0;
        
            RED(printf("%lu ", test + 1);)
        
        }
    }

    if (none_failed_tests)
    {
    
        GREEN(printf("None");)
    
    }
    printf("\n");
}

