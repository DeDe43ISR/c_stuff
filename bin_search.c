#include <stdio.h>

int dataBase[10] = {3 ,6 ,12 ,23 ,28 ,46 ,49 ,68 ,78 ,83};

int search (int num) {

    int pointer, lower = 0, upper = 9, flag = 0;

    while (lower <= upper) {

        pointer = (upper + lower) / 2;

        if (dataBase[pointer] == num) {
            flag = 1;
            break;
        }
        else if (dataBase[pointer] > num) 
            upper = pointer - 1;

        else 
            lower = pointer + 1;
    }

    if(flag == 0)
        printf("%d  value not found\n",num);
    else
        printf("%d value  found at %d position\n",num ,pointer);
    }

int main () {

    int token = 0;

    printf ("Please insert a number to search : ");
    scanf ("%d", &token);

    search (token);
    return 0;
}
