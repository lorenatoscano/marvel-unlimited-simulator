#include "altera.h"
#include "pesquisa.h"


int main()
{
	system("clear");

	printf("                                                                                                                                                   \n");
	printf("WWWWWWWW                           WWWWWWWW               lllllll                                                                                  \n");
	printf("W::::::W                           W::::::W               l:::::l                                                                                  \n");
	printf("W::::::W                           W::::::W               l:::::l                                                                                  \n");
	printf("W::::::W                           W::::::W               l:::::l                                                                                  \n");
	printf(" W:::::W           WWWWW           W:::::W eeeeeeeeeeee    l::::l     cccccccccccccccc   ooooooooooo      mmmmmmm    mmmmmmm       eeeeeeeeeeee    \n");
	printf("  W:::::W         W:::::W         W:::::Wee::::::::::::ee  l::::l   cc:::::::::::::::c oo:::::::::::oo  mm:::::::m  m:::::::mm   ee::::::::::::ee  \n");
	printf("   W:::::W       W:::::::W       W:::::We::::::eeeee:::::eel::::l  c:::::::::::::::::co:::::::::::::::om::::::::::mm::::::::::m e::::::eeeee:::::ee\n");
	printf("    W:::::W     W:::::::::W     W:::::We::::::e     e:::::el::::l c:::::::cccccc:::::co:::::ooooo:::::om::::::::::::::::::::::me::::::e     e:::::e\n");
	printf("     W:::::W   W:::::W:::::W   W:::::W e:::::::eeeee::::::el::::l c::::::c     ccccccco::::o     o::::om:::::mmm::::::mmm:::::me:::::::eeeee::::::e\n");
	printf("      W:::::W W:::::W W:::::W W:::::W  e:::::::::::::::::e l::::l c:::::c             o::::o     o::::om::::m   m::::m   m::::me:::::::::::::::::e \n");
	printf("       W:::::W:::::W   W:::::W:::::W   e::::::eeeeeeeeeee  l::::l c:::::c             o::::o     o::::om::::m   m::::m   m::::me::::::eeeeeeeeeee  \n");
	printf("        W:::::::::W     W:::::::::W    e:::::::e           l::::l c::::::c     ccccccco::::o     o::::om::::m   m::::m   m::::me:::::::e           \n");
	printf("         W:::::::W       W:::::::W     e::::::::e         l::::::lc:::::::cccccc:::::co:::::ooooo:::::om::::m   m::::m   m::::me::::::::e          \n");
	printf("          W:::::W         W:::::W       e::::::::eeeeeeee l::::::l c:::::::::::::::::co:::::::::::::::om::::m   m::::m   m::::m e::::::::eeeeeeee  \n");
	printf("           W:::W           W:::W         ee:::::::::::::e l::::::l  cc:::::::::::::::c oo:::::::::::oo m::::m   m::::m   m::::m  ee:::::::::::::e  \n");
	printf("            WWW             WWW            eeeeeeeeeeeeee llllllll    cccccccccccccccc   ooooooooooo   mmmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee  \n");
	printf("                                                                                                                                                   \n\n");
	
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




