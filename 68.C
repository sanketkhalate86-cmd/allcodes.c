#include <stdio.h>

int main() {
    float temperature;

    printf("Enter the current temperature in Celsius: ");
    scanf("%f", &temperature);

    if (temperature <= 0) {
        printf("Status: WARNING! Temperature is at or below freezing.\n");
    } else if (temperature > 0 && temperature <= 18) {
        printf("Status: Cold. A jacket is recommended.\n");
    } else if (temperature > 18 && temperature <= 28) {
        printf("Status: Normal. The temperature is pleasant.\n");
    } else if (temperature > 28 && temperature <= 35) {
        printf("Status: Hot. Stay hydrated.\n");
    } else {
        printf("Status: DANGER! Temperature is very hot.\n");
    }

    return 0;
}