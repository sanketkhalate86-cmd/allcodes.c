#include <stdio.h>

int main() {
    int score;
    score = 95;
    int numberOfStudents = 30;
    int totalScore = score * numberOfStudents;

    printf("The score is: %d\n", score);
    printf("Number of students: %d\n", numberOfStudents);
    printf("The total combined score is: %d\n", totalScore);

    return 0;
}