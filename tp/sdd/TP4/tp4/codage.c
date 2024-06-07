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
  if (a == NULL) {
    return 0;
  }
  if (code_char(a->gauche, c, e)) {
    *e = cree_encodage(0, *e);
    return 1;
  }
  
  if (code_char(a->droite, c, e)) {
    *e = cree_encodage(1, *e);
    return 1;
  }
  
  return 0;
}

encodage code_texte(arbre a, char* s) {
  encodage res = NULL;
  while (*s != '\0') {
    encodage e = NULL;
    code_char(a, *s, &e);
    if (e != NULL) {
      if (res == NULL) {
        res = e;
      } else {
        encodage temp = res;
        while (temp->suivant != NULL) {
          temp = temp->suivant;
        }
        temp->suivant = e;
      }
    }
    s++;
  }
  return res;
}

encodage decode_suivant(FILE* f, arbre a, encodage e) {
  if (a == NULL) {
    return e;
  }
  
  while (e != NULL) {
    if (e->data == 0) {
      a = a->gauche;
    } else {
      a = a->droite;
    }
    
    if (a->gauche == NULL && a->droite == NULL) {
      fprintf(f, "%c", a->data);
      return e->suivant;
    }
    
    e = e->suivant;
  }
  
  return e;
}

void decode(FILE* f, arbre a, encodage e) {
    while (e != NULL) {
      e = decode_suivant(f, a, e);
    }
  
}

