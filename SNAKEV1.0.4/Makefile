snake : main.o menu.o jeu.o
	gcc -o snake main.o menu.o jeu.o `pkg-config --libs MLV`

main.o : main.c fct_menu.h fct_types.h
	gcc -c -Wall `pkg-config --cflags MLV` main.c -o main.o


menu.o : fonctions_menu.c fct_menu.h
	gcc -c -Wall `pkg-config --cflags MLV` fonctions_menu.c -o menu.o

jeu.o : fonctions_jeu.c fct_types.h fct_menu.h
	gcc -c -Wall `pkg-config --cflags MLV` fonctions_jeu.c -o jeu.o

clean :
	rm -rf *.o *~ snake