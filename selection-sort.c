#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*defining size of array*/
#define ARRAY_MAX 30000

/*selection sort function which is called upon in main*/
void selection_sort(int *a, int n){
    /*variable declaration*/
    int i, j;
    int key, swap;
    /*nested for loops to run through each point*/
    for(i=0; i<(n-1);i++){
        key = i;
        for(j=i+1; j<n;j++){
            if(a[key]>a[j]){
                key = j;
            }
        }
        /*if statement to take into account if key is not i*/
        if(key != i){
            swap = a[i];
            a[i] = a[key];
            a[key]=swap;
        }
    }
}

/*main function which declares variables and runs selection sort*/
int main(void){
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    /*while loop to check for count and if there is more input*/
    while(count<ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    /*starting the clock and call the selection sort method*/
    start = clock();
    selection_sort(my_array, count);
    end=clock();
    for(i=0; i<count; i++){
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr,"%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;/*exiting the loop*/
}
