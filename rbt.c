#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))



struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};



rbt rbt_delete(rbt b, char *str){
    if (NULL == b){
        return b;
    }
    if(strcmp(b->key,str) < 0){
        b->right = rbt_delete(b->right, str);
    }else if(strcmp(b->key,str) > 0){
        b->left = rbt_delete(b->left,str);
    }
    if(strcmp(b->key,str) == 0){
        if(b->right == NULL && b->left == NULL){
            free(b->key);
            b = NULL;
            return b;
        } else if(b->right != NULL){
            char *temp = b->key;
            b->key = b->right->key;
            b->right->key = temp;
            b = rbt_delete(b, temp);
        } else if(b->left != NULL){
            char *temp = b->key;
            b->key = b->left->key;
            b->left->key = temp;
            b = rbt_delete(b, temp);
        } else if(b->left != NULL && b->right != NULL){
            rbt temp = b->right;
            while(temp->left != NULL){
                temp = temp->left;
            }
            strcpy(b->key, temp->key);
            b->right=rbt_delete(b->right, temp->key);
        }
    }
    return b;
}

rbt rbt_free(rbt b){
    if(b == NULL){
        return b;
    }
    rbt_free(b->left);
    rbt_free(b->right);
    free(b->key);
    free(b);
    return b;
}

static rbt right_rotate(rbt r){
    rbt temp;
    temp = r;
    r = temp->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

static rbt left_rotate(rbt r){
    rbt temp;
    temp = r;
    r = temp->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

static rbt rbt_fix(rbt r){
    if(IS_RED(r->left) && IS_RED(r->left->left)){
        if(IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if(IS_RED(r->left) && IS_RED(r->left->right)){
        if(IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->left = left_rotate(r->left);
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if(IS_RED(r->right) && IS_RED(r->right->left)){
        if(IS_RED(r->left)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->right = right_rotate(r->right);
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    else if(IS_RED(r->right) && IS_RED(r->right->right)){
        if(IS_RED(r->left)){
            r->colour = RED;
            r->right->colour = BLACK;
            r->left->colour = BLACK;
        } else {
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    return r;
}



rbt rbt_insert(rbt b, char *str){
    if(b == NULL){
        b = emalloc(sizeof * b);
        b->key = NULL;
        b->left = NULL;
        b->right = NULL;
        b->colour = RED;
    }

    if(b->key == NULL){
        b->key = emalloc((strlen(str)+1) * sizeof(char));
        strcpy(b->key, str);
    }

    if(strcmp(b->key, str) == 0){
        return b;
    }

    if(strcmp(b->key, str) < 0){
        b->right = rbt_insert(b->right, str);
    }
    if(strcmp(b->key, str) > 0){
        b->left = rbt_insert(b->left, str);
    }
    b = rbt_fix(b);
    return b;
}

rbt rbt_new(){
    return NULL;
}

void rbt_preorder(rbt b, void f(char *str, char *c)){
    if(b == NULL){
        return;
    }
    f(b->key, IS_BLACK(b)? "black":"red");
    rbt_preorder(b->left, f);
    rbt_preorder(b->right, f);
}

void rbt_inorder(rbt b, void f(char *str, char *c)){
    if(b == NULL){
        return;
    }
    rbt_inorder(b->left, f);
    f(b->key, IS_BLACK(b)? "black":"red");
    rbt_inorder(b->right, f);
}

        

int rbt_search(rbt b, char *str){

    if(b->key == NULL){
        return 1;
    }
    if(strcmp(b->key, str) == 0){
        return 1;
    }
    if(strcmp(b->key, str) > 0){
        return rbt_search(b->left, str);
    }
    if(strcmp(b->key, str) < 0){
        return rbt_search(b->right, str);
    }
    return 1;

}
