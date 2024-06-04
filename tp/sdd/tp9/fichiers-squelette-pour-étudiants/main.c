#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <unistd.h>
#include <time.h>

list* liste_test();
list* liste_decroissante(int n);
void test_listPivot();
void test_quicksort();
void test_randomPivot();

int main(int argc, char ** argv) {
    srand(time(NULL));

	test_listPivot(); // DECOMMENTER APRES AVOIR TERMINE 1.1
	test_quicksort(); // DECOMMENTER APRES AVOIR TERMINE 1.2
	test_randomPivot(); // DECOMMENTER APRES AVOIR TERMINE 2
}

list* liste_test(){
    list* l = listCreate();
    l = listAdd(l,2);
    l = listAdd(l,4);
    l = listAdd(l,8);
    l = listAdd(l,5);
    l = listAdd(l,3);
    l = listAdd(l,5);
    l = listAdd(l,7);
    return l; // liste [7,5,3,5,8,4,2]
}

list* liste_decroissante(int n){
    list* l = listCreate();
    for (int i = 1; i <= n; i++){
        l = listAdd(l,i);
    }
    return l; // liste [5,4,3,2,1] pour n = 5
}

void test_listPivot(){
    printf("--- Test de la fonction listPivot ---\n");
    list* l = liste_test();
    printf("Liste de depart ");
    listDisplay(l);
    int pivot = 5;
    printf("Pivot : %d\n", pivot);
    list** duo = listPivot(l,pivot);
    printf("A gauche du pivot (doit contenir 2,4,5,3) : ");
    listDisplay(duo[0]);
    printf("A droite du pivot (doit contenir 8,7) : ");
    listDisplay(duo[1]);
    listFree(duo[0]);
    listFree(duo[1]);
    free(duo);

    printf("Test avec liste vide (doit faire apparaitre deux listes vides ci-dessous) \n");
    l = listCreate();
    duo = listPivot(l,pivot);
    listDisplay(duo[0]);
    listDisplay(duo[1]);
    free(duo);

    printf("--- Fin du test ---\n\n\n");
}

void test_quicksort(){
    printf("--- Test de la fonction quickSort ---\n");
    list* l = liste_test();
    printf("Liste de depart : ");
    listDisplay(l);
    printf("Liste triee : ");
    list* l_copy = quickSort(l);
    listDisplay(l_copy);
    printf("Liste de depart, doit rester inchangee (non triee) : ");
    listDisplay(l);
    listFree(l);
    listFree(l_copy);

    printf("Test avec liste vide ");
    l = listCreate();
    l_copy = quickSort(l);
    listDisplay(l_copy);
    free(l_copy);
    free(l);

    printf("Test liste avec un seul element ");
    l = listAdd(l,3);
    l_copy = quickSort(l);
    listDisplay(l_copy);
    listFree(l);
    listFree(l_copy);
    printf("--- Fin du test ---\n\n\n");
}

void test_randomPivot(){
    printf("--- Comparaison des selections de pivot sur une liste decroissante à 3000 valeurs ---\n\n");
    list* l = liste_decroissante(3000);

    if (l){
        printf("- Liste triee, pivot premier element, temps d'execution : ");

        clock_t begin = clock();
        list* l_copy = quickSort(l);
        clock_t end = clock();
        double time_spent = ((double)(end - begin))*1000/CLOCKS_PER_SEC;
        printf("%f ms\n", time_spent);
        listFree(l_copy);
        printf("\n");

        printf("- Liste triee, pivot aleatoire, temps d'execution : ");
        clock_t begin_2 = clock();
        l_copy = quickSort_alea(l);
        clock_t end_2 = clock();
        time_spent = ((double)(end_2 - begin_2))*1000/CLOCKS_PER_SEC;
        printf("%f ms\n", time_spent);

        printf("10 premiers elements de la liste triee avec pivot aleatoire: ");
        list* temp = listCreate();
        list* temp_copy = l_copy;
        for (int i = 0; i < 10; i++){
            temp = listAdd(temp,temp_copy->value);
            temp_copy = temp_copy->next;
        }
        list* tempInv = listInverse(temp);
        listFree(temp);

        listDisplay(tempInv);
        listFree(tempInv);
        listFree(l);
        listFree(l_copy);
        printf("--- Fin du test ---\n");
    }
}


