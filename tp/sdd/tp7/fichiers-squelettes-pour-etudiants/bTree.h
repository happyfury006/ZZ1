#ifndef BT_H
#define BT_H

struct BTreeNode {
  int item[MAX + 1], count;
  struct BTreeNode *linker[MAX + 1];
};




void addValToNode(int item, int pos, struct BTreeNode *node, struct BTreeNode *child);
void splitNode(int item, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode);
int setValueInNode(int item, int *pval, struct BTreeNode *node, struct BTreeNode **child);
struct BTreeNode * bTreeCreateNode(int item, struct BTreeNode *child);
void bTreeInsert(int item);

void copySuccessor(struct BTreeNode *myNode, int pos);
void removeVal(struct BTreeNode *myNode, int pos);
void rightShift(struct BTreeNode *myNode, int pos);
void leftShift(struct BTreeNode *myNode, int pos);
void mergeNodes(struct BTreeNode *myNode, int pos);
void adjustNode(struct BTreeNode *myNode, int pos);
int delValFromNode(int item, struct BTreeNode *myNode);
void bTreeDelete (int item, struct BTreeNode *myNode);

void bTreeInorderTraversal(struct BTreeNode *myNode);

#endif
