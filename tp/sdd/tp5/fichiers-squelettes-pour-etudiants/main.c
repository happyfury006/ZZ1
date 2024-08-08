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
	//test number 4 (demandé)
	printf("Création d'un ABR vide :\n");
	abr=NULL;
	bstDisplay(abr);
	printf("\n");
	bstFree(abr);
	//test number 5(demandé)
	printf("ajout de : 6 7 5 8 4 9 1 3\n");
	abr=NULL;
	abr = bstInsert(abr, 6);
	abr = bstInsert(abr, 7);
	abr = bstInsert(abr, 5);
	abr = bstInsert(abr, 8);
	abr = bstInsert(abr, 4);
	abr = bstInsert(abr, 9);	
	abr = bstInsert(abr, 1);
	abr = bstInsert(abr, 3);
	printf("Affichage Fonction DIsplay :\n");
	bstDisplay(abr);
	printf("\n");
	printf("Affichage Fonction inorderTrasversal:\n");
	bstInorderTraversal(abr);		
	printf("Supression de 7 :\n");
	bstDelete(abr,7);
	bstDisplay(abr);
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
		// test number 3(demandé)
	avl = NULL;
	printf("Affichage d'un AVL vide :\n");
	avlDisplay(avl);
	printf("\n");
		// test number 2
	avl = NULL;
	avl= avlInsert(avl,6);
	avl= avlInsert(avl,7);
	avl= avlInsert(avl,5);
	avl= avlInsert(avl,8);
	printf("Affichage d'un AVL avec 6 7 5 8 :\n");
	avlDisplay(avl);
	printf("\n");
	avl= avlInsert(avl,4);
	avl= avlInsert(avl,9);
	avl= avlInsert(avl,1);
	avl= avlInsert(avl,3);
	printf("Affichage d'AVL avec les valeurs ajoutés 4 9 1 3 :\n");
	avlDisplay(avl);
	printf("\n");
	avlFree(avl);
		// test number 2
	avl = NULL;
	avl= avlInsert(avl,6);
	avl= avlInsert(avl,7);
	avl= avlInsert(avl,5);
	avl= avlInsert(avl,8);
	avl= avlInsert(avl,4);
	avl= avlInsert(avl,9);
	avl= avlInsert(avl,1);
	avl= avlInsert(avl,3);	
	printf("Affichage d'un AVL ajouté des valeurs 6 7 5 8 4 9 1 3 :\n");
	avlDisplay(avl);
	printf("\n");
	avl = avlDelete(avl, 7);
	printf("Suppression de 7 :\n");
	avlDisplay(avl);
 printf("\n");
}
