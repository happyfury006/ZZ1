#include "arbre.h"

#ifndef DECODAGE_H
#define DECODAGE_H

typedef int binaire;

typedef struct listeBinaire { 
  binaire data;
  struct listeBinaire *suivant; 
} *encodage;

encodage cree_encodage(binaire data, encodage suivant);

void libere_encodage(encodage* e);

void imprime_encodage(FILE* f, encodage e);


int code_char(arbre a, char c, encodage *e);

encodage code_texte(arbre a, char* s);

encodage decode_suivant(FILE* f, arbre a, encodage e);

void decode(FILE* f, arbre a, encodage e);

#endif
