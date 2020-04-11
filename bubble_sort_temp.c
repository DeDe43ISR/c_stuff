#include <stdio.h>
 
void bubble_sort (int *dataBase, int arraySize) {
    int counter, temp, limit = arraySize, s = 1;
    while (s) {
        s = 0;
        for (counter = 1; counter < limit; counter++) {
            if (dataBase[counter] < dataBase[counter - 1]) {
                temp = dataBase[counter];
                dataBase[counter] = dataBase[counter - 1];
                dataBase[counter - 1] = temp;
                s = 1;
            }
        }
        limit--;
    }
}
 
int main () {
    int dataBase[] = {15, 56, 12, -21, 1, 659, 3, 83, 51, 3, 135, 0};
    int arraySize = dataBase / sizeof dataBase[0];
    int counter;
    for (counter = 0; counter < n; counter++)
        printf("%d%s", dataBase[counter], counter == arraySize- 1 ? "\n" : " ");
    bubble_sort(dataBase, n);
    for (counter = 0; counter < n; counter++)
        printf("%d%s", dataBase[counter], counter == arraySize- 1 ? "\n" : " ");
    return 0;
}
