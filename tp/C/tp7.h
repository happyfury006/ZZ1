#include <stdio.h>
#ifdef tp7_h
#define tp7_h

typedef struct cellule 
{
  char           * ligne;
  struct cellule * suivant;
} cellule_t;


typedef struct liste 
{
  cellule_t * tete;
  cellule_t * fin;
} liste_t;

#endif