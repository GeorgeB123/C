#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void insertion_sort(char *a[], int n){
    /*variable declaration*/
    int i, j;
    char *key;
    /*for and while loops to run through each i and move it appropriately*/
    for(i=1; i<n;i++){
        key = a[i];
        j=i-1;
        while(strcmp(key,a[j])<0 && j>=0){
            a[j+1]=a[j];
            --j;
        }
        a[j+1]=key;
    }/*exiting the for and while loop*/
}

int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int i, num_words = 0;

    while(num_words<ARRAY_LEN && 1 == scanf("%79s",word)){
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    insertion_sort(wordlist, num_words);
    for(i=0; i<num_words; i++){
        printf("%s\n", wordlist[i]);
    }
    return EXIT_SUCCESS;

}

