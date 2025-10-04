#include <stdio.h>

int main(void) {
    char light_color = 'Y';
    if (light_color == 'G') {
        printf("Go\n");
    } else if (light_color == 'Y') {
        printf("Slow down\n");
    } else if (light_color == 'R') {
        printf("Stop\n");
    } else {
        printf("Invalid color\n");
    }
    return 0;
}