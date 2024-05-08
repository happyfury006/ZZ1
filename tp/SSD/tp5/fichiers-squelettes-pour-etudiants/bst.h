#ifndef BST_H
#define BST_H

struct bst {
	int key;
	struct bst * left;
	struct bst * right;
};

struct bst * bstCreateNode(int key);
void bstInorderTraversal(struct bst * root);
struct bst * bstInsert(struct bst * root, int key);
struct bst * bstMinValue(struct bst * root);
struct bst * bstDelete(struct bst * root, int key);
void bstFree(struct bst * root);
void bstDisplay(struct bst * root);

#endif
