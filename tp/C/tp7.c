#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tp7.h"

void insere_start(liste_t *liste,char *element){
    int sizecel = sizeof(cellule_t);
    cellule_t *cellule_inser =(cellule_t*)malloc(sizecel);
    strcpy(cellule_inser->ligne,element);
    if (liste->fin==NULL)
        liste->fin=cellule_inser;
    cellule_inser->suivant=liste->tete;
    liste->tete= &cellule_inser;

}

void insere_end(liste_t *liste,char *element){
    int sizecel = sizeof(cellule_t);
    cellule_t *cellule_inser= (cellule_t*)malloc(sizecel);
    strcpy(cellule_inser->ligne,element);
    if (liste->tete==NULL)
        liste->tete=cellule_inser;
    cellule_inser->suivant=NULL;
    liste->fin->suivant=cellule_inser->suivant;
    liste->fin= cellule_inser;

}
void afficher_Liste(liste_t *liste){
    cellule_t *courant=liste->tete;
    while(courant != NULL){
        printf("%s",courant->ligne);
        courant= courant->suivant;
    }
}



int main(int argv, char * argv[]){

    liste_t *liste=(liste_t*)malloc(sizeof(liste_t));
    liste->tete=NULL;
    liste->fin=NULL;
    insere_start(liste,argv);
    afficher_Liste(liste);
    return 0;
};
