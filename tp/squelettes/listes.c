#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listes.h"

list * listCreate() {
    return NULL;
}

list * listAdd(list * l,int n){
    list * plist=(list *) malloc(sizeof(list));
    if (plist==NULL) return NULL;

    plist->value=n;
    plist->next=l;
    return plist;
}



void listDisplay(list * l){
      if(l->next==NULL){
        printf("%d",l->value);
      }
      else{
        listDisplay(l->next);
        printf("%d",l->value);
      }
}


void listInverseDisplay(list * l){
      if(l->next==NULL){
        printf("%d",l->value);
      }
      else{
        printf("%d",l->value);
        listInverseDisplay(l->next);
        
      }

}

int listSearch(list * plist, int n){
      if(plist==NULL){
        return 0;
      }
      else if(plist->value==n){
            return 1;
        }
      else{  
        listSearch(plist->next,n);
      }
      
      
}



list * listMap(list* l , int (*f)(int)){
      if(l==NULL){
        return listCreate();
      }
      else{
        list * newlist = listMap(l->next,f);
        return listAdd(newlist,f(l->value));
      }
      

      //  DONE question 5
      

}

list * listFilter(list* l , int (*p)(int)){
    if(l == NULL){
      return listCreate();
    } 
    else{
        list * l2 = listFilter(l->next, p);
        if(p(l->value)){
          return listAdd(l2, l->value);
        } 
        else{
          return l2;
        } 
    }
}

int listFold(list* l , int (*op)(int,int),int base){
    if(l == NULL){
      return base;
    } 
    else{
        return op(l->value, listFold(l->next, op, base));
    }

    // DONE question 7
}


// DONE  question 7


int opSomme(int a, int b){
    return a + b;
}

int listSum(list* l ){
    return listFold(l, &opSomme, 0);
}

int opProd(int a, int b){
    return a*b;
}

int listProd(list* l ){
    return listFold(l, &opProd, 1);
}

int opLen(int a, int b){
    return b+1;
}

int listLen(list* l ){
    return listFold(l, &opLen, 0);
}


// concatene à l1 l'inverse de l2
list * ajouteInverse(list * l1,list * l2){
    if(l2 == NULL){
        return l1;
    }
    else{
        list * tete_l2 = l2 ;
        l2 = l2->next;
        tete_l2->next = l1 ;
        l1 = tete_l2;
        return ajouteInverse(l1, l2);
    }
    // DONE question 8
}

list* listInverse(list *l){
    // DONE question 8
      return ajouteInverse(NULL,l);
}



void listFree(list * plist){
    if(plist!=NULL){
      listFree(plist->next);
      free(plist);
    }
    // DONE question 9
}