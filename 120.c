#include <stdio.h>

int main(void) {
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    printf("The maximum value is %d\n", max);
    return 0;
}