#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};
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
        }else{
            workspace[k] = array[j];
            j++;
        }
        k++;
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

/*merge sort function which is called upon in main*/
void merge_sort(int *a, int *w, int n){
    int i;
    if(n > 2){     
        if(n<15){
            insertion_sort(a, n);
        }else{
            merge_sort(a, w, n/2);
            merge_sort(a+(n/2), w, (n-(n/2)));
            merge(a, w ,n);
            for(i=0; i < n; i++){
                a[i] = w[i];
            }
        }
    }   
}    
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}
void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}
void flexarray_print(flexarray f) {
    int i;
    for(i = 0; i < f->itemcount ; i++){
        printf("%d\n", f->items[i]);
    }
}
  
void flexarray_sort(flexarray f) {
    int *array;
    array = emalloc(f->itemcount);
    merge_sort(f->items, array ,f->itemcount);
}
void flexarray_free(flexarray f) {
    free(f->items);
}
