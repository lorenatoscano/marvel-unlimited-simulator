#include "altera.h"
#include "pesquisa.h"

//Funções que retiram determinadas informações sem alterar o conteúdo do arquivo

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
