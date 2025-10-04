#include <stdio.h>
#include <stdbool.h> 

int main(void) {
    bool is_active = true;
    if (is_active) {
        printf("The system is active \n");
    } else {
        printf("The system is inactive \n");
    }
    return 0;
}