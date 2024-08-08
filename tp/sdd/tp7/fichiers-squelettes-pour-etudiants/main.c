
#include <stdio.h>
#include <stdlib.h>
#include "bTree.h"

extern struct BTreeNode *root;

int main() {
    bTreeInsert(8);
    bTreeInsert(9);
    bTreeInsert(10);
    bTreeInsert(11);
    bTreeInsert(15);
    bTreeInsert(16);
    bTreeInsert(17);
    bTreeInsert(18);
    bTreeInsert(20);
    bTreeInsert(23);

  bTreeInorderTraversal(root);

  bTreeDelete (20, root);
  printf("\n");
  bTreeInorderTraversal(root);
}
