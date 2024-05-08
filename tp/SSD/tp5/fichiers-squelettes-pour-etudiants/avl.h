#ifndef AVL_H
#define AVL_H

struct avl {
	int key;
	int height;
	struct avl * left;
	struct avl * right;
};

int max(int a, int b);
int avlHeight(struct avl * root);
struct avl * avlCreateNode(int key);
struct avl * avlRotateRight(struct avl * y);
struct avl * avlRotateLeft(struct avl * x);
int avlGetBalance(struct avl * root);
struct avl * avlInsert(struct avl * root, int key);
struct avl * avlMinValue(struct avl * root);
struct avl * avlDelete(struct avl * root, int key);
void avlDisplay(struct avl * root);
void avlFree(struct avl * root);

#endif
