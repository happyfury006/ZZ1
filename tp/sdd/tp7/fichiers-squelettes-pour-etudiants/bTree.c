
#include <stdio.h>
#include <stdlib.h>
#include "bTree.h"

#define MAX 3
#define MIN 2


struct BTreeNode *root;

// Add value to the node
void addValToNode(int item, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    // TODO : question 1
}

// Split the node
void splitNode(int item, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode) {
    // TODO : question 2
}

// Node creation
struct BTreeNode *bTreeCreateNode(int item, struct BTreeNode *child) {
    // TODO : question 3
}

// Set the value in the node
int setValueInNode(int item, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  if (!node) {
    *pval = item;
    *child = NULL;
    return 1;
  }

  if (item < node->item[1]) {
    pos = 0;
  } else {
    for (pos = node->count;
       (item < node->item[pos] && pos > 1); pos--)
      ;
    if (item == node->item[pos]) {
      printf("Duplicates not allowed\n");
      return 0;
    }
  }
  if (setValueInNode(item, pval, node->linker[pos], child)) {
    if (node->count < MAX) {
      addValToNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insertion operation
void bTreeInsert(int item) {
    // TODO : question 4 : flag = setValueInNode(item, &i, root, &child);
}



// Remove the value
void removeVal(struct BTreeNode *myNode, int pos) {
    // TODO : question 5
}

// Do right shift
void rightShift(struct BTreeNode *myNode, int pos) {
    // TODO : question 6
}

// Do left shift
void leftShift(struct BTreeNode *myNode, int pos) {
    // TODO : question 7
}

// Merge the nodes
void mergeNodes(struct BTreeNode *myNode, int pos) {
    // TODO : question 8
}

// Adjust the node
void adjustNode(struct BTreeNode *myNode, int pos) {
    // TODO : question 9
}

// Copy the successor
void copySuccessor(struct BTreeNode *myNode, int pos) {
  struct BTreeNode *dummy;
  dummy = myNode->linker[pos];

  for (; dummy->linker[0] != NULL;)
    dummy = dummy->linker[0];
  myNode->item[pos] = dummy->item[1];
}

// Delete a value from the node
int delValFromNode(int item, struct BTreeNode *myNode) {
  int pos, flag = 0;
  if (myNode) {
    if (item < myNode->item[1]) {
      pos = 0;
      flag = 0;
    } else {
      for (pos = myNode->count; (item < myNode->item[pos] && pos > 1); pos--)
        ;
      if (item == myNode->item[pos]) {
        flag = 1;
      } else {
        flag = 0;
      }
    }
    if (flag) {
      if (myNode->linker[pos - 1]) {
        copySuccessor(myNode, pos);
        flag = delValFromNode(myNode->item[pos], myNode->linker[pos]);
        if (flag == 0) {
          printf("Given data is not present in B-Tree\n");
        }
      } else {
        removeVal(myNode, pos);
      }
    } else {
      flag = delValFromNode(item, myNode->linker[pos]);
    }
    if (myNode->linker[pos]) {
      if (myNode->linker[pos]->count < MIN)
        adjustNode(myNode, pos);
    }
  }
  return flag;
}

// Delete operaiton
void bTreeDelete (int item, struct BTreeNode *myNode) {
    // TODO : question 10
}

void searching(int item, int *pos, struct BTreeNode *myNode) {
  if (!myNode) {
    return;
  }

  if (item < myNode->item[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count;
       (item < myNode->item[*pos] && *pos > 1); (*pos)--)
      ;
    if (item == myNode->item[*pos]) {
      printf("%d present in B-tree", item);
      return;
    }
  }
  searching(item, pos, myNode->linker[*pos]);
  return;
}

void bTreeInorderTraversal(struct BTreeNode *myNode) {
    // TODO : question 11
}
