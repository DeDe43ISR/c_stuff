#include <stdio.h>

int main () {

    int dataBase[10] = {66 ,5 ,32 ,25 ,88 ,16 ,9 ,48 ,98 ,3};
    int spots = 9,low = 0,test = 1, temp;

    printf("\nThe wrong order : ");
    for (int i = 0; i <= spots; i++)
        printf("%d ", dataBase[i]);

    while (low <= spots) {
        test = low + 1;
        while (test <= spots) {
            if (dataBase[low] > dataBase[test]){
                temp = dataBase[low];
                dataBase[low] = dataBase[test];
                dataBase[test] = temp;
            }
            test++;
        }
    low ++;
    }
    printf("\nThe right order : ");
    for (int i = 0; i <= spots; i++)
        printf("%d ", dataBase[i]);
    return 0;
}

