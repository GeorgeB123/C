#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "queue.h"

int main(void){
    queue q = queue_new();
    int i = 0;
    double item=0;
    while(1 == scanf("%lg", &item)){
        if(item <5){
            enqueue(q, item);
        }else{
            dequeue(q);
        }
        i++;
        if(i==5){
            queue_print(q);
        }
    }
    queue_free(q);
    return EXIT_SUCCESS;
}
