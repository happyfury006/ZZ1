#include <stdio.h>
#include <string.h>
#include "listes.h"
#include "base.h"

list* liste_de_test(){
	list * l =listCreate();
	l =listAdd(l, 1 );
	l =listAdd(l, 10 );
	l =listAdd(l, 15 );
	l =listAdd(l,5 );
	return l;

}

void test_printBaseB(){
	setBase(16);
	list * l=liste_de_test();
	printf("Affichage d'un nombre en base 16 : ");
	printBaseB(l);
	printf("\n");
	listFree(l);
}

void test_baseToDec(){
	setBase(16);
	list * l=liste_de_test();
	printf("Conversion en décimal : %d\n",baseToDec(l));

	listFree(l);
}
void test_baseToDec2(){
	setBase(16);
	list * l=liste_de_test();
	printf("Conversion en décimal méthode 2 : %d\n",baseToDec2(l));

	listFree(l);
}
void test_decToBase(){
	setBase(16);
	list * l=decToBase(6901);
	printf("Conversion en base b : ");
	printBaseB(l);
	printf("\n");

	listFree(l);
}

void test_global(int n,int b)
{
	setBase(b);
	
	list * l = decToBase(n);
	printf("Nombre initial , %d\n",n);
	printf("Nombre en base %d : ",b);
	printBaseB(l);
	printf("\n");
	printf("Nombre retransformé en décimal %d \n",baseToDec(l));

	listFree(l);

}

int main()
{
	test_printBaseB();
	test_baseToDec();
	test_baseToDec2();
	test_decToBase();
	
	test_global(55,2);
	test_global(55,8);
	test_global(55,16);

	/*setBase(2);
	test_base();
	setBase(16);
	test_base();*/
}
