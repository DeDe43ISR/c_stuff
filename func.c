#include <stdio.h>

int check_odd (int num) {
    if ((num % 2) == 0) {
        printf("\nThe number is even\n");
    }
    else {
        printf("\nThe number is odd\n");
    }
}

int main () {
    int test_num = 0;
    
    printf("\nPlease Insert a number : ");
    scanf("%d", &test_num);

    check_odd (test_num);
    return 0;
}
