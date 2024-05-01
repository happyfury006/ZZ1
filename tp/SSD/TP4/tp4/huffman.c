#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "huffman.h"

arbrepoids cree_arbrepoids(arbre a, int poids) {
  arbrepoids ap =  malloc(sizeof(struct arbrepoids));
  if (ap != NULL) {
    ap->element = a;
    ap->poids = poids;
  }
  return ap;
}

liste cree_liste(arbre a, int poids, liste suivant) {
  liste res = malloc(sizeof(struct liste));

  if (res != NULL) {
    arbrepoids ap = cree_arbrepoids(a, poids);
    if (ap != NULL) {
      res->data = ap;
    }
    res->suivant = suivant;
  }

  return res;
}

liste genere_liste(char* s) {
  return NULL;
}

arbrepoids extrait_min(liste *l) {
  return NULL;
}

arbre huffman(char* s) {
  return NULL;
}
