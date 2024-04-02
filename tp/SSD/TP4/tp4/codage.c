#include <stdlib.h>
#include <stdio.h>
#include "codage.h"

encodage cree_encodage(binaire data, encodage suivant) {
  encodage res = malloc(sizeof(struct listeBinaire));
  if (res != NULL) {
    res->data = data;
    res->suivant = suivant;
  }
  
  return res;
}

void imprime_encodage(FILE *f, encodage e) {
  encodage reste = e;
  while(reste != NULL) {
    fprintf(f, "%i", reste->data);
    reste = reste->suivant;
  }
  fprintf(f, "\n");
}


void libere_encodage(encodage* e) {
  if (*e != NULL) {
    libere_encodage(&(*e)->suivant);
    free(*e);
    *e = NULL;
  }
}

int code_char(arbre a, char c, encodage *e) {
  return 0;
}

encodage code_texte(arbre a, char* s) {
  return NULL; 
}

encodage decode_suivant(FILE* f, arbre a, encodage e) {
  return NULL;
}

void decode(FILE* f, arbre a, encodage e) {
}

