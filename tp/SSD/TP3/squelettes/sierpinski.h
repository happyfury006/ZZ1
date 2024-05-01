#ifndef sierpinski_h
#define sierpinski_h

typedef struct point{
	double x;
	double y;
} point;

typedef struct triangle{
	point A;
	point B;
	point C;
} triangle;

typedef struct list_triangles{
	triangle ABC;
	struct list_triangles * next ;
} list_triangles;


// Ajout d'un triangle en tete de liste
list_triangles * addTriangle(list_triangles * l,triangle ABC);

// Génération de la liste de triangles correspondant à la fractale à l'étape n
void sierpinski_n(list_triangles * l,int n);

// Libération de la mémoire
void listTrianglesFree(list_triangles * l);

#endif