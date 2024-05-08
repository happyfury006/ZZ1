#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "avl.h"

void testAbr();
void testAvl();

int main(void) {
	testAbr();
	testAvl();
	return 0;
}

void testAbr() {
	struct bst * abr;
	int i;
	// test number 1
	abr = NULL;
	abr = bstInsert(abr, 10);
	printf("Ajout de 10 :\n");
	bstInorderTraversal(abr);
	abr = bstInsert(abr, 7);
	abr = bstInsert(abr, 5);
	printf("Ajout de 7 et 5 :\n");
	bstInorderTraversal(abr);
	bstDisplay(abr);
	bstFree(abr);
	// test number 2
	abr = NULL;
	printf("Ajout de 100 entiers (dans le désordre) :\n");
	for (i=0; i<100; i++) {
		abr = bstInsert(abr, (123*i+456)%100);
	}
	bstInorderTraversal(abr);
	bstFree(abr);
	// test number 3
	abr = NULL;
	printf("Ajout de 10 entiers (dans le désordre) :\n");
	for (i=0; i<10; i++) {
		abr = bstInsert(abr, (123*i+456)%100);
	}
	bstInorderTraversal(abr);
	bstDisplay(abr);
    printf("\n");
	bstFree(abr);
}

void testAvl() {
	int i;
	struct avl * avl;
	// test number 1
	avl = NULL;
	for (i=0; i<10; i++) {
		avl = avlInsert(avl, i);
	}
	printf("Ajout de 10 entiers :\n");
	avlDisplay(avl);
	avlFree(avl);
	// test number 2
	avl = NULL;
	for (i=0; i<10; i++) {
		avl = avlInsert(avl, i);
	}
	printf("Ajout de 10 entiers, et suppression de 1 et 0 :\n");
	avl = avlDelete(avl, 1);
	avl = avlDelete(avl, 0);
	avlDisplay(avl);
    printf("\n");
	avlFree(avl);
}
