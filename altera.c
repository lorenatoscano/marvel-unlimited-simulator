//Funções que alteram o arquivo e/ou o array

#include "altera.h"
#include "pesquisa.h"

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
        {
            printf("Quadrinho nao encontrado!\n");
            system("rm marvel-tmp.txt");
        }

        system("mv marvel-tmp.txt marvel-data.txt");
	}

	getchar();
	getchar();

	system("clear");
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
						fclose(arq);
        				fclose(novo);
						system("rm marvel-tmp.txt");
						ok = -1;
					}
					else ok = 1;
					
					flag = i;
					break;
				}
			}
		}

		if (ok == 0) 
		{
			printf("Quadrinho não encontrado!\n");
			fclose(arq);
        	fclose(novo);
        	system("rm marvel-tmp.txt");
		}
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
			fclose(arq);
        	fclose(novo);
			system("mv marvel-tmp.txt marvel-data.txt");
		}	
	}

	getchar();
	getchar();

	system("clear");
}