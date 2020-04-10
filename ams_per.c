#include <stdio.h>
#include <math.h>

int checkAms (int num) {
    int hun = num / 100;
    int doz = (num - (hun * 100)) / 10;
    int uni = num % 10;

    int ams = pow((double)hun, 3) + pow((double)doz, 3) + pow((double)uni, 3);

    if (ams == num){
        printf ("The number %d is an Armstrong number\n", num);
    }
    else {
        printf ("The number %d is not an Armstrong number\n", num);
    }
}

int checkPre (int num) {

    int dividers = num / 2;
    int sum = 0;

    for (int i = 1; i <= dividers; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    if (num == sum) {
        printf ("The number %d is a Perfect number\n", num);
    }
    else {
        printf ("The number %d is not a Perfect number\n", num);
    }
}
int main () {

    int checkNum = 0;

    printf ("Please insert a number : ");
    scanf ("%d", &checkNum);

    checkAms (checkNum);
    checkPre (checkNum);

    return 0;
}
