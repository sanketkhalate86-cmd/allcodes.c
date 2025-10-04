#include <stdio.h>

int main() {
    char name[50];
    int age;
    
    printf("Please enter your name: ");
    scanf("%s", name);

    printf("Please enter your age: ");
    scanf("%d", &age);
    printf("\nHello, %s! You are %d years old.\n", name, age);

    return 0; 
}