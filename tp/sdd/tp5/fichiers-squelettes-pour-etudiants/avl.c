#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

struct avl * avlCreateNode(int key) {
    struct avl * init = (struct avl *)malloc(sizeof(struct avl));
    if (init == NULL) {
        printf("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    init->key = key;
    init->height = 1;
    init->left = NULL;
    init->right = NULL;
    return init;
}

int avlHeight(struct avl * root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return root->height;
    }
}

int avlGetBalance(struct avl * root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return avlHeight(root->left) - avlHeight(root->right);
    }
}

struct avl * avlRotateRight(struct avl * y) {
    if (y == NULL || y->left == NULL) {
        return y;
    }
    struct avl * x = y->left;
    struct avl * tmp = x->right;
    x->right = y;
    y->left = tmp;

    y->height = max(avlHeight(y->left), avlHeight(y->right)) + 1;
    x->height = max(avlHeight(x->left), avlHeight(x->right)) + 1;

    return x;
}

struct avl * avlRotateLeft(struct avl * x) {
    if (x == NULL || x->right == NULL) {
        return x;
    }
    struct avl * y = x->right;
    struct avl * tmp = y->left;
    y->left = x;
    x->right = tmp;

    x->height = max(avlHeight(x->left), avlHeight(x->right)) + 1;
    y->height = max(avlHeight(y->left), avlHeight(y->right)) + 1;

    return y;
}

struct avl * avlInsert(struct avl * root, int key) {
    if (root == NULL) {
        return avlCreateNode(key);
    }
    if (key < root->key) {
        root->left = avlInsert(root->left, key);
    }
    else if (key > root->key) {
        root->right = avlInsert(root->right, key);
    }
    else {
        return root;
    }
    root->height = 1 + max(avlHeight(root->left), avlHeight(root->right));

    int balance = avlGetBalance(root);

    if (balance > 1 && key < root->left->key) {
        return avlRotateRight(root);
    }
    if (balance < -1 && key > root->right->key) {
        return avlRotateLeft(root);
    }
    if (balance > 1 && key > root->left->key) {
        root->left = avlRotateLeft(root->left);
        return avlRotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = avlRotateRight(root->right);
        return avlRotateLeft(root);
    }
    return root;
}

struct avl * avlMinValue(struct avl * root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL) {
        return root;
    }
    else {
        return avlMinValue(root->left);
    }
}

struct avl * avlDelete(struct avl * root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = avlDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = avlDelete(root->right, key);
    }
    else {
        if (root->left == NULL) {
            struct avl *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct avl *temp = root->left;
            free(root);
            return temp;
        }

        struct avl* temp = avlMinValue(root->right);

        root->key = temp->key;

        root->right = avlDelete(root->right, temp->key);
    }
    return root;
}

void avlFree(struct avl * root) {
    if (root != NULL) {
        avlFree(root->left);
        avlFree(root->right);
        free(root);
    }
}

void avlDisplay(struct avl * root) {
    if (root == NULL) {
        printf("[]");
        return;
    }

    printf("[%d ", root->key);
    avlDisplay(root->left);
    printf(" ");
    avlDisplay(root->right);
    printf("]");
}
