#include<stdio.h>

void sort (int *dataBase, int arraySize) {
    
    int s = 1, limit = (arraySize - 1), temp, counter = 1;
    while (s) {
        s = 0;
        while (counter < limit) {
            if (counter == 0) {
                counter++;
            }
            printf ("counter : %d\n", counter);
            if (dataBase[counter] < dataBase[counter - 1]) {
                temp = dataBase[counter];
                dataBase[counter] = dataBase[counter - 1];
                dataBase[counter - 1] = temp;
                printf("%d is bigger %d\n", dataBase[counter], dataBase[counter - 1]);
                counter--;
                s = 1;
            }
            else if (dataBase[counter] > dataBase[counter + 1]) {
                temp = dataBase[counter];
                dataBase[counter] = dataBase[counter + 1];
                dataBase[counter + 1] = temp;
                printf("%d is smaller %d\n", dataBase[counter], dataBase[counter + 1]);
                s = 1;
            }
            else {
                counter++;
                s++;
            }
        }
    }
}

int main () {
    int dataBase[] = {15, 56, 12, 21, 1, 659, 33, 83, 51, 3, 135, 2};
    int arraySize = sizeof dataBase / sizeof dataBase[0];
    int counter;
    for (counter = 0; counter < arraySize; counter++)
        printf("%d%s", dataBase[counter], counter == arraySize- 1 ? "\n" : " "); // Prints old array
    sort(dataBase, arraySize);
    for (counter = 0; counter < arraySize; counter++)
        printf("%d%s", dataBase[counter], counter == arraySize- 1 ? "\n" : " "); // Prints new array
    return 0;
}
