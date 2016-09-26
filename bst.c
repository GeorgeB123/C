#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "mylib.h"

struct bstnode{
    char *key;
    bst left;
    bst right;
};

bst bst_delete(bst b, char *str){
    if(b == NULL){
        return b;
    }
    if(strcmp(b->key, str)>0){
        b->left = bst_delete(b->left, str);
    }
    if(strcmp(b->key, str)<0){
        b->right = bst_delete(b->right, str);
    }
    if(strcmp(b->key, str)==0){
        if(b->left==NULL && b->right==NULL){
            free(b->key);
            free(b);
            b = NULL;
            return b;
        }
        if(b->left == NULL){
            char *temp = b->key;
            b->key = b->left->key;
            b->left->key = temp;
            b = bst_delete(b, temp);
        } else if( b->right == NULL){
            char *temp = b->key;
            b->key = b->right->key;
            b->right->key = temp;
            b = bst_delete(b, temp);
        }else if(b->left!=NULL && b->right!=NULL){
            bst t = b->right;
            while(t->left !=NULL){
                t= t->left;
            }
            strcpy(b->key, t->key);
            b->right = bst_delete(b->right, t->key);
            
        }
    }
    return b;
}

bst bst_free(bst b){
    if(b == NULL){
        return b;
    }
    bst_free(b->left);
    bst_free(b->right);
    free(b->key);
    free(b);
    return b;
}

void print_key(char *s) {
    printf("%s\n", s);
}

void bst_inorder(bst b, void f(char *str)){
    if(b==NULL){
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);       
}

bst bst_insert(bst b, char *str){
    if(b == NULL){
        b = emalloc(sizeof *b);
        b->key = NULL;
        b->left = NULL;
        b->right =NULL;
    }
    if(b->key == NULL){
        b->key = emalloc((strlen(str)+1)*sizeof(char));
        strcpy(b->key, str);
    }
    if(strcmp(b->key,str)==0){
        return b;
    }
    if(strcmp(b->key,str)>0){
        b->left = bst_insert(b->left, str);
    }
    if(strcmp(b->key,str)<0){
        b->right = bst_insert(b->right, str);
    }
    return b;
}

bst bst_new(){
    return NULL;   
}

void bst_preorder(bst b, void f(char *str)){
    if(b==NULL){
        return;
    }
    f(b->key);
    bst_inorder(b->left, f);
    bst_inorder(b->right, f); 
}

int bst_search(bst b, char *str){
    if(b == NULL){
        return 0;
    }
    if(strcmp(b->key,str)==0){
        return 1;
    }
    if(strcmp(b->key, str)>0){
        return bst_search(b->left, str);
    }else if(strcmp(b->key, str)<0){
        return bst_search(b->right, str);
    }
    return 1;
}
