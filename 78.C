#include <stdio.h>

int main() {
    // Calculate sum of 1 to 5
    int sum = 0;
    for (int i = 1; i <= 5; i++) {
        sum += i;
    }
    printf("Sum: %d", sum);
    return 0;
}