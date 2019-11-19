main: main.c altera.o pesquisa.o
	gcc main.c altera.o pesquisa.o -o marvel -g -W

altera: altera.c
	gcc -c altera.c -g -W

pesquisa: pesquisa.c
	gcc -c pesquisa.c -g -W