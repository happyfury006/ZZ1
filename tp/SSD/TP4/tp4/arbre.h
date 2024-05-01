#ifndef ARBRE_H
#define ARBRE_H

typedef struct chararbre {
  char data;
  struct chararbre *gauche;
  struct chararbre *droite;
} *arbre;

arbre feuille(char c);

arbre noeud(char c, arbre g, arbre d);

int est_feuille(arbre a);

void libere_arbre(arbre *a);

void infixe_inverse(FILE* f, arbre a);

void imprime_blancs(FILE *f, int niveau, int est_droit);

void imprime_avec_blancs(FILE *f, arbre a, int niveau, int est_droit);

void imprime_arbre(FILE *f, arbre a);

#endif
