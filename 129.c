#include <stdio.h>

int main(void) {
    int temp = 25;
    if (temp > 30) {
        printf("It's hot outside \n");
    } else if (temp < 10) {
        printf("It's cold outside \n");
    } else {
        printf("The weather is pleasant \n");
    }
    return 0;
}