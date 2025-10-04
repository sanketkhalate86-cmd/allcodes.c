#include <stdio.h>

int main() {
    
    float sensor1_value, sensor2_value;
    float sum, difference;
    printf("Enter the value from Sensor 1: ");
    scanf("%f", &sensor1_value);
    
    printf("Enter the value from Sensor 2: ");
    scanf("%f", &sensor2_value);
    sum = sensor1_value + sensor2_value;
    difference = sensor1_value - sensor2_value;

    printf("\n--- Calculation Results ---\n");
    printf("Sum (Sensor 1 + Sensor 2)      = %.2f\n", sum);
    printf("Difference (Sensor 1 - Sensor 2) = %.2f\n", difference);

    return 0; 
}