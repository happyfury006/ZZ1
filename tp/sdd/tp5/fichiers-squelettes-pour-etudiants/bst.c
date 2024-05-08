#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst * bstCreateNode(int key) {
    struct bst * init=(struct bst *)malloc(sizeof(struct bst));
    init->key= key;
    init->left=NULL;
    init->right=NULL;
    return init;
    // TODO : question 1
}

void bstInorderTraversal(struct bst * root) {
    if (root->left!=NULL)
    {
        bstInorderTraversal(root->left);
    }
    printf("%d",root->key);
    if (root->right!=NULL)
    {
       bstInorderTraversal(root->right);
    }
    printf("%d",root->key);
}

struct bst * bstInsert(struct bst * root, int key) {
    struct bst * new;
    if (root->key > key)
    {
        if (root->left == NULL)
        {
            new =bstCreateNode(key);
            root->left= new;
        }
        else
            bstInsert(root->left,key);
    }
    else
        if (root->right == NULL)
        {
            new =bstCreateNode(key);
            root->right= new;
        }
        else
            bstInsert(root->right,key);
    return root;
    // TODO : question 3
}


struct bst * bstMinValue(struct bst * root) {
    if (root->left==NULL){
        return root;
    }
    else {
        bstMinValue(root->left);
    }
    
    
    // TODO : question 4
}

struct bst * bstDelete(struct bst * root, int key) {
    //elimination de du noeud
    if (root->key=key){
        if ((root->left==NULL) && (root->right==NULL) ){
            root->key=NULL;
            free(root->left);
            free(root->right);
        }
        if ((root->left!=NULL) && (root->right!=NULL) ){
            struct bst * min;
            min=bstMinValue(root->right);
            root->key=min->key;
            min->key=NULL;
            free(min->left);
            free(min->right);
        }
        else if ((root->left!=NULL) && (root->right==NULL)){
            root->key=root->left;
            root->left=NULL;
        }
        else if ((root->left==NULL) && (root->right!=NULL)){
            root->key=root->right;
            root->right=NULL;
        }
    }
    // parcour de la bonne valeur
    else{
        if (root->key>key){
            bstDelete(root->left,key);
        }
        else{
            bstDelete(root->right,key);
        }   
    }
    // TODO : question 5
}

void bstFree(struct bst * root) {
    if (root->left==NULL)
    {
        free(root->left);
    }
    if (root->right==NULL)
    {
        free(root->right);
    }
    if (root->left!=NULL)
    {
        bstFree(root->left);
    }
    if (root->right!=NULL)
    {
        bstFree(root->right);
    }
    // TODO : question 6
}

void bstDisplay(struct bst * root) {
    printf("[");
    if (root->left==NULL)
    {
       printf(" []");
    }
    else
    {
        
    }
    
    if (root->right==NULL)
    {
        printf(" []")
    }
    
    
    {
        printf("%d",cour->key)
        
    }
    

    // TODO : question 7
}

