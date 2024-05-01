#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct liste_solutions{
	int * placement;
	struct liste_solutions * next;
} liste_solutions;

liste_solutions *  addSolution(liste_solutions * liste,int * placement,int n)
{
	liste_solutions * nouvelle = (liste_solutions*)malloc(sizeof(liste_solutions));
	
	nouvelle->next=liste;

	nouvelle->placement=(int*)malloc(n*sizeof(int));
	for (int l=0;l<n;l++){
		nouvelle->placement[l]=placement[l];
	}
	return nouvelle;
}

// Pour visualiser l'échiquier correspondant à un placement donné.
// Le paramètre placement est une liste de n entiers entre 0 et n-1 correspondant au 
// numéro de colonne de chaque dame (sur chaque ligne).
// Si une valeur est négative, aucune dame ne sera placée sur la ligne.
void displayGame(int* placement, int n){
	for (int l = 0; l<n;l++){
		for (int c = 0; c<n;c++){
			if (c== placement[l]){
				printf("|*");
			}
			else{
				printf("|O");
			}
		}
		printf("|\n");
	}
}

int casePossible(int * placement,int l,int c){
	int OK = 1;

	// TO DO question 13
	// Dans cette fonction, seules les valeurs placement[0], placement[1], ... placement[i-1]
	// sont utilisées, les suivantes sont ignorées.

	return OK;
}

liste_solutions *  addAllSolutions(liste_solutions * l_sol, int * placement,int l,int n){

	// TO DO Question 14
	return NULL;
}



void test_casePossible(){
	int placement[]={4,7,5,-1,-1,-1,-1,-1};
	displayGame(placement,8);

	for (int c=0;c<8;c++){
		int l=3;
		printf("casePosssible(%d , %d =%d )\n",l,c,casePossible(placement,l,c));
	}
	return ;
}


int nbSolutions(liste_solutions*l){
	
	// TO DO Question 14

	return 0;
}

void displaySolutions(liste_solutions*l,int n){
	if (l){
		printf("=======================\n");
		for (int ligne=0;ligne<n;ligne++){
			printf("%d ",l->placement[ligne]);
		}
		printf("\n");

		displayGame(l->placement,n);
		displaySolutions(l->next,n);
	}
}

int main(){
	
	liste_solutions * solutions=NULL;
	int n=8;
	
	// TO DO Question 14
	// Compléter ici par un appel à addAllSolutions


	// FIN TO DO

	// Affichage du nombre de solutions et des solutions
	printf("Nombre  de solutions : %d\n",nbSolutions(solutions));
	
	printf("Ensemble des solutions :\n");
	displaySolutions(solutions,n);

	return 0;

}