#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"

arbre feuille(char c){
  return noeud(c,NULL,NULL);
}

arbre noeud(char c, arbre g, arbre d){
  arbre  a=(arbre)malloc(sizeof(arbre));
  a->data=c;
  a->gauche=g;
  a->droite=d;
  return a;
}

int est_feuille(arbre a) {
  return (a->gauche==NULL && a->droite==NULL);
}

void libere_arbre(arbre *a){
  if( *a!=NULL){
    libere_arbre(&(*a)->gauche);
    libere_arbre(&(*a)->droite);
    free(*a);
    *a=NULL;
  }
}

void infixe_inverse(FILE *f, arbre a) {
  if(a!=NULL){
    infixe_inverse(f,a->droite);
    fprintf(f,"%c\n",a->data);
    infixe_inverse(f,a->gauche);
  }
}

void imprime_blancs(FILE *f, int niveau, int est_droit) {
  int i;
  if(niveau!=0){
    for(i=0;i<niveau;i++){
    fprintf(f,"   ");
  }
  if(est_droit){
    fprintf(f,"/-");
  }
  else{
    fprintf(f,"\\-");
  }
  }
}

void imprime_avec_blancs(FILE *f, arbre a, int niveau, int est_droit) {
  if(a!=NULL){
    imprime_avec_blancs(f,a->droite,niveau+1,1);
    imprime_blancs(f,niveau,est_droit);
    fprintf(f,"%c\n",a->data);
    imprime_avec_blancs(f,a->gauche,niveau+1,0);
  }

}

void imprime_arbre(FILE *f, arbre a){
  imprime_avec_blancs(f,a,0,1);
}


