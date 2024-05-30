#ifndef LIST_H
#define LIST_H

typedef struct list {
	int value;
	struct list * next;
} list;

list * listCreate();
list * listAdd(list * l, int v);
int listSize(list * l);
void listDisplay(list * l);
list * listRemove(list * l);
void listFree(list * l);
list* listInverse(list* l);
list* listCopy(list* l);
list** listPivot(list* l, int pivot);
list* reassemble(list* gauche, list* droite, int pivot);
list* quickSort_rec(list* l);
list* quickSort(list* l);
int getRandomElement(list* l);
int getRandomPivot(list* l);
list* quickSort_rec_alea(list* l);
list* quickSort_alea(list* l);

#endif
