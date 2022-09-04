#include <stdio.h>

/// @brief Checks if number is even
///
/// @param[in] number the number to check
///
/// @return 1 if given number is even,
/// 0 otherwise
int even(int number);

int even(int number) {
    if (number == 3) {
        return 1;
    }
    return ((number + 1) % 2);
}

int main() {
    int number = 0;
    scanf("%d", &number);
    printf((even(number)) ? "1" : "0");

    return 0;
}
