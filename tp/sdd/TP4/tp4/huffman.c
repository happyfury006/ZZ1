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
  int freq[256] = {0}; // Initialisation
  int i = 0;
  
  // Détermine la fréquence des éléments dans la chaine de caractère
  while (s[i] != '\0') {
    freq[(unsigned char)s[i]]+=1;
    i++;
  }
  
  liste res = NULL;
  
  // Create a list of associations of leaf and weight
  for (i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      arbrepoids a = cree_arbrepoids((unsigned char)i, freq[i]);
      res = cree_liste(a, freq[i], res);
    }
  }
  
  return res;
}

arbrepoids extrait_min(liste *l) {
  if (*l == NULL) {
    return NULL;
  }
  
  liste min = *l;
  liste prec = NULL;
  liste courant = *l;
  
  // Trouver le minimum dans l'arbre
  while (courant->suivant != NULL) {
    if (courant->suivant->data->poids < min->data->poids) {
      min = courant->suivant;
      prec = courant;
    }
    courant = courant->suivant;
  }
  
  // suppression du minimum 
  if (prec == NULL) {
    *l = min->suivant;
  } else {
    prec->suivant = min->suivant;
  }
  
  arbrepoids ap = min->data;
  free(min);
  
  return ap;
}

arbre huffman(char* s) {
  liste lf=genere_liste(s);
  arbre newabr =NULL;

  while (lf->suivant != NULL)
  {
    arbrepoids min1 = extrait_min(&lf);
    arbrepoids min2 = extrait_min(&lf);

    newabr = cree_arbrepoids('*',min1->poids + min2->poids);
    newabr->gauche = min1->element;
    newabr->droite = min2->element;
  }
  
  return newabr;
}

