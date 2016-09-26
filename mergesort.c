#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*defining size of array*/
#define ARRAY_MAX 30000

/*merge that is a sub function of the merge_sort function*/
void merge(int *array, int *workspace, int len){
    int i, j, k;
    i = 0;
    j = len/2;
    k = 0;
    while(i<len/2 && j<len){
        if(array[i] <= array[j]){
            workspace[k] = array[i];
            i++;
            k++;
        }else if(array[j] < array[i]){
            workspace[k] = array[j];
            j++;
            k++;
        }
    }
    while(i<len/2){
        workspace[k] = array[i];
        i++;
        k++;
    }
    while(j<len){
        workspace[k] = array[j];
        j++;
        k++;
    }

}

/*merge sort function which is called upon in main*/
void merge_sort(int *a, int *w, int n){
    int i;
    if(n < 2){
        return;
    }else{
        merge_sort(a, w, n/2);
        merge_sort(a+(n/2), w, (n-(n/2)));
        merge(a, w ,n);
        for(i=0; i < n; i++){
            a[i] = w[i];
        }
    }   
}


/*main function which declares variables and runs insertion sort*/
int main(void){
    int my_array[ARRAY_MAX];
    int workspace[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    /*while loop to check for count and if there is more input*/
    while(count<ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    /*starting the clock and call the insertion sort method*/
    start = clock();
    merge_sort(my_array, workspace, count);
    end = clock();
    for(i=0; i<count; i++){
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr,"%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS; /*exiting the loop*/
}
