#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"



// Partie donnée aux étudiants
list * listCreate() {
	return NULL;
}

list * listAdd(list * l, int v) {
	list * new = (list *)malloc(1*sizeof(list));
	if (new==NULL) {
		return NULL;
	}
	new->value = v;
	new->next = l;
	return new;
}

int listSize(list * l) {
	int n = 0;
	while (l!=NULL) {
		n = n+1;
		l = l->next;
	}
	return n;
}

void listDisplay(list * l) {
	printf("(");
	while (l) {
		printf("%d", l->value);
		if (l->next) {
			printf(", ");
		}
		l = l->next;
	}
	printf(")\n");
}

list * listRemove(list * l) {
	list * head;
	if (l==NULL) {
		return NULL;
	}
	else {
		head = l->next;
		free(l);
		return head;
	}
}

void listFree(list * l) {
	while (l) {
		l = listRemove(l);
	}
}

list* listInverse(list* l){
    list* l_copy = listCreate();
    while (l){
        l_copy = listAdd(l_copy,l->value);
        l = l->next;
    }
    return l_copy;
}

list* listCopy(list* l){
    list* temp = listInverse(l);
    list* result = listInverse(temp);
    listFree(temp);
    return result;
}

// Exo 1 : quicksort sans mémoire extra

list** listPivot(list* l, int pivot) {
    list* gauche = NULL;
    list* droite = NULL;
    list* gauchefin = NULL;
    list* droitefin = NULL;

    
    list* cour = l;
    int nbr=0;
    while (cour != NULL) {
        list* next = cour->next;
        if (cour->value < pivot) {
            if (gauche == NULL) {
                gauche = cour;
                gauchefin = cour;
            } else {
                gauchefin->next = cour;
                gauchefin = cour;
            }
        } else if (cour->value > pivot) {
            if (droite == NULL) {
                droite = cour;
                droitefin = cour;
            } else {
                droitefin->next = cour;
                droitefin = cour;
            }
        } 
        else{
            // Cas de la première apparition du pivot
            if (cour->value == pivot && nbr==0){
                nbr=1;
            }
             else{
                //réaparition du pivot : on l'ajoute a gauche
                if (gauchefin == NULL) {
                    gauche = cour;
                    gauchefin = cour;
                } else {
                    gauchefin->next = cour;
                    gauchefin = cour;
                }
            }
            
            } 
            
        
        cour = next;
    }

    if (gauchefin != NULL) gauchefin->next = NULL;
    if (droitefin != NULL) droitefin->next = NULL;

    list** duo = (list**)malloc(2 * sizeof(list*));
    if (duo) {
        duo[0] = gauche;
        duo[1] = droite;
    } else {
        return NULL;
    }
    return duo;
}


list* reassemble(list* gauche, list* droite, int pivot){
    list * assemble=listAdd(droite,pivot);
    list * p=gauche;
    if (p == NULL) {
        return assemble;
    }
    while (p->next != NULL){
        p=p->next;
    }
    p->next=assemble;
    
    return gauche;
}

list* quickSort_rec(list* l){
    if (l==NULL || l->next==NULL)
    {
        return l;
    }
    else{
        list ** duo =listPivot(l,l->value);
        list * trié=reassemble(quickSort_rec(duo[0]),quickSort_rec(duo[1]),l->value);
        free(duo);
        return trié;
    }
    return NULL;
}

list* quickSort(list* l){
    list* l_copy = listCopy(l);
    l_copy = quickSort_rec(l_copy);
    return l_copy;
}

// Exo 2 : choix du pivot aleatoire
int getRandomElement(list* l){
    int randompiv= rand()% listSize(l);
    list* listCopy=l;
    for(int i=0;i<randompiv;i++){
        listCopy=listCopy->next;
    }
    return listCopy->value;
}

int getRandomPivot(list* l){
    int random1=getRandomElement(l);
    int random2=getRandomElement(l);
    int random3= getRandomElement(l);
    list * listerand=listCreate(random1);
    listerand=listAdd(listerand,random2);
    listerand=listAdd(listerand,random3);
    list* listrie=quickSort(listerand);
    // A COMPLETER
    return listrie->next->value;
}

list* quickSort_rec_alea(list* l){
    int randpivot = getRandomPivot(l);
    if (l==NULL || l->next==NULL)
    {
        return l;
    }
    else{
        list ** duo =listPivot(l,randpivot);
        list * trié=reassemble(quickSort_rec(duo[0]),quickSort_rec(duo[1]),l->value);
        free(duo);
        return trié;
    }
    return NULL;
}

list* quickSort_alea(list* l){
    list* l_copyalea = listCopy(l);
    l_copyalea = quickSort_rec_alea(l_copyalea);
    return l_copyalea;
}
