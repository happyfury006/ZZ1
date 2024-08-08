#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst * bstCreateNode(int key) {
    struct bst * init = (struct bst *)malloc(sizeof(struct bst));
    init->key = key;
    init->left = NULL;
    init->right = NULL;
    return init;
}

void bstInorderTraversal(struct bst * root) {
    if (root != NULL) {
        bstInorderTraversal(root->left);
        printf("%d\n", root->key);
        bstInorderTraversal(root->right);
    }
}

struct bst * bstInsert(struct bst * root, int key) {
    if (root == NULL) {
        return bstCreateNode(key);
    }

    if (key < root->key) {
        root->left = bstInsert(root->left, key);
    }
    else if (key > root->key) {
        root->right = bstInsert(root->right, key);
    }
    return root;
}

struct bst * bstMinValue(struct bst * root) {
    if (root->left == NULL){
        return root;
    }
    else {
        return bstMinValue(root->left);
    }
}

struct bst * bstDelete(struct bst * root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = bstDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = bstDelete(root->right, key);
    }
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct bst *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct bst *temp = root->left;
            free(root);
            return temp;
        }

        struct bst* temp = bstMinValue(root->right);

        root->key = temp->key;

        root->right = bstDelete(root->right, temp->key);
    }
    return root;
}

void bstFree(struct bst * root) {
    if (root != NULL) {
        bstFree(root->left);
        bstFree(root->right);
        free(root);
    }
}

void bstDisplay(struct bst * root) {
    if (root == NULL) {
        printf("[]");
        return;
    }

    printf("[%d ", root->key);
    bstDisplay(root->left);
    printf(" ");
    bstDisplay(root->right);
    printf("]");
}
