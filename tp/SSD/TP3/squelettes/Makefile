OPTIONS=-Wall -Wextra -g
LIB= -lm -lSDL2 
CC=gcc

romains: romains.c
	${CC} -o romains  romains.c  

testLists: listes_tests.o listes.o 
	${CC} -o testLists listes_tests.o  listes.o ${LIB}
listes_tests.o: listes_tests.c
	${CC} ${OPTIONS}  listes_tests.c -c

testBase: base_tests.o  base.o listes.o 
	${CC} -o testBase base_tests.o  base.o listes.o ${LIB}
base.o: base.c  base.h
	${CC} ${OPTIONS} base.c -c
base_tests.o: base_tests.c
	${CC} ${OPTIONS}  base_tests.c -c

listes.o: listes.c  listes.h
	${CC} ${OPTIONS} listes.c -c

dames: dames.o 
	${CC} -o dames dames.o  ${LIB}
dames.o: dames.c  
	${CC} ${OPTIONS} dames.c -c


progSDL: mainSDL.o sierpinski.o
	${CC} -o progSDL mainSDL.o sierpinski.o ${LIB}
mainSDL.o: mainSDL.c  sierpinski.h
	${CC} ${OPTIONS} mainSDL.c -c
sierpinski.o: sierpinski.c sierpinski.h
	${CC} ${OPTIONS} sierpinski.c -c


clean:
	rm -f *.o *.gch 
