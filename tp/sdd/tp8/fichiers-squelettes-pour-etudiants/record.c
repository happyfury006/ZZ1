#include <stdlib.h>
#include <stdio.h>
#include "record.h"

list * listCreate() {
    list * nouv=(list *)malloc(sizeof(list));
    nouv->length=0;
    nouv->head=NULL;
    nouv->tail=NULL;
    return nouv;
}

int listSize(list * l) {
    return l->length;
    // TODO : question 2
}

void addRecord(list * l, int variant, int limit) {
    record * newR=(record *)malloc(sizeof(record));
    newR->variant=variant;
    newR->limit=limit;
    newR->next=NULL;
    if (l->length==0)
    {
        l->head=newR;
        l->tail=newR;
    }
    else{
        l->tail->next=newR;
        
    }
        
    l->length=l->length+1;
    // TODO : question 3
}

void listDisplay(list * l) {
    record * parcours=l->head;
    while (parcours !=NULL)
    {
        printf("le varient :%d et la limite :%d\n",parcours->variant,parcours->limit);
        parcours=parcours->next;
    }
    // TODO : question 4
}

void listFree(list * l){
    record * libere=l->head;
    while (l->head!=l->tail){
        libere=l->head->next;
        free(l->head);
        l->head=libere;
    }
    
    // TODO : question 5
}


void listDestroy(list * l) {
    listFree(l);
    free(l);
    // TODO : question 6
}


int veriTer(list * l){
    int tendance=1;
    record * parcours=l->head;
    
    if (parcours!=NULL)
    {
        int diff =abs(parcours->variant - parcours->limit);
        while (parcours->next!=NULL && tendance ==1){
        parcours=l->head->next;
        int newdiff=abs(parcours->variant - parcours->limit);
        if (newdiff>diff)
        {
            tendance=0;
        }
        else
            diff=newdiff;
        listDisplay(l);
    }
    }
    return tendance;
    // TODO : question 7
}


