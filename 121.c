#include <stdio.h>
int main() {
    int num, i;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num > 0) {
        for (i = 1; i * i * i <= num; i++) {
            if (i * i * i == num) {
                printf("Perfect cube\n");
                return 0;
            }
        }
        printf("Not a perfect cube\n");
    } else {
        printf("Invalid input\n");
    }
    return 0;
}