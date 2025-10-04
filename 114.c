#include <stdio.h>

int main(void) {
    int temperature = 78; // Celsius
    if (temperature <= 0) {
        printf("It's freezing! \n");
    } else {
        printf("It's not freezing \n");
    }
    return 0;
}