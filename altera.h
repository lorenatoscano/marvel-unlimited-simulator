//Funções que alteram o arquivo e/ou o array

#ifndef ALTERA_H
#define ALTERA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char nome[100];
	int num;
	int mes, ano;
	int lido;
	int qtd;
	char pers[50][100];
} HQ;

void carrega_base(HQ*, int*);
void adiciona(HQ*);
void remove_hq(HQ*);
void marca_lido(HQ*);

#endif