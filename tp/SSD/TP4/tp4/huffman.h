#include "arbre.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct arbrepoids{
  arbre element;
  int poids;
} *arbrepoids;

typedef struct liste { 
  arbrepoids data;
  struct liste *suivant;
} *liste;


arbrepoids cree_arbrepoids(arbre a, int poids);

liste cree_liste(arbre a, int poids, liste suivant);

liste genere_liste(char* s);

arbrepoids extrait_min(liste *l);

arbre huffman(char* s);

#endif
