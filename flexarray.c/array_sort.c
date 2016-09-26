#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

static void array_print(int *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

/*insertion sort function which is called upon in main*/
void insertion_sort(int *a, int n){
    /*variable declaration*/
    int i, j;
    int key;
    /*for and while loops to run through each i and move it appropriately*/
    for(i=1; i<n;i++){
        key = a[i];
        j=i-1;
        while(key<a[j] && j>=0){
            a[j+1]=a[j];
            --j;
        }
        a[j+1]=key;
    }/*exiting the for and while loop*/
}

int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = emalloc(capacity * sizeof my_array[0]);
    
    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
            
        }
        my_array[itemcount++] = item;
    }
    insertion_sort(my_array, itemcount);
    array_print(my_array, itemcount);
    free(my_array);
    return EXIT_SUCCESS;
}
