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
void busca(HQ*);
void consulta(HQ*);
void consulta1(HQ*, int);
void consulta2(HQ*, int);
void consulta3(HQ*, int);
void consulta4(HQ*, int);
void consulta5(HQ*, int);
void marca_lido(HQ*);

int main()
{
	system("clear");

	int option = 0;
	int qtd;
	HQ* quadrinhos;

	quadrinhos = calloc(200, sizeof(HQ));

	while (option != 7)
	{

		printf("MENU DE OPÇÕES:\n");
		printf("1 - Carregar base de dados\n");
		printf("2 - Adicionar um quadrinho\n");
		printf("3 - Remover um quadrinho\n");
		printf("4 - Consultar um quadrinho\n");
		printf("5 - Consultas Gerais\n");
		printf("6 - Marcar como lido:\n");
		printf("7 - Sair​\n\n");

		scanf("%d", &option);

		switch (option)
		{
			case 1: carrega_base(quadrinhos, &qtd); break;
			case 2: adiciona(quadrinhos); break;
			case 3: remove_hq(quadrinhos); break;
			case 4: busca(quadrinhos); break;
			case 5: consulta(quadrinhos); break;
			case 6: marca_lido(quadrinhos); break;
			case 7: break;
			default: printf("Opção inválida!\n");
		}
	}

	system("clear");

	return 0;
}

void carrega_base(HQ quad[200], int* n)
{
	system("clear");

	FILE* arq = fopen("marvel-data.txt", "r");
	
	int i = 0, j = 0, k, l;
	int tam, qtd, flag;
	char linha[1000], tail[1000], aux[1000], str[100];
	char* temp;

	if (arq == NULL) printf("Base de dados vazia!\n");
	else
	{
		printf("Carregando base de dados...\n\n");
		
		//Le linha por linha ate o final
		while(fgets(linha, 1000, arq) != NULL)
		{
			//Le o titulo
			sscanf(linha, "%[^;]s", quad[i].nome);

			//Guarda o resto numa string auxiliar
			for(k=strlen(quad[i].nome), l = 0; linha[k] != '\0'; k++, l++)
                tail[l] = linha[k];

            tail[l] = '\0';

            //Retira da auxiliar o restante das informacoes
			sscanf(tail, "; %d; %d/%d; %d; %d;", &quad[i].num, &quad[i].mes, &quad[i].ano, &quad[i].lido, &quad[i].qtd);

			//Repete o processo pra guardar o resto da linha
			for(k=21, l = 0; tail[k] != '\0'; k++, l++)
                aux[l] = tail[k];
            aux[l - 1] = '\0';

			temp = strtok(aux, ",");
			j = 0;
			while(temp != NULL)
			{
				strcpy(quad[i].pers[j], temp);
				j++;
				temp = strtok(NULL, ",");
			}
			
			i++;
		}
		*n = i;

		fclose(arq);
	}
}

void adiciona(HQ quad[200])	
{
	system("clear");

	FILE* arq = fopen("marvel-data.txt", "a");

	HQ novo;
	int i = 0, ins = 0, res, qtd, n;
	
	if (arq == NULL) printf("Erro na abertura do arquivo!\n");
	else
	{
		carrega_base(quad, &n);

		printf("Digite as informações do quadrinho que deseja adicionar:\n\n");
		printf("Título:\n");
		scanf(" %[^\n]s", novo.nome);
		printf("Número:\n");
		scanf("%d", &novo.num);

		//Verifica se o quadrinho ja existe
		for (i = 0; i < n; i++)
		{
			res = strcmp(novo.nome, quad[i].nome);
			if (res == 0)
			{
				if (quad[i].num == novo.num)
				{
					printf("Esse quadrinho já está cadastrado!\n");
					ins = 1;
					break;
				}
			}
		}

		//Se nao foi cadastrado, le as demais informacoes
		if (ins == 0)
		{
			printf("Mês e ano de publicação (no formato mês/ano):\n");
			scanf("%d/%d", &novo.mes, &novo.ano);

			novo.lido = 0;

			printf("Quantos personagens deseja adicionar?\n");
			scanf("%d", &novo.qtd);
			printf("Insira os personagens separados por enter:\n");
			for (i = 0; i < novo.qtd; ++i)
				scanf(" %[^\n]s", novo.pers[i]);

			//Insere as informações no arquivo:
			fprintf(arq, "%s; ", novo.nome);

			//Faz o tratamento para imprimir os numeros com duas casas
			if (novo.num < 10) 
			{
				if (novo.mes < 10)
					fprintf(arq, "0%d; 0%d/%d; %d; %d; ", novo.num, novo.mes, novo.ano, novo.lido, novo.qtd);
				else	
					fprintf(arq, "0%d; %d/%d; %d; %d; ", novo.num, novo.mes, novo.ano, novo.lido, novo.qtd);
			}
			else if (novo.mes < 10) 
				fprintf(arq, "%d; 0%d/%d; %d; %d; ", novo.num, novo.mes, novo.ano, novo.lido, novo.qtd);
			else 
				fprintf(arq, "%d; %d/%d; %d; %d; ", novo.num, novo.mes, novo.ano, novo.lido, novo.qtd);
			
			for (i = 0; i < novo.qtd; ++i)
			{
				fprintf(arq, "%s,", novo.pers[i]);
			}
			fprintf(arq, "\n");

			printf("Cadastro feito com sucesso!\n");
		}
		fclose(arq);
	}
	
	getchar();
	getchar();

	system("clear");
}

void remove_hq(HQ quad[200])
{
	system("clear");

	FILE* arq = fopen("marvel-data.txt", "r");
	FILE* novo = fopen("marvel-tmp.txt", "w");

	HQ del;
	int i, ok = 0, n;
	int num;
	char linha[1000], tit[200];

	if (arq == NULL || novo == NULL) printf("Erro na abertura do arquivo!\n");
	else
	{
		carrega_base(quad, &n);

		printf("Digite as informações do quadrinho que deseja remover:\n\n");
		printf("Título:\n");
		scanf(" %[^\n]s", del.nome);
		printf("Número:\n");
		scanf("%d", &del.num);

		printf("Deletar %s %d\n", del.nome, del.num);

		while(fgets(linha, 1000, arq) != NULL)
		{
			//Le o titulo e o numero no arquivo
			sscanf(linha, "%[^;]; %d", tit, &num);

			//Se for diferente do del, copia para o novo
			if(strcmp(tit, del.nome) != 0 && num != del.num)
				fprintf(novo, "%s", linha);
			//Senao, informo que a remocao ocorreu
			else
				ok = 1;

		}
		
		fclose(arq);
        fclose(novo);

        if(ok == 1)
            printf("Remocao realizada com sucesso!\n");
        else
            printf("Quadrinho nao encontrado!\n");

        system("mv marvel-tmp.txt marvel-data.txt");
	}

	getchar();
	getchar();

	system("clear");
}

void busca(HQ quad[200])
{
	HQ busc; 
	int i, j, ok = 0, flag, res, n;
	carrega_base(quad, &n);

	printf("Digite as informações do quadrinho que deseja buscar:\n\n");
	printf("Título:\n");
	scanf(" %[^\n]s", busc.nome);
	printf("Número:\n");
	scanf("%d", &busc.num);


	printf("\nBuscando quadrinho...\n\n");

	//Verifica se existe na base de dados
	for (i = 0; i < n; i++)
	{
		res = strcmp(busc.nome, quad[i].nome);
		if (res == 0)
		{
			if (quad[i].num == busc.num)
			{
				flag = i;
				ok = 1;
				break;
			}
		}
	}


	if (ok == 0) printf("Quadrinho nao encontrado!\n");
	else
	{
		printf(">> %s %d <<\n", quad[flag].nome, quad[flag].num);
		printf("Data de publicação: %d/%d\n", quad[flag].mes, quad[flag].ano);
		printf("Status de leitura: ");
		if (quad[flag].lido == 0) printf("Não lido\n");
		else if (quad[flag].lido == 1) printf("Lido\n");
		printf("Personagens:\n");
		for (i = 0; i < quad[flag].qtd; i++)
		{
			printf("-%s\n", quad[flag].pers[i]);
		}
	}

	getchar();
	getchar();

	system("clear");
}

void consulta(HQ quad[200])
{
	system("clear");

	int option = 0, n;

	carrega_base(quad, &n);

	printf("LISTAR QUADRINHOS POR: \n");
	printf("1- Ano\n");
	printf("2 - Período\n");
	printf("3 - Personagem\n");
	printf("4 - Série/Título\n");
	printf("5 - Status de leitura\n\n");

	scanf("%d", &option);

	switch(option)
	{
		case 1: consulta1(quad, n); break;
		case 2: consulta2(quad, n); break;
		case 3: consulta3(quad, n); break;
		case 4: consulta4(quad, n); break;
		case 5: consulta5(quad, n); break;
		default: printf("Opção inválida!\n");
	}

	getchar();
	getchar();

	system("clear");
}

void consulta1(HQ quad[200], int n)
{
	int ano, i, ok = 0;

	printf("Informe o ano a ser consultado:\n");
	scanf("%d", &ano);

	printf("\nBuscando quadrinhos publicados em %d...\n\n", ano);
	//Busca os quadrinhos publicados naquele ano
	for (i = 0; i < n; i++)
	{
		if (quad[i].ano == ano)
		{
			printf("- %s %d\n", quad[i].nome, quad[i].num);
			ok = 1;
		}
	}

	if (ok == 0) printf("Nenhum quadrinho cadastrado para o ano informado\n");
}

void consulta2(HQ quad[200], int n)
{
	int mi, ai, mf, af, i, ok = 0;

	printf("Informe o período da sua consulta\n");
	printf("Mês e ano iniciais (na forma mês/ano, 10/1985, por exemplo):\n");
	scanf("%d/%d", &mi, &ai);
	printf("Mês e o ano finais:\n");
	scanf("%d/%d", &mf, &af);

	printf("\nBuscando quadrinhos publicados de %d/%d a %d/%d...\n", mi, ai, mf, af);

	for (i = 0; i < n; i++)
	{
		if (ai == af)
		{
			if(quad[i].mes >= mi && quad[i].mes <= mf)
			{
				printf("- %s %d\n", quad[i].nome, quad[i].num);
				ok = 1;
			}
		}
		else //Anos diferentes
		{
			if(quad[i].ano > ai && quad[i].ano < af)
			{
				printf("- %s %d\n", quad[i].nome, quad[i].num);
				ok = 1;
			}
			else if(quad[i].ano == ai && quad[i].mes >= mi)
			{
				printf("- %s %d\n", quad[i].nome, quad[i].num);
				ok = 1;
			}
			else if(quad[i].ano == af && quad[i].mes <= mf)
			{
				printf("- %s %d\n", quad[i].nome, quad[i].num);
				ok = 1;
			}
		}
	}
	if (ok == 0) printf("Nenhum quadrinho cadastrado para o período informado\n");

}

void consulta3(HQ quad[200], int n)
{
	char personagem[100];
	HQ aux[n];
	HQ sup;
	int i, j, k = 0, ok = 0;

	printf("Informe o personagem de deseja procurar:\n");
	scanf(" %[^\n]s", personagem);

	printf("\nBuscando quadrinhos com %s...\n", personagem);

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < quad[i].qtd; j++)
		{
			if (strcmp(quad[i].pers[j], personagem) == 0)
			{
				aux[k] = quad[i];
				k++;
				ok = 1;
			}
		}
	}
	if (ok == 0) printf("Nenhum quadrinho cadastrado com o personagem informado\n");
	else
	{	
		//Ordena o vetor
		for (i = k - 1; i > 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				if (aux[j].ano == aux[j + 1].ano)
				{
					if (aux[j].mes > aux[j + 1].mes)
					{
						sup = aux[j];
						aux[j] = aux[j + 1];
						aux[j + 1] = sup;
					}
				}

				else if(aux[j].ano > aux[j + 1].ano)
				{
					sup = aux[j];
					aux[j] = aux[j + 1];
					aux[j + 1] = sup;
				}
			}
		}
	}

	for (i = 0; i < k; i++)
		printf("- %s %d - %d/%d\n", aux[i].nome, aux[i].num, aux[i].mes, aux[i].ano);

	

}

void consulta4(HQ quad[200], int n)
{
	char titulo[100];
	int i, ok = 0;

	printf("Informe série/título que deseja consultar:\n");
	scanf(" %[^\n]s", titulo);

	printf("\nBuscando quadrinhos de %s...\n\n", titulo);


	for (i = 0; i < n; i++)
	{
		if (strcmp(titulo, quad[i].nome) == 0)
		{
			printf("- %s %d\n", quad[i].nome, quad[i].num);
			ok = 1;
		}
	}

	if (ok == 0) printf("Nenhum quadrinho cadastrado para o parâmetro informado\n");
}

void consulta5(HQ quad[200], int n)
{
	int i, ok = 0;

	printf("\nBuscando quadrinhos marcados como 'lido'...\n\n");
	
	for (i = 0; i < n; i++)
	{
		if (quad[i].lido == 1)
		{
			printf("- %s %d\n", quad[i].nome, quad[i].num);
			ok = 1;
		}
	}

	if (ok == 0) printf("Nenhum quadrinho cadastrado para parâmetro informado\n");

}

void marca_lido(HQ quad[])
{
	system("clear");

	FILE* arq = fopen("marvel-data.txt", "r");
	FILE* novo = fopen("marvel-tmp.txt", "w");

	HQ busc;
	int i, ok = 0, n, res, flag;
	int num;
	char linha[1000], tit[200];

	if (arq == NULL || novo == NULL) printf("Erro na abertura do arquivo!\n");
	else
	{
		carrega_base(quad, &n);

		printf("Digite as informações do quadrinho que deseja marcar como lido:\n\n");
		printf("Título:\n");
		scanf(" %[^\n]s", busc.nome);
		printf("Número:\n");
		scanf("%d", &busc.num);

		//Verifica se o quadrinho está cadastrado e qual seu status
		for (i = 0; i < n; i++)
		{
			res = strcmp(busc.nome, quad[i].nome);
			if (res == 0)
			{
				if (quad[i].num == busc.num)
				{
					if (quad[i].lido == 1)
					{
						printf("Quadrinho já marcado!\n");
						ok = -1;
					}
					else ok = 1;
					
					flag = i;
					break;
				}
			}
		}

		if (ok == 0) printf("Quadrinho não encontrado!\n");
		else if (ok == 1)
		{
			quad[flag].lido = 1;

			while(fgets(linha, 1000, arq) != NULL)
			{
				//Le o titulo e o numero no arquivo
				sscanf(linha, "%[^;]; %d", tit, &num);

				//Se for igual ao que o usuario digitou, imprime as informações no arquivo com a alteração
				if(strcmp(tit, busc.nome) == 0 && num == busc.num)
				{
					fprintf(novo, "%s; ", quad[flag].nome);

					//Faz o tratamento para imprimir os numeros com duas casas
					if (quad[flag].num < 10) 
					{
						if (quad[flag].mes < 10)
							fprintf(novo, "0%d; 0%d/%d; %d; %d; ", quad[flag].num, quad[flag].mes, quad[flag].ano, quad[flag].lido, quad[flag].qtd);
						else	
							fprintf(novo, "0%d; %d/%d; %d; %d; ", quad[flag].num, quad[flag].mes, quad[flag].ano, quad[flag].lido, quad[flag].qtd);
					}
					else if (quad[flag].mes < 10) 
						fprintf(novo, "%d; 0%d/%d; %d; %d; ", quad[flag].num, quad[flag].mes, quad[flag].ano, quad[flag].lido, quad[flag].qtd);
					else 
						fprintf(novo, "%d; %d/%d; %d; %d; ", quad[flag].num, quad[flag].mes, quad[flag].ano, quad[flag].lido, quad[flag].qtd);
					
					for (i = 0; i < quad[flag].qtd; ++i)
					{
						fprintf(novo, "%s,", quad[flag].pers[i]);
					}
					fprintf(novo, "\n");
				}

				//Senao, so copio a linha para o novo
				else 
					fprintf(novo, "%s", linha);
			}

			printf("Alteração realizada com sucesso!");
			system("mv marvel-tmp.txt marvel-data.txt");
		}	
		
		fclose(arq);
        fclose(novo);
	}

	getchar();
	getchar();

	system("clear");
}