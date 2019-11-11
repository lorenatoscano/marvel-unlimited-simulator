#include "altera.h"
#include "pesquisa.h"


int main()
{
	system("clear");

	printf(" __   __  _______  ______    __   __  _______  ___     \n");
	printf("|  |_|  ||   _   ||    _ |  |  | |  ||       ||   |    \n");
	printf("|       ||  |_|  ||   | ||  |  |_|  ||    ___||   |    \n");
	printf("|       ||       ||   |_||_ |       ||   |___ |   |    \n");
	printf("|       ||       ||    __  ||       ||    ___||   |___ \n");
	printf("| ||_|| ||   _   ||   |  | | |     | |   |___ |       |\n");
	printf("|_|   |_||__| |__||___|  |_|  |___|  |_______||_______|\n\n");
	
	printf("BEM VINDO!\n\n");
	
	int option = 0;
	int qtd;
	HQ* quadrinhos;

	quadrinhos = calloc(200, sizeof(HQ));

	while (option != 7)
	{

		printf("MENU DE OPÇÕES:\n\n");
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




