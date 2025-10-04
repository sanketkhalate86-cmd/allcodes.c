#include <stdio.h>

// Function
int sumUpTo(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

// Example Usage
int main(void) {
    printf("Sum of numbers from 1 to 100 is %d.\n", sumUpTo(100));
    return 0;
}