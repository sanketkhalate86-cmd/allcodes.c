#include <stdio.h>

int main() {
    // Sum numbers until sum > 20
    int sum = 0, i = 1;
    while (sum <= 20) {
        sum += i++;
    }
    printf("Final sum: %d", sum);
    return 0;
}