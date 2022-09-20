
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../stdlike_strings.h"
#include "../../../unit_testing/colorful_text.h"

#define UnitTest(x, y)                    \
YELLOW(printf("Unit test for " #x "\n");) \
y;                                        \
YELLOW(printf("Unit test is over\n\n");)

void puts_test(const char *str);

void strlen_test(const char *str);

void strcpy_test(const char *str);

void strncpy_test(const char *str, size_t count);

void strcat_test(const char *dest, const char *src);

void strncat_test(const char *dest, const char *src, size_t count);

void fgets_test();

void strdup_test(const char *str);

void strchr_test(const char *str, int ch);

void puts_ut();

void strlen_ut();

void strcpy_ut();

void strncpy_ut();

void strcat_ut();

void strncat_ut();

void fgets_ut();

void strdup_ut();

void strchr_ut();

const int MAXLENDEST = 100; 

const char *filename_fgets_test = "fgets_test.txt";

int main() {
    UnitTest(puts,           puts_ut())
    UnitTest(strlen,         strlen_ut())
    UnitTest(strcpy,         strcpy_ut())
    UnitTest(strncpy,        strncpy_ut())
    UnitTest(strcat,         strcat_ut())
    UnitTest(strcat,         strncat_ut())
    UnitTest(fgets,          fgets_ut())
    UnitTest(strdup,         strdup_ut())
    UnitTest(strchr,         strchr_ut())

    return 0;
}

void puts_test(const char *str) {
    static int nTest = 1;
    YELLOW(printf("Test # %d\n", nTest++);)

    printf("Func from string.h:\n");
    puts(str);
    printf("My func:\n");
    my_puts(str);
}

void strlen_test(const char *str) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    size_t std_res = strlen(str);
    size_t my_res  = my_strlen(str);
    if (std_res != my_res) {
        RED(printf("Failed\n");)
        printf("String: %s\n"
               "Std func result: %lu\n"
               "My func result: %lu\n", str, std_res, my_res);
    } else {
        GREEN(printf("Ok\n");)
    }
}

void strcpy_test(const char *str) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    char dest1[MAXLENDEST] = {};
    char dest2[MAXLENDEST] = {};
    strcpy(dest1, str);
    my_strcpy(dest2, str);
    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("String: %s\n"
               "Std func result: %s\n"
               "My func result:  %s\n", str, dest1, dest2);
    } else {
        GREEN(printf("Ok\n");)
    }
}   

void strncpy_test(const char *str, size_t count) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    char dest1[MAXLENDEST] = {};
    char dest2[MAXLENDEST] = {};
    strncpy(dest1, str, count);
    my_strncpy(dest2, str, count);
    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("String: %s\n"
               "Count: %lu\n"
               "Std func result: %s\n"
               "My func result:  %s\n", str, count, dest1, dest2);
    } else {
        GREEN(printf("Ok\n");)
    }
}

void strcat_test(const char *dest, const char *src) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)
        
    char dest1[MAXLENDEST] = {};
    char dest2[MAXLENDEST] = {};
    strcpy(dest1, dest);
    strcpy(dest2, dest);
    strcat(dest1, src);
    my_strcat(dest2, src);
    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("Dest string: %s\n"
               "Src string: %s\n"
               "Std func result: %s\n"
               "My func result:  %s\n", dest, src, dest1, dest2);
    } else {
        GREEN(printf("Ok\n");)
    }
} 

void strncat_test(const char *dest, const char *src, size_t count) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    char dest1[MAXLENDEST] = {};
    char dest2[MAXLENDEST] = {};
    strcpy(dest1, dest);
    strcpy(dest2, dest);
    strncat(dest1, src, count);
    my_strncat(dest2, src, count);
    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("Dest string: %s\n"
               "Src string: %s\n"
               "Count: %lu\n"
               "Std func result: %s\n"
               "My func result:  %s\n", dest, src, count, dest1, dest2);
    } else {
        GREEN(printf("Ok\n");)
    }
}

void fgets_test() {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    FILE *file = NULL;
    file = fopen(filename_fgets_test, "r");
    char dest1[MAXLENDEST] = {};
    fgets(dest1, MAXLENDEST, file);
    fclose(file);

    file = fopen(filename_fgets_test, "r");
    char dest2[MAXLENDEST] = {};
    my_fgets(dest2, MAXLENDEST, file);
    fclose(file);

    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("Std func string: %s\n"
               "My func string: %s\n", dest1, dest2);
    } else {
        GREEN(printf("Ok\n"););
    }
}

void strdup_test(const char *str) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    char *dest1 = strdup(str);
    char *dest2 = my_strdup(str);
    if (strcmp(dest1, dest2)) {
        RED(printf("Failed\n");)
        printf("Std func string: %s\n"
               "My func string: %s\n", dest1, dest2);
    } else {
        GREEN(printf("Ok\n"););
    }

    free(dest1);
    free(dest2);
}

void strchr_test(const char *str, int ch) {
    static int nTest = 1;
    YELLOW(printf("Test # %d: ", nTest++);)

    const char *std_res = strchr(str, ch);
    const char *my_res  = my_strchr(str, ch);
    if (my_res != std_res) {
        RED(printf("Failed\n");)
        printf("String: %s\n"
               "Char: %c\n"
               "Std func result: %c\n"
               "My func result: %c\n", str, ch, *std_res, *my_res);
    } else {
        GREEN(printf("Ok\n"););
    }
}

void puts_ut() {
    puts_test("");
    puts_test("a");
    puts_test("abc");
}

void strlen_ut() {
    strlen_test("");
    strlen_test("a");
    strlen_test("abc");
}

void strcpy_ut() {
    strcpy_test("");
    strcpy_test("a");
    strcpy_test("abc");
}

void strncpy_ut() {
    strncpy_test(""   , 1);
    strncpy_test("a"  , 1);
    strncpy_test("abc", 2);
}

void strcat_ut() {
    strcat_test("" , "");
    strcat_test("" , "a");
    strcat_test("a", "");
    strcat_test("a", "b");
}

void strncat_ut() {
    strncat_test(""   , ""   , 1);
    strncat_test(""   , "a"  , 1);
    strncat_test("a"  , ""   , 1);
    strncat_test("a"  , "b"  , 1);
    strncat_test("abc", "123", 2);
}

void fgets_ut() {
    fgets_test();
}

void strdup_ut() {
    strdup_test("");
    strdup_test("a");
    strdup_test("abc");
}

void strchr_ut() {
    strchr_test(""   , '\0');
    strchr_test(""   , 'a');
    strchr_test("abc", 'b');
    strchr_test("abc", 'd');
}
