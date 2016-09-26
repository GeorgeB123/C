#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {

/* variable declaration */
int i,h, f = 0, g = 1;

/* a familiar "for loop"*/
for(i=0;i<40;i++) {
    printf("%9d ", g);
    h = g;
    g += f;
    f = h;
    if(i%5==0 && (i!=1 ||i!=0)){
        printf("\n");
 }
 }
    return 0;
    
}


