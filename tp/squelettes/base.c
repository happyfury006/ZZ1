#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base.h"

static int base=2;


//  IMPORTANT :  les nombres en binaires sont par exemple modélisés de la façon suivante :
//  Le nombre binaire 1101101
//  NULL <- 1 <- 1 <- 0 <- 1 <- 1 <- 0 <- 1 
//  C'est à dire que la tête de la liste est le bit de poids faible et la queue le bit de poids fort.

// 
void setBase(int b)
{
    base=b;
}

void printBaseB(list * l){
    if(l != NULL){
        char symboles[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k'};
        printBaseB(l->next);
        printf("%c", symboles[l->value]);
    }

    // DONE : A compléter question 10
}

int baseToDec(list* l){
    if(l == NULL){
        return 0;
    }else{
        return (l->value + base*baseToDec(l->next));
    }
    // DONE : A compléter question 11
}



int baseToDec2(list* l){
    
    // DONE : A compléter question 11 (si vous voulez faire avec les deux méthodes)

 
    return 0;
}


list* decToBase(int n ){
    // DONE : A compléter question 11 (si vous voulez faire avec les deux méthodes)
    if(n == 0){
        return NULL;
    }else{
        list * l = decToBase(n / base);
        return listAdd(l, n%base);
    }

}
