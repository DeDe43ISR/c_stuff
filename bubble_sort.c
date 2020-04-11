#include <stdio.h>

int main () {

    int dataBase[10] = {66 ,5 ,-32 ,25 ,88 ,16 ,9 ,48 ,98 ,3};
    int spots = 9,first = 0,sec = 1,strikes = 0, temp;

    printf("\nThe wrong order : ");
    for (int i = 0; i <= spots; i++)
        printf("%d ", dataBase[i]);

    do {
        first = 0;
        sec = 1;
        strikes = 0;
        while (first < spots) {
            if (dataBase[first] > dataBase[sec]){
                temp = dataBase[first];
                dataBase[first] = dataBase[sec];
                dataBase[sec] = temp;
                strikes++;
            }
            first++;
            sec++;
        }

        printf("\nThe current order : ");
        for (int i = 0; i <= spots; i++)
            printf("%d ", dataBase[i]);
    } while (strikes > 0);
    printf("\nThe right order : ");
    for (int i = 0; i <= spots; i++)
        printf("%d ", dataBase[i]);
    return 0;
}

