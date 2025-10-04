#include <stdio.h>

int main(void) {
    float balance = 199.0f;
    float withdrawal = 760.0f;
    while (balance > 0) {
        if (balance >= withdrawal) {
            balance -= withdrawal;
            printf("Withdrew $%.2f. New balance: $%.2f\n", withdrawal, balance);
        } else {
            printf("Insufficient funds to withdraw $%.2f.\n", withdrawal);
            break;
        }
    }
    return 0;
}