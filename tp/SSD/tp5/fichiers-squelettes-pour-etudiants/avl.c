#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int max(int a, int b) {
	if (a>b) {
		return a;
	}
	else {
		return b;
	}
}

struct avl * avlCreateNode(int key) {
    // TODO : question 8
}

int avlHeight(struct avl * root) {
    // TODO : question 9
}

int avlGetBalance(struct avl * root) {
    // TODO : question 10
}

struct avl * avlRotateRight(struct avl * y) {
    // TODO : question 11
}

struct avl * avlRotateLeft(struct avl * x) {
    // TODO : question 12
}

struct avl * avlInsert(struct avl * root, int key) {
    // TODO : question 13
}

struct avl * avlMinValue(struct avl * root) {
    // TODO : question 14
}

struct avl * avlDelete(struct avl * root, int key) {
    // TODO : question 15
}

void avlFree(struct avl * root) {
    // TODO : question 16
}

void avlDisplay(struct avl * root) {
    // TODO : question 17
}


