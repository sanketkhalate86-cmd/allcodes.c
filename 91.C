#include <stdio.h>

int main() {
    int countdown = 2;
    while(countdown >= 0) {
        printf("%d ", countdown);
        countdown--;
    }
    return 0;
}