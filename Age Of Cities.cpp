#include <stdio.h> // printf, scanf_s
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct efects
{
	/*****************************EFECTS***************************************/
#define NONE        "\033[32m"
#define BOLD        "\033[1m"
#define HALFBRIGHT  "\033[2m"
#define UNDERSCORE  "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"

/*****************************COLORS***************************************/
#define C_BLACK     "\033[30m"
#define C_RED       "\033[31m"
#define C_GREEN     "\033[32m"
#define C_YELLOW    "\033[33m"
#define C_BLUE      "\033[34m"
#define C_MAGENTA   "\033[35m"
#define C_CYAN      "\033[36m"
#define C_GRAY      "\033[37m"
#define C_WHITE     "\033[0m"

/***************************BACKGROUNDS************************************/
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_GRAY     "\033[47m"
};

using namespace std;

bool vivo[4] = { true, true, true, true }; // se o player está vivo
bool atacado[4]{ false, false, false, false }; // se um player está sendo atacado
int atacante[4]{ 0,0,0,0 };// o numero do player alvo, na posição 0 é o player 1 e assim sucessivamente
int tempoatq[4]{ 0,0,0,0 };// contagem do tempo até um exérito chegar a um xy local no mapa
int mapa[20][25]; // mapa tem que ser global.
int turno = 0, qtp = 0; // qtd de players.

void map();
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void converter_hab(int* vez, int* tipop, int* hab)
{
	char c;
	int qtd_soldados[3] = { 0, 0, 0 };
	system("cls");
	while ((qtd_soldados[0] == 0) && (qtd_soldados[1] == 0) && (qtd_soldados[2] == 0))
	{
		printf("Quantos habitantes deseja converter para soldados?\nNo máximo 50 por cento da população pode ser convertida em soldados!!\n");
		printf("Humanos - %i         Gigantes - %i          Goblins - %i\n", hab[0], hab[1], hab[2]);
		do
		{
			system("cls");
			printf("Quantos habitantes deseja converter para soldados?\nNo máximo 50 por cento da população pode ser convertida em soldados!!\n");
			printf("Humanos - %i         Gigantes - %i          Goblins - %i\n", hab[0], hab[1], hab[2]);
			printf("Humanos - ");
			scanf_s("%i", &qtd_soldados[0]);
		} while ((c = getchar() != '\n' && c != EOF) || (qtd_soldados[0] > (hab[0] / 2) && (qtd_soldados[0] < 0)));
		do
		{
			system("cls");
			printf("Quantos habitantes deseja converter para soldados?\nNo máximo 50 por cento da população pode ser convertida em soldados!!\n");
			printf("Humanos - %i         Gigantes - %i          Goblins - %i\n", hab[0], hab[1], hab[2]);
			printf("Humanos - %i\n", qtd_soldados[0]);
			printf("\nGigantes - ");
			scanf_s("%i", &qtd_soldados[1]);
		} while ((c = getchar() != '\n' && c != EOF) || (qtd_soldados[1] > (hab[2] / 2) && (qtd_soldados[1] < 0)));
		do
		{
			system("cls");
			printf("Quantos habitantes deseja converter para soldados?\nNo máximo 50 por cento da população pode ser convertida em soldados!!\n");
			printf("Humanos - %i         Gigantes - %i          Goblins - %i\n", hab[0], hab[1], hab[2]);
			printf("Humanos - %i\n", qtd_soldados[0]);
			printf("\nGigantes- %i\n", qtd_soldados[1]);
			printf("\nGoblins - ");
			scanf_s("%i", &qtd_soldados[2]);
		} while ((c = getchar() != '\n' && c != EOF) || (qtd_soldados[2] > (hab[2] / 2) && (qtd_soldados[2] < 0)));
	}
	printf("\n\nPressione qualquer tecla para ver o resultado!!\n");
	system("pause");

	hab[0] = hab[0] - qtd_soldados[0];
	hab[1] = hab[1] - qtd_soldados[1];
	hab[2] = hab[2] - qtd_soldados[2];
	tipop[0] = tipop[0] + qtd_soldados[0];
	tipop[1] = tipop[1] + qtd_soldados[1];
	tipop[2] = tipop[2] + qtd_soldados[2];

	system("cls");
	printf("Quantidade de soldados:\n");
	printf("Soldados Humanos - %i\n", tipop[0]);
	printf("Soldados Gigantes- %i\n", tipop[1]);
	printf("Soldados Goblins - %i\n", tipop[2]);
	printf("\n\nQuatidade de habitantes restantes:\n");
	printf("Humanos - %i\n", hab[0]);
	printf("Gigantes- %i\n", hab[1]);
	printf("Goblins - %i\n", hab[2]);
	printf("\n\nPressione qualquer tecla para terminar sua vez!!\n");
	system("pause");
	*vez = 0;

}

struct recursos
{
	int madeira[20][25];
	int alimento[20][25];
	int pedra[20][25];
	int ocupado[20][25];
}; struct recursos recursos;

int constrjg[20][25]; // mapa de construções

// Struct de variaveis para contagem de construções, e armazenamento das construções
struct var_construcao
{
	//contador de turnos, e armazenamento das casas para distribuir em determinado turno
	int casas1[3][3] = { {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} };
	int casas2[3][3] = { {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} };
	int casas3[3][3] = { {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} };
	int casas4[3][3] = { {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} };

	//contador de construções simultaneas
	int qtd_construcoes[4] = { 0, 0, 0, 0 };

	//armazenar construções (muralha, templo, quartel) até dar o turno para distribui-las
	int construcao1[3] = { -1,-1,-1 };
	int construcao2[3] = { -1,-1,-1 };
	int construcao3[3] = { -1,-1,-1 };
	int construcao4[3] = { -1,-1,-1 };

	int acao[4][3];
	int controle = 0;

}; struct var_construcao vct;


void ataque(int* vez, int* tipop, int* atq, int* def, int* xp, int* yp, int* exercito)
{
	int n, x, y, i;
	char c = 0;
	exercito[0] = 0;
	exercito[1] = 0;
	exercito[2] = 0;
	n = *vez;
	system("CLS");
	gotoxy(19, 5);
	printf("=================================================================================");
	gotoxy(19, 6);
	printf("|DIGITE ESC PARA VOLTAR AO MENU OU PRESSIONE QUALQUER OUTRA TECLA PARA CONTINUAR|");
	gotoxy(19, 7);
	printf("=================================================================================");
	i = _getch();
	if (i == 27)
	{
		return;
	}

	do
	{
		do
		{
			system("CLS");
			printf("Digite qual player você quer atacar \n");
			printf("1 - Player 1\n");
			printf("2 - Player 2\n");
			printf("3 - Player 3\n");
			printf("4 - Player 4\n");
			scanf_s("%i", &n);
		} while (c = getchar() != '\n' && c != EOF);
		if (atacado[n - 1] == true)
		{
			printf("Este player já está sendo atacado, não permitimos covardias aqui!!!!\n");
			printf("Digite ESC para voltar ao menu inicial ou qualquer outra tecla para continuar!!!\n");
			system("CLS");
			if (i == 27)
			{
				return;
			}
		}
	} while ((n == *vez) || (n > qtp) || (vivo[n - 1] == false));
	system("CLS");
	printf("Escolha a coordenada do mapa em que você quer atacar\n");
	printf("Você deve atacar o territorio do player escolhido, Player %i\n", n);
	system("Pause");
	do
	{
		map();
		do
		{
			system("CLS");
			printf("\nDigite posição em x: ");
			scanf_s("%d", &x);
		} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
		do
		{
			printf("\nDigite posição em y: ");
			scanf_s("%d", &y);
			system("CLS");
		} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
	} while (mapa[x][y] != n);


	do
	{
		system("cls");
		printf("Escolha a quantidade de soldados que deseja mandar para atacar:\n\n");
		printf("Humanos - %i (15 de ataque / 10 de defesa)\nGigantes - %i (5 de ataque / 20 de defesa)\nGoblins - %i (20 de ataque / 5 de defesa)\n\n", tipop[0], tipop[1], tipop[2]);
		printf("Humanos - ");
		scanf_s("%i", &exercito[0]);
	} while ((c = getchar() != '\n' && c != EOF) || (exercito[0] > tipop[0]));
	do
	{
		system("cls");
		printf("Escolha a quantidade de soldados que deseja mandar para atacar:\n\n");
		printf("Humanos - %i (15 de ataque / 10 de defesa)\nGigantes - %i (5 de ataque / 20 de defesa)\nGoblins - %i (20 de ataque / 5 de defesa)\n\n", tipop[0], tipop[1], tipop[2]);
		printf("Humanos - %i", exercito[0]);
		printf("\nGigantes - ");
		scanf_s("%i", &exercito[1]);
	} while ((c = getchar() != '\n' && c != EOF) || (exercito[1] > tipop[1]));
	do
	{
		system("cls");
		printf("Escolha a quantidade de soldados que deseja mandar para atacar:\n\n");
		printf("Humanos - %i (15 de ataque / 10 de defesa)\nGigantes - %i (5 de ataque / 20 de defesa)\nGoblins - %i (20 de ataque / 5 de defesa)\n\n", tipop[0], tipop[1], tipop[2]);
		printf("Humanos - %i\n", exercito[0]);
		printf("Gigantes - %i\n", exercito[1]);
		printf("Goblins - ");
		scanf_s("%i", &exercito[2]);
	} while ((c = getchar() != '\n' && c != EOF) || (exercito[2] > tipop[2]));

	system("cls");
	printf("Escolha a quantidade de soldados que deseja mandar para atacar:\n\n");
	printf("Humanos - %i (15 de ataque / 10 de defesa)\nGigantes - %i (5 de ataque / 20 de defesa)\nGoblins - %i (20 de ataque / 5 de defesa)\n\n", tipop[0], tipop[1], tipop[2]);
	printf("Humanos  - %i\n", exercito[0]);
	printf("Gigantes - %i\n", exercito[1]);
	printf("Goblins  - %i\n", exercito[2]);
	printf("Pressione qualquer tecla para continuar\n");
	_getch();
	system("CLS");
	tempoatq[*vez - 1] = int(sqrt((pow((x - *xp), 2)) + (pow((y - *yp), 2))));
	printf("Levará %i turnos para seu exército chegar ao seu alvo, contagem regressiva para a batalha!", tempoatq[*vez - 1]);
	tipop[0] = tipop[0] - exercito[0];
	tipop[1] = tipop[1] - exercito[1];
	tipop[2] = tipop[2] - exercito[2];
	*atq = (exercito[0] * 15) + (exercito[1] * 5) + (exercito[2] * 20);
	*def = (exercito[0] * 10) + (exercito[1] * 20) + (exercito[2] * 5);
	printf("Total de ataque e defesa sem bonus (bonus serão aplicados automaticamente na batalha, se houver):\n");
	printf("Ataque : %i\n", *atq);
	printf("Defesa : %i", *def);
	_getch();
	atacado[n - 1] = true;
	atacante[*vez - 1] = n;
	*vez = 0;

}
//função para não deixar construir caso ja esteja construindo quartel, muralha ou templo 
void n_constroi(int* vez, int* n)
{

	//bloqueia caso tenha mais de duas construções simultâneas
	if ((*vez == 1) && (vct.qtd_construcoes[0] > 1))
	{
		system("cls");
		printf("Você já alcançou seu limite de 2 construções simultâneas\nPor favor volte após uma das duas construções terminar!!\n\n");
		system("pause");
		vct.controle = 1;
	}

	if ((*vez == 2) && (vct.qtd_construcoes[1] > 1))
	{
		system("cls");
		printf("Você ja alcançou seu limite de 2 construç~es simultâneas\nPor favor volte após uma das duas construções terminar!!\n\n");
		system("pause");
		vct.controle = 1;
	}

	if ((*vez == 3) && (vct.qtd_construcoes[2] > 1))
	{
		system("cls");
		printf("Você ja alcançou seu limite de 2 construç~es simultâneas\nPor favor volte após uma das duas construções terminar!!\n\n");
		system("pause");
		vct.controle = 1;
	}

	if ((*vez == 4) && (vct.qtd_construcoes[3] > 1))
	{
		system("cls");
		printf("Você ja alcançou seu limite de 2 construç~es simultâneas\nPor favor volte após uma das duas construções terminar!!\n\n");
		system("pause");
		vct.controle = 1;
	}
	/*********************************************************/

	//player 1
	if ((*vez == 1) && ((vct.construcao1[0] > 0) && (vct.acao[0][0] > 0) && (*n == 62)))
	{
		system("cls");
		printf("Não é possível construir mais de uma Muralha\nA construção da Muralha já está em andamento. Acesse as informações para obter mais detalhes!!\n");
		system("pause");
		vct.controle = 1;
	}
	else
	{
		if ((*vez == 1) && ((vct.construcao1[1] > 0) && (vct.acao[0][1] > 0) && (*n == 61)))
		{
			system("cls");
			printf("Não é possível construir mais de um Templo\nA construção do Templo já está em andamento. Acesse as informações para obter mais detalhes!!\n");
			system("pause");
			vct.controle = 1;
		}
		else
		{
			if ((*vez == 1) && ((vct.construcao1[2] > 0) && (vct.acao[0][2] > 0) && (*n == 60)))
			{
				system("cls");
				printf("Não é possível construir mais de um Quartel\nA construção do Quartel já está em andamento. Acesse as informações para obter mais detalhes!!\n");
				system("pause");
				vct.controle = 1;
			}
		}
	}

	//player 2
	if ((*vez == 2) && ((vct.construcao2[0] > 0) && (vct.acao[1][0] > 0)))
	{
		system("cls");
		printf("Não é possível construir mais de uma Muralha\nA construção da Muralha já está em andamento. Acesse as informações para obter mais detalhes!!\n");
		system("pause");
		vct.controle = 1;
	}
	else
	{
		if ((*vez == 2) && ((vct.construcao2[1] > 0) && (vct.acao[1][1] > 0)))
		{
			system("cls");
			printf("Não é possível construir mais de um Templo\nA construção do Templo já está em andamento. Acesse as informações para obter mais detalhes!!\n");
			system("pause");
			vct.controle = 1;
		}
		else
		{
			if ((*vez == 2) && ((vct.construcao2[2] > 0) && (vct.acao[1][2] > 0)))
			{
				system("cls");
				printf("Não é possível construir mais de um Quartel\nA construção do Quartel já está em andamento. Acesse as informações para obter mais detalhes!!\n");
				system("pause");
				vct.controle = 1;
			}
		}
	}

	//player 3
	if ((*vez == 3) && ((vct.construcao3[0] > 0) && (vct.acao[2][0] > 0)))
	{
		system("cls");
		printf("Não é possível construir mais de uma Muralha\nA construção da Muralha já está em andamento. Acesse as informações para obter mais detalhes!!\n");
		system("pause");
		vct.controle = 1;
	}
	else
	{
		if ((*vez == 3) && ((vct.construcao3[1] > 0) && (vct.acao[2][1] > 0)))
		{
			system("cls");
			printf("Não é possível construir mais de um Templo\nA construção do Templo já está em andamento. Acesse as informações para obter mais detalhes!!\n");
			system("pause");
			vct.controle = 1;
		}
		else
		{
			if ((*vez == 3) && ((vct.construcao3[2] > 0) && (vct.acao[2][2] > 0)))
			{
				system("cls");
				printf("Não é possível construir mais de um Quartel\nA construção do Quartel já está em andamento. Acesse as informações para obter mais detalhes!!\n");
				system("pause");
				vct.controle = 1;
			}
		}
	}

	//player 4
	if ((*vez == 4) && ((vct.construcao4[0] > 0) && (vct.acao[3][0] > 0)))
	{
		system("cls");
		printf("Não é possível construir mais de uma Muralha\nA construção da Muralha já está em andamento. Acesse as informações para obter mais detalhes!!\n");
		system("pause");
		vct.controle = 1;
	}
	else
	{
		if ((*vez == 4) && ((vct.construcao4[1] > 0) && (vct.acao[3][1] > 0)))
		{
			system("cls");
			printf("Não é possível construir mais de um Templo\nA construção do Templo já está em andamento. Acesse as informações para obter mais detalhes!!\n");
			system("pause");
			vct.controle = 1;
		}
		else
		{
			if ((*vez == 4) && ((vct.construcao4[2] > 0) && (vct.acao[3][2] > 0)))
			{
				system("cls");
				printf("Não é possível construir mais de um Quartel\nA construção do Quartel já está em andamento. Acesse as informações para obter mais detalhes!!\n");
				system("pause");
				vct.controle = 1;
			}
		}
	}

}

struct construcao
{
	//função para construir casa de humano
	void casa_humano(int* vez, int* madeira, int* pedra, int* xp, int* yp)
	{
		int n = 0, x = 0, y = 0, xc, yc;
		char c = 0;
		*madeira = *madeira - 25;
		*pedra = *pedra - 25;
		do
		{
			system("CLS");
			printf("Selecione a posição no mapa\n");
			printf("Apenas pode construir nos arredores do território do Player, em terreno vazio %d\n", *vez);
			printf("Digite onde será a referência de centro do jogador, pode ser a posição inicial, ou outra em que já tenha construções\n");
			printf("Posição inicial: \n");
			printf("x: %d		y: %d\n", *xp, *yp);
			system("Pause");
			map();
			do
			{
				do
				{
					printf("\nDigite posição em x: ");
					scanf_s("%d", &xc);
				} while ((c = getchar() != '\n' && c != EOF) || ((xc < 0) || (xc > 19)));
				do
				{
					printf("\nDigite posição em y: ");
					scanf_s("%d", &yc);
					system("CLS");
				} while ((c = getchar() != '\n' && c != EOF) || ((yc < 0) || (yc > 24)));
			} while (mapa[xc][yc] != *vez);
			system("CLS");
			printf("Agora, digite, em relação ao centro, uma posição ao arredor dela\n");
			printf("Sua posição escolhida foi: \n");
			printf("x: %d		y: %d\n", xc, yc);
			system("Pause");
			map();
			do
			{
				printf("\nDigite posição em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
			do
			{
				printf("\nDigite posição em y: ");
				scanf_s("%d", &y);
				system("CLS");
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
			if (1 <= mapa[x][y] <= 4)
			{
				if (vivo[mapa[x][y] - 1] == false)
				{
					mapa[x][y] = 86;
				}
			}
		} while ((1 <= mapa[x][y] <= 4) || (recursos.ocupado[x][y] != 0) || (((xc + 1 != x) && (xc - 1 != x) && (xc != x)) || ((yc + 1 != y) && (yc - 1 != y) && (yc != y))));
		constrjg[x][y] = 72; // h de humano
		mapa[x][y] = *vez;
		//será adicionado na varaivel global para manter o valor até terminar os turnos para adicionar a variavel do player
		if (*vez == 1)
		{
			if (vct.qtd_construcoes[0] == 1)
			{
				vct.qtd_construcoes[0] = 2;
				vct.casas1[0][0] = vct.casas1[0][0] + 1;
				vct.casas1[2][0] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[0] == 0)
				{
					vct.qtd_construcoes[0] = 1;
					vct.casas1[0][0] = vct.casas1[0][0] + 1;
					vct.casas1[1][0] = turno + 5;
				}
			}
		}

		if (*vez == 2)
		{
			if (vct.qtd_construcoes[1] == 1)
			{
				vct.qtd_construcoes[1] = 2;
				vct.casas2[0][0] = vct.casas2[0][0] + 1;
				vct.casas2[2][0] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[1] == 0)
				{
					vct.qtd_construcoes[1] = 1;
					vct.casas2[0][0] = vct.casas2[0][0] + 1;
					vct.casas2[1][0] = turno + 5;
				}
			}
		}

		if (*vez == 3)
		{
			if (vct.qtd_construcoes[2] == 1)
			{
				vct.qtd_construcoes[2] = 2;
				vct.casas3[0][0] = vct.casas3[0][0] + 1;
				vct.casas3[2][0] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[2] == 0)
				{
					vct.qtd_construcoes[2] = 1;
					vct.casas3[0][0] = vct.casas3[0][0] + 1;
					vct.casas3[1][0] = turno + 5;
				}
			}
		}

		if (*vez == 4)
		{
			if (vct.qtd_construcoes[3] == 1)
			{
				vct.qtd_construcoes[3] = 2;
				vct.casas4[0][0] = vct.casas4[0][0] + 1;
				vct.casas4[2][0] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[3] == 0)
				{
					vct.qtd_construcoes[3] = 1;
					vct.casas4[0][0] = vct.casas4[0][0] + 1;
					vct.casas4[1][0] = turno + 5;
				}
			}
		}
		*vez = 0;
	}

	//função para construir casa de gigante
	void casa_gigante(int* vez, int* madeira, int* pedra, int* xp, int* yp)
	{
		int x, y, xc, yc;
		char c = 0;
		*madeira = *madeira - 25;
		*pedra = *pedra - 25;

		do
		{
			system("CLS");
			printf("Selecione a posição no mapa\n");
			printf("Apenas pode construir nos arredores do território do Player, em terreno vazio %d\n", *vez);
			printf("Digite onde será a referência de centro do jogador, pode ser a posição inicial, ou outra em que já tenha construções\n");
			printf("Posição inicial: \n");
			printf("x: %d		y: %d\n", *xp, *yp);
			system("Pause");
			map();
			do
			{
				do
				{
					printf("\nDigite posição em x: ");
					scanf_s("%d", &xc);
				} while ((c = getchar() != '\n' && c != EOF) || ((xc < 0) || (xc > 19)));
				do
				{
					printf("\nDigite posição em y: ");
					scanf_s("%d", &yc);
					system("CLS");
				} while ((c = getchar() != '\n' && c != EOF) || ((yc < 0) || (yc > 24)));
			} while (mapa[xc][yc] != *vez);
			system("CLS");
			printf("Agora, digite, em relação ao centro, uma posição ao arredor dela\n");
			printf("Sua posição escolhida foi: \n");
			printf("x: %d		y: %d\n", xc, yc);
			system("Pause");
			map();
			do
			{
				printf("\nDigite posição em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
			do
			{
				printf("\nDigite posição em y: ");
				scanf_s("%d", &y);
				system("CLS");
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
			if (1 <= mapa[x][y] <= 4)
			{
				if (vivo[mapa[x][y] - 1] == false)
				{
					mapa[x][y] = 86;
				}
			}
		} while ((1 <= mapa[x][y] <= 4) || (recursos.ocupado[x][y] != 0) || ((xc + 1 != x && xc - 1 != x && xc != x) && (yc + 1 != y && yc - 1 != y && yc != y)));

		constrjg[x][y] = 71; // G de GIGANTE
		mapa[x][y] = *vez;

		if (*vez == 1)
		{
			if (vct.qtd_construcoes[0] == 1)
			{
				vct.qtd_construcoes[0] = 2;
				vct.casas1[0][1] = vct.casas1[0][1] + 1;
				vct.casas1[2][1] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[0] == 0)
				{
					vct.qtd_construcoes[0] = 1;
					vct.casas1[0][1] = vct.casas1[0][1] + 1;
					vct.casas1[1][1] = turno + 5;
				}
			}
		}

		if (*vez == 2)
		{
			if (vct.qtd_construcoes[1] == 1)
			{
				vct.qtd_construcoes[1] = 2;
				vct.casas2[0][1] = vct.casas2[0][1] + 1;
				vct.casas2[2][1] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[1] == 0)
				{
					vct.qtd_construcoes[1] = 1;
					vct.casas2[0][1] = vct.casas2[0][1] + 1;
					vct.casas2[1][1] = turno + 5;
				}
			}
		}

		if (*vez == 3)
		{
			if (vct.qtd_construcoes[2] == 1)
			{
				vct.qtd_construcoes[2] = 2;
				vct.casas3[0][1] = vct.casas3[0][1] + 1;
				vct.casas3[2][1] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[2] == 0)
				{
					vct.qtd_construcoes[2] = 1;
					vct.casas3[0][1] = vct.casas3[0][1] + 1;
					vct.casas3[1][1] = turno + 5;
				}
			}
		}

		if (*vez == 4)
		{
			if (vct.qtd_construcoes[3] == 1)
			{
				vct.qtd_construcoes[3] = 2;
				vct.casas4[0][1] = vct.casas4[0][1] + 1;
				vct.casas4[2][1] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[3] == 0)
				{
					vct.qtd_construcoes[3] = 1;
					vct.casas4[0][1] = vct.casas4[0][1] + 1;
					vct.casas4[1][1] = turno + 5;
				}
			}
		}
	}

	//função para construir casa de goblin
	void casa_goblin(int* vez, int* madeira, int* pedra, int* xp, int* yp)
	{
		int x, y, i, xc, yc;
		char c = 0;
		*madeira = *madeira - 25;
		*pedra = *pedra - 25;
		do
		{
			system("CLS");
			printf("Selecione a posição no mapa\n");
			printf("Apenas pode construir nos arredores do território do Player, em terreno vazio %d\n", *vez);
			printf("Digite onde será a referência de centro do jogador, pode ser a posição inicial, ou outra em que já tenha construções\n");
			printf("Posição inicial: \n");
			printf("x: %d		y: %d\n", *xp, *yp);
			system("Pause");
			map();
			do
			{
				do
				{
					printf("\nDigite posição em x: ");
					scanf_s("%d", &xc);
				} while ((c = getchar() != '\n' && c != EOF) || ((xc < 0) || (xc > 19)));
				do
				{
					printf("\nDigite posição em y: ");
					scanf_s("%d", &yc);
					system("CLS");
				} while ((c = getchar() != '\n' && c != EOF) || ((yc < 0) || (yc > 24)));
			} while (mapa[xc][yc] != *vez);
			system("CLS");
			printf("Agora, digite, em relação ao centro, uma posição ao arredor dela\n");
			printf("Sua posição escolhida foi: \n");
			printf("x: %d		y: %d\n", xc, yc);
			system("Pause");
			map();
			do
			{
				printf("\nDigite posição em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
			do
			{
				printf("\nDigite posição em y: ");
				scanf_s("%d", &y);
				system("CLS");
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
			if (1 <= mapa[x][y] <= 4)
			{
				if (vivo[mapa[x][y] - 1] == false)
				{
					mapa[x][y] = 86;
				}
			}
		} while ((1 <= mapa[x][y] <= 4) || (recursos.ocupado[x][y] != 0) || ((xc + 1 != x && xc - 1 != x && xc != x) && (yc + 1 != y && yc - 1 != y && yc != y)));
		constrjg[x][y] = 103; // g de goblin
		mapa[x][y] = *vez;


		if (*vez == 1)
		{
			if (vct.qtd_construcoes[0] == 1)
			{
				vct.qtd_construcoes[0] = 2;
				vct.casas1[0][2] = vct.casas1[0][2] + 1;
				vct.casas1[2][2] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[0] == 0)
				{
					vct.qtd_construcoes[0] = 1;
					vct.casas1[0][2] = vct.casas1[0][2] + 1;
					vct.casas1[1][2] = turno + 5;
				}
			}
		}

		if (*vez == 2)
		{
			if (vct.qtd_construcoes[1] == 1)
			{
				vct.qtd_construcoes[1] = 2;
				vct.casas2[0][2] = vct.casas2[0][2] + 1;
				vct.casas2[2][2] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[1] == 0)
				{
					vct.qtd_construcoes[1] = 1;
					vct.casas2[0][2] = vct.casas2[0][2] + 1;
					vct.casas2[1][2] = turno + 5;
				}
			}
		}

		if (*vez == 3)
		{
			if (vct.qtd_construcoes[2] == 1)
			{
				vct.qtd_construcoes[2] = 2;
				vct.casas3[0][2] = vct.casas3[0][2] + 1;
				vct.casas3[2][2] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[2] == 0)
				{
					vct.qtd_construcoes[2] = 1;
					vct.casas3[0][2] = vct.casas3[0][2] + 1;
					vct.casas3[1][2] = turno + 5;
				}
			}
		}

		if (*vez == 4)
		{
			if (vct.qtd_construcoes[3] == 1)
			{
				vct.qtd_construcoes[3] = 2;
				vct.casas4[0][2] = vct.casas4[0][2] + 1;
				vct.casas4[2][2] = turno + 5;
			}
			else
			{
				if (vct.qtd_construcoes[3] == 0)
				{
					vct.qtd_construcoes[3] = 1;
					vct.casas4[0][2] = vct.casas4[0][2] + 1;
					vct.casas4[1][2] = turno + 5;
				}
			}
		}

	}

	//função para o menu de construção de casas
	void construir_casa(int* madeira, int* pedra, int* vez, int* xp, int* yp)
	{
		int n = 0;
		system("cls");
		printf("Agora irá abrir o mapa para que você escolha onde irá construir a casa!!\n");
		system("pause");
		map();
		system("cls");
		printf("Abaixo está os tipos de opções de casas diferenciando seus habitantes. Qual deseja construir?\n");
		printf("F1 - Casa para Humanos\n");
		printf("F2 - Casa para Gigantes\n");
		printf("F3 - Casa para Goblins\n");
		printf("ESC - Voltar para o Menu\n");
		do
		{
			n = _getch();
			if (n == 0)
			{
				n = _getch();
			}
			else
			{
				system("cls");
				printf("Abaixo está os tipos de opções de casas, diferenciando seus habitantes. Qual deseja construir?\n");
				printf("F1 - Casa para Humanos\n");
				printf("F2 - Casa para Gigantes\n");
				printf("F3 - Casa para Goblins\n");
				printf("ESC - Voltar para o Menu\n");
			}
		} while (((n < 59) || (n > 61)) && !(n == 27));

		switch (n)
		{
		case 59:
			casa_humano(vez, madeira, pedra, xp, yp);
			*vez = 0;
			break;

		case 60:
			casa_gigante(vez, madeira, pedra, xp, yp);
			*vez = 0;
			break;

		case 61:
			casa_goblin(vez, madeira, pedra, xp, yp);
			*vez = 0;
			break;

		default:
			break;
		}

	}

	//função para construir quartel
	void construir_quartel(int* madeira, int* pedra, int* vez, int* xp, int* yp)
	{
		int x, y, i = 0, xc, yc;
		char c = 0;
		*madeira = *madeira - 60;
		*pedra = *pedra - 50;
		do
		{
			system("CLS");
			printf("Selecione a posição no mapa\n");
			printf("Apenas pode construir nos arredores do território do Player, em terreno vazio %d\n", *vez);
			printf("Digite onde será a referência de centro do jogador, pode ser a posição inicial, ou outra em que já tenha construções\n");
			printf("Posição inicial: \n");
			printf("x: %d		y: %d\n", *xp, *yp);
			system("Pause");
			map();
			do
			{
				do
				{
					printf("\nDigite posição em x: ");
					scanf_s("%d", &xc);
				} while ((c = getchar() != '\n' && c != EOF) || ((xc < 0) || (xc > 19)));
				do
				{
					printf("\nDigite posição em y: ");
					scanf_s("%d", &yc);
					system("CLS");
				} while ((c = getchar() != '\n' && c != EOF) || ((yc < 0) || (yc > 24)));
			} while (mapa[xc][yc] != *vez);
			system("CLS");
			printf("Agora, digite, em relação ao centro, uma posição ao arredor dela\n");
			printf("Sua posição escolhida foi: \n");
			printf("x: %d		y: %d\n", xc, yc);
			system("Pause");
			map();

			do
			{
				printf("\nDigite posição em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
			do
			{
				printf("\nDigite posição em y: ");
				scanf_s("%d", &y);
				system("CLS");
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
			if (1 <= mapa[x][y] <= 4)
			{
				if (vivo[mapa[x][y] - 1] == false)
				{
					mapa[x][y] = 86;
				}
			}
		} while ((1 <= mapa[x][y] <= 4) || (recursos.ocupado[x][y] != 0) || ((xc + 1 != x && xc - 1 != x && xc != x) && (yc + 1 != y && yc - 1 != y && yc != y)));

		constrjg[x][y] = 81; //Q DE QUARTEL
		mapa[x][y] = *vez;
		if (*vez == 1)
		{
			vct.construcao1[2] = turno + 15;
			vct.acao[0][2] = 1;
		}
		else
		{
			if (*vez == 2)
			{
				vct.construcao2[2] = turno + 15;
				vct.acao[1][2] = 1;
			}
			else
			{
				if (*vez == 3)
				{
					vct.construcao3[2] = turno + 15;
					vct.acao[2][2] = 1;
				}
				else
				{
					vct.construcao4[2] = turno + 15;
					vct.acao[3][2] = 1;
				}
			}

		}
		*vez = 0;
	}

	//função para construir templo
	void construir_templo(int* madeira, int* pedra, int* vez, int* xp, int* yp)
	{
		int x, y, i = 0, xc, yc;
		char c = 0;
		system("cls");
		printf("Construindo Templo");
		system("pause");
		*madeira = *madeira - 50;
		*pedra = *pedra - 50;
		do
		{
			system("CLS");
			printf("Selecione a posição no mapa\n");
			printf("Apenas pode construir nos arredores do território do Player, em terreno vazio %d\n", *vez);
			printf("Digite onde será a referência de centro do jogador, pode ser a posição inicial, ou outra em que já tenha construções\n");
			printf("Posição inicial: \n");
			printf("x: %d		y: %d\n", *xp, *yp);
			system("Pause");
			map();
			do
			{
				do
				{
					printf("\nDigite posição em x: ");
					scanf_s("%d", &xc);
				} while ((c = getchar() != '\n' && c != EOF) || ((xc < 0) || (xc > 19)));
				do
				{
					printf("\nDigite posição em y: ");
					scanf_s("%d", &yc);
					system("CLS");
				} while ((c = getchar() != '\n' && c != EOF) || ((yc < 0) || (yc > 24)));
			} while (mapa[xc][yc] != *vez);
			system("CLS");
			printf("Agora, digite, em relação ao centro, uma posição ao arredor dela\n");
			printf("Sua posição escolhida foi: \n");
			printf("x: %d		y: %d\n", xc, yc);
			system("Pause");
			map();

			do
			{
				printf("\nDigite posição em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
			do
			{
				printf("\nDigite posição em y: ");
				scanf_s("%d", &y);
				system("CLS");
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
			if (1 <= mapa[x][y] <= 4)
			{
				if (vivo[mapa[x][y] - 1] == false)
				{
					mapa[x][y] = 86;
				}
			}
		} while ((1 <= mapa[x][y] <= 4) || (recursos.ocupado[x][y] != 0) || ((xc + 1 != x && xc - 1 != x && xc != x) && (yc + 1 != y && yc - 1 != y && yc != y)));


		constrjg[x][y] = 84; // T DE TEMPLO
		mapa[x][y] = *vez;
		if (*vez == 1)
		{
			vct.construcao1[1] = turno + 15;
			vct.acao[0][1] = 1;
		}
		else
		{
			if (*vez == 2)
			{
				vct.construcao2[1] = turno + 15;
				vct.acao[1][1] = 1;
			}
			else
			{
				if (*vez == 3)
				{
					vct.construcao3[1] = turno + 15;
					vct.acao[2][1] = 1;
				}
				else
				{
					vct.construcao4[1] = turno + 15;
					vct.acao[3][1] = 1;
				}
			}

		}
		*vez = 0;

	}

	//função para construir muralha
	void construir_muralha(int* madeira, int* pedra, int* vez)
	{
		*madeira = *madeira - 120;
		*pedra = *pedra - 120;

		if (*vez == 1)
		{
			vct.construcao1[0] = turno + 35;
			vct.acao[0][0] = 1;

		}
		else
		{
			if (*vez == 2)
			{
				vct.construcao2[0] = turno + 35;
				vct.acao[1][0] = 1;
			}
			else
			{
				if (*vez == 3)
				{
					vct.construcao3[0] = turno + 35;
					vct.acao[2][0] = 1;
				}
				else
				{
					vct.construcao4[0] = turno + 35;
					vct.acao[3][0] = 1;
				}
			}

		}
		*vez = 0;

	}

	//função do menu de construções
	void construcoes(int* madeira, int* pedra, int* alimento, int* vez, bool* quartel, bool* templo, bool* muralha, int* xp, int* yp)
	{
		int n = 0;



		system("cls");
		printf("O que deseja construir? (Limite de 2 construções simultâneas, porém uma a cada turno!!)\n\n");
		printf("F1 - Casa				         Turnos - 5   /  Madeiras - 25  /  Pedras - 25  /  Habitantes - 10\n");
		printf("F2 - Quartel (Necessário para atacar / Único)    Turnos - 15  /  Madeiras - 60  /  Pedras - 50  \n");
		printf("F3 - Templo  (única)                             Turnos - 15  /  Madeiras - 50  /  Pedras - 50  / Ataq/Def de Soldados - +10%% \n");
		printf("F4 - Muralha (única)                             Turnos - 35  /  Madeiras - 120 /  Pedras - 120 /  Def - +25%% \n");
		printf("ESC - Voltar ao Menu\n");
		do
		{
			n = _getch();
			if (n == 0)
			{
				n = _getch();
			}
			else
			{
				system("cls");
				printf("O que deseja construir?(Limite de 2 construções simultâneas.)\n\n");
				printf("F1 - Casa				         Turnos - 5   /  Madeiras - 25  /  Pedras - 25  /  Habitantes - 10\n");
				printf("F2 - Quartel (Necessário para atacar / Único)    Turnos - 15  /  Madeiras - 60  /  Pedras - 50  \n");
				printf("F3 - Templo  (único)                             Turnos - 15  /  Madeiras - 50  /  Pedras - 50  / Ataq/Def de Soldados - +10%% \n");
				printf("F4 - Muralha (único)                             Turnos - 35  /  Madeiras - 120 /  Pedras - 120 /  Def - +25%% \n");
				printf("ESC - Voltar ao Menu\n");
			}
		} while (((n < 59) || (n > 62)) && !(n == 27));

		switch (n)
		{
			//construir casa
		case 59:
			if ((*madeira < 25) && (*pedra < 25))
			{
				system("cls");
				printf("Você não possuí recursos suficientes!!\nPor Favor volte mais tarde!!\n\n");
				system("pause");
			}
			else
			{
				construir_casa(madeira, pedra, vez, xp, yp);
			}
			break;

			//construir quartel
		case 60:
			if ((*madeira < 60) && (*pedra < 50))
			{
				system("cls");
				printf("Você não possuí recursos suficientes!!\nPor Favor volte mais tarde!!\n\n");
				system("pause");
			}
			else
			{
				if (*quartel == true)
				{
					system("cls");
					printf("Você ja possúi quartel\n");
					system("pause");
				}
				else
				{
					vct.controle = 0;
					n_constroi(vez, &n);
					if (vct.controle == 0)
					{
						construir_quartel(madeira, pedra, vez, xp, yp);
					}
				}
			}
			break;

			//construir templo
		case 61:
			if ((*madeira < 50) && (*pedra < 50))
			{
				system("cls");
				printf("Você não possuí recursos suficientes!!\nPor Favor volte mais tarde!!\n\n");
				system("pause");
			}
			else
			{
				vct.controle = 0;
				n_constroi(vez, &n);

				if (vct.controle == 0)
				{
					construir_templo(madeira, pedra, vez, xp, yp);
				}
			}
			break;

			//construir muralha
		case 62:
			if ((*madeira < 120) && (*pedra < 120))
			{
				system("cls");
				printf("Você não possuí recursos suficientes!!\nPor Favor volte mais tarde!!\n\n");
				system("pause");
			}
			else
			{
				vct.controle = 0;
				n_constroi(vez, &n);
				if (vct.controle == 0)
				{
					construir_muralha(madeira, pedra, vez);
				}
			}
			break;

			//volta pro menu
		default:
			break;
		}
	}

}; struct construcao ct;

void map()
{
	int x, y;
	system("CLS");
	for (x = 0; x < 20; x++)
	{
		printf("    %s[%02d]\n", C_GREEN, x);
	}
	printf("\t");
	for (y = 0; y < 25; y++)
	{
		printf("%s[%02d]", C_GREEN, y);
	}
	printf("\n");
	gotoxy(3, 0);
	for (x = 0; x < 20; x++)
	{
		printf("\t");
		for (y = 0; y < 25; y++)
		{
			switch (mapa[x][y])
			{
			case 1:
				if (vivo[0] == false)
				{
					printf(" %s[%c]", C_BLACK, mapa[x][y]);
				}
				else
				{
					if (constrjg[x][y] != 0)
					{
						printf(" %s[%c]", C_BLUE, constrjg[x][y]);
					}
					else
					{
						printf(" %s[%d]", C_BLUE, mapa[x][y]);
					}
				}
				break;
			case 2:
				if (vivo[1] == false)
				{
					printf(" %s[%c]", C_BLACK, mapa[x][y]);
				}
				else
				{
					if (constrjg[x][y] != 0)
					{
						printf(" %s[%c]", C_MAGENTA, constrjg[x][y]);
					}
					else
					{
						printf(" %s[%d]", C_MAGENTA, mapa[x][y]);
					}
				}
				break;
			case 3:
				if (vivo[2] == false)
				{
					printf(" %s[%c]", C_BLACK, mapa[x][y]);
				}
				else
				{
					if (constrjg[x][y] != 0)
					{
						printf(" %s[%c]", C_YELLOW, constrjg[x][y]);
					}
					else
					{
						printf(" %s[%d]", C_YELLOW, mapa[x][y]);
					}
				}
				break;
			case 4:
				if (vivo[0] == false)
				{
					printf(" %s[%c]", C_BLACK, mapa[x][y]);
				}
				else
				{
					if (constrjg[x][y] != 0)
					{
						printf(" %s[%c]", C_RED, constrjg[x][y]);
					}
					else
					{
						printf(" %s[%d]", C_RED, mapa[x][y]);
					}
				}
				break;
			case 86:
				if (recursos.ocupado[x][y] == 0)
				{
					printf(" %s[%c]", C_BLACK, mapa[x][y]);
				}
				else
				{
					printf(" %s[%d]", C_CYAN, recursos.ocupado[x][y]);
				}
				break;
			default:
				if (recursos.ocupado[x][y] == 0)
				{
					printf(" %s[%c]", C_GRAY, mapa[x][y]);
				}
				else
				{
					printf(" %s[%d]", C_CYAN, recursos.ocupado[x][y]);
				}
				break;
			}
		}
		printf("\n");
	}
	printf("%s\n", NONE);

	system("Pause");
	system("CLS");
}

void coleta(int* xp, int* yp, int* coletap, int* tempop, int* coletorp, int* hab, int* vez, int* ocupadox, int* ocupadoy)
{
	int n = 0, x, y;
	int calc = 0;
	int nc = 0;
	char c = 0;
	system("CLS");
	printf("Abrindo mapa para exibição...\n");
	system("Pause");
	map();
	gotoxy(19, 5);
	printf("=================================================================================");
	gotoxy(19, 6);
	printf("|DIGITE ESC PARA VOLTAR AO MENU OU PRESSIONE QUALQUER OUTRA TECLA PARA CONTINUAR|");
	gotoxy(19, 7);
	printf("=================================================================================");
	n = _getch();
	system("CLS");
	if (n == 27)
	{
		return;
	}
	do
	{
		do
		{
			printf("\nDigite posição em x: ");
			scanf_s("%d", &x);
		} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19)));
		do
		{
			printf("\nDigite posição em y: ");
			scanf_s("%d", &y);
			system("CLS");
		} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (y > 24)));
	} while ((mapa[x][y] != 67 && mapa[x][y] != *vez) || (recursos.ocupado[x][y] != 0) || (x == *xp && y == *yp));
	if (mapa[x][y] == *vez)
	{
		printf("-------VOCÊ SELECIONOU UMA ÁREA DE COLETA QUE É TERRITÓRIO SEU-------\n");
		printf("OS RECURSOS SEMPRE SERÃO GERADOS DE FORMA ALEATÓRIA A CADA COLETA NO SEU TERRITÓRIO, POIS SÃO INFINITOS, BASTA TER PESSOAS PARA COLETAR\n");
		recursos.alimento[x][y] = 400 + (rand() % 2000);
		recursos.madeira[x][y] = 400 + (rand() % 2000);
		recursos.pedra[x][y] = 400 + (rand() % 2000);
	}
	printf("Quantidade de recursos na área selecionada: \n\n ");
	printf("Alimento: %d\n", recursos.alimento[x][y]);
	printf("Madeira: %d\n", recursos.madeira[x][y]);
	printf("Pedra: %d\n", recursos.pedra[x][y]);
	printf("Humano coleta 3\t Gigante coleta 6\t Goblin coleta 2\n\n");
	printf("Humano não interfere no tempo\t Gigante é 10 por cento mais lento\t Goblin é 10 por cento mais rápido\n\n");
	printf("A raça em maior quantidade predomina o resultado do tempo de coleta, caso sejam iguais, não há atribuição nenhuma.\n");
	printf("Digite a quantidade de habitantes que você deseja designar\n");
	printf("VOCÊ SÓ PODE MANDAR COLETAR NO MÁXIMO 10 POR CENTO DA POPULAÇÃO EM CADA COLETA.\n");
	printf("Humanos: %d - Gigantes: %d - Goblins: %d\n", hab[0], hab[1], hab[2]);
	if ((coletorp[0] == 0) && (coletorp[1] == 0) && (coletorp[2] == 0))
	{

		do
		{
			do
			{
				printf("\n---> Quantidade de humanos: ");
				scanf_s("%d", &coletorp[0]);
			} while ((c = getchar() != '\n' && c != EOF) || (coletorp[0] > hab[0]));
			do
			{
				printf("\n---> Quantidade de Gigantes: ");
				scanf_s("%d", &coletorp[1]);
			} while ((c = getchar() != '\n' && c != EOF) || (coletorp[1] > hab[1]));
			do
			{
				printf("\n---> Quantidade de Goblins: ");
				scanf_s("%d", &coletorp[2]);
			} while ((c = getchar() != '\n' && c != EOF) || (coletorp[2] > hab[2]));
			system("CLS");
		} while (((coletorp[0] + coletorp[1] + coletorp[2]) > ((hab[0] + hab[1] + hab[2]) * 0.1)) || ((coletorp[0] == 0 && coletorp[1] == 0 && coletorp[2] == 0)));
		system("CLS");
		calc = coletorp[0] * 3 + coletorp[1] * 6 + coletorp[2] * 2;
		hab[0] = hab[0] - coletorp[0];
		hab[1] = hab[1] - coletorp[1];
		hab[2] = hab[2] - coletorp[2];
		ocupadox[0] = x;
		ocupadoy[0] = y;
		tempop[0] = int(sqrt((pow((x - *xp), 2)) + (pow((y - *yp), 2)))); // distância de um ponto no mapa até outro
		printf("\nTempo calculado para coleta sem atributos dos personagens: %d\n\n\n", tempop[0]);
		nc = 0;
		system("Pause");
	}
	else
	{
		if ((coletorp[3] == 0) && (coletorp[4] == 0) && (coletorp[5] == 0))
		{
			do
			{
				do
				{
					printf("\n---> Quantidade de humanos: ");
					scanf_s("%d", &coletorp[3]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[3] > hab[0]));
				do
				{
					printf("\n---> Quantidade de Gigantes: ");
					scanf_s("%d", &coletorp[4]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[4] > hab[1]));
				do
				{
					printf("\n---> Quantidade de Goblins: ");
					scanf_s("%d", &coletorp[5]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[5] > hab[2]));
				system("CLS");
			} while (((coletorp[3] + coletorp[4] + coletorp[5]) > ((hab[0] + hab[1] + hab[2]) * 0.1)) || ((coletorp[3] == 0 && coletorp[4] == 0 && coletorp[5] == 0)));
			system("CLS");
			calc = coletorp[3] * 3 + coletorp[4] * 6 + coletorp[5] * 2;
			hab[0] = hab[0] - coletorp[3];
			hab[1] = hab[1] - coletorp[4];
			hab[2] = hab[2] - coletorp[5];
			ocupadox[1] = x;
			ocupadoy[1] = y;
			tempop[1] = int(sqrt((pow((x - *xp), 2)) + (pow((y - *yp), 2))));
			printf("\nTempo calculado para coleta sem atributos dos personagens: %d\n\n\n", tempop[1]);
			nc = 1;
			system("Pause");
		}
		else
		{
			do
			{
				do
				{
					printf("\n---> Quantidade de humanos: ");
					scanf_s("%d", &coletorp[6]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[6] > hab[0]));
				do
				{
					printf("\n---> Quantidade de Gigantes: ");
					scanf_s("%d", &coletorp[7]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[7] > hab[1]));
				do
				{
					printf("\n---> Quantidade de Goblins: ");
					scanf_s("%d", &coletorp[8]);
				} while ((c = getchar() != '\n' && c != EOF) || (coletorp[8] > hab[2]) || ((coletorp[6] == 0 && coletorp[7] == 0 && coletorp[8] == 0)));
				system("CLS");
			} while (((coletorp[6] + coletorp[7] + coletorp[8]) > ((hab[0] + hab[1] + hab[2]) * 0.1)) || ((coletorp[6] == 0 && coletorp[7] == 0 && coletorp[8] == 0)));
			system("CLS");
			calc = coletorp[6] * 3 + coletorp[7] * 6 + coletorp[8] * 2;
			hab[0] = hab[0] - coletorp[6];
			hab[1] = hab[1] - coletorp[7];
			hab[2] = hab[2] - coletorp[8];
			ocupadox[2] = x;
			ocupadoy[2] = y;
			tempop[2] = int(sqrt((pow((x - *xp), 2)) + (pow((y - *yp), 2))));
			printf("\nTempo calculado para coleta sem atributos dos personagens: %d\n\n\n", tempop[2]);
			n = 2;
			system("Pause");

		}
	}
	recursos.ocupado[x][y] = *vez;
	if (nc == 0)
	{
		if ((coletorp[0] > coletorp[1]) && (coletorp[0] > coletorp[2]))
		{
			if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
			{
				coletap[0] = recursos.alimento[x][y];
				recursos.alimento[x][y] = 0;
			}
			else
			{
				coletap[0] = calc;
				recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
			}
			if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
			{
				coletap[1] = recursos.madeira[x][y];
				recursos.madeira[x][y] = 0;
			}
			else
			{
				coletap[1] = calc;
				recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
			}
			if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
			{
				coletap[2] = recursos.pedra[x][y];
				recursos.pedra[x][y] = 0;
			}
			else
			{
				coletap[2] = calc;
				recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
			}
		}
		else
		{
			if ((coletorp[1] > coletorp[0]) && (coletorp[1] > coletorp[2]))
			{
				tempop[0] = tempop[0] + int((tempop[0] * 0.1));
				if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
				{
					coletap[0] = recursos.alimento[x][y];
					recursos.alimento[x][y] = 0;
				}
				else
				{
					coletap[0] = calc;
					recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
				}
				if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
				{
					coletap[1] = recursos.madeira[x][y];
					recursos.madeira[x][y] = 0;
				}
				else
				{
					coletap[1] = calc;
					recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
				}
				if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
				{
					coletap[2] = recursos.pedra[x][y];
					recursos.pedra[x][y] = 0;
				}
				else
				{
					coletap[2] = calc;
					recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
				}
			}
			else
			{
				if (coletorp[2] > coletorp[1] && coletorp[2] > coletorp[0])
				{
					tempop[0] = tempop[0] - int((tempop[0] * 0.1));
					if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
					{
						coletap[0] = recursos.alimento[x][y];
						recursos.alimento[x][y] = 0;
					}
					else
					{
						coletap[0] = calc;
						recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
					}
					if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
					{
						coletap[1] = recursos.madeira[x][y];
						recursos.madeira[x][y] = 0;
					}
					else
					{
						coletap[1] = calc;
						recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
					}
					if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
					{
						coletap[2] = recursos.pedra[x][y];
						recursos.pedra[x][y] = 0;
					}
					else
					{
						coletap[2] = calc;
						recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
					}
				}
				else
				{
					if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
					{
						coletap[0] = recursos.alimento[x][y];
						recursos.alimento[x][y] = 0;
					}
					else
					{
						coletap[0] = calc;
						recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
					}
					if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
					{
						coletap[1] = recursos.madeira[x][y];
						recursos.madeira[x][y] = 0;
					}
					else
					{
						coletap[1] = calc;
						recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
					}
					if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
					{
						coletap[2] = recursos.pedra[x][y];
						recursos.pedra[x][y] = 0;
					}
					else
					{
						coletap[2] = calc;
						recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
					}
				}
			}
		}
		printf("\nTempo após atributos contabilizados: %d", tempop[0]);
	}
	else
	{
		if (nc == 1)
		{
			if ((coletorp[3] > coletorp[4]) && (coletorp[3] > coletorp[5]))
			{
				if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
				{
					coletap[3] = recursos.alimento[x][y];
					recursos.alimento[x][y] = 0;
				}
				else
				{
					coletap[3] = calc;
					recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
				}
				if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
				{
					coletap[4] = recursos.madeira[x][y];
					recursos.madeira[x][y] = 0;
				}
				else
				{
					coletap[4] = calc;
					recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
				}
				if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
				{
					coletap[5] = recursos.pedra[x][y];
					recursos.pedra[x][y] = 0;
				}
				else
				{
					coletap[5] = calc;
					recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
				}
			}
			else
			{
				if ((coletorp[4] > coletorp[3]) && (coletorp[4] > coletorp[5]))
				{
					tempop[1] = tempop[1] + int((tempop[1] * 0.1));
					if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
					{
						coletap[3] = recursos.alimento[x][y];
						recursos.alimento[x][y] = 0;
					}
					else
					{
						coletap[3] = calc;
						recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
					}
					if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
					{
						coletap[4] = recursos.madeira[x][y];
						recursos.madeira[x][y] = 0;
					}
					else
					{
						coletap[4] = calc;
						recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
					}
					if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
					{
						coletap[5] = recursos.pedra[x][y];
						recursos.pedra[x][y] = 0;
					}
					else
					{
						coletap[5] = calc;
						recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
					}
				}
				else
				{
					if (coletorp[5] > coletorp[3] && coletorp[5] > coletorp[4])
					{
						tempop[1] = tempop[1] - ((tempop[1] * 0.1));
						if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
						{
							coletap[3] = recursos.alimento[x][y];
							recursos.alimento[x][y] = 0;
						}
						else
						{
							coletap[3] = calc;
							recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
						}
						if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
						{
							coletap[4] = recursos.madeira[x][y];
							recursos.madeira[x][y] = 0;
						}
						else
						{
							coletap[4] = calc;
							recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
						}
						if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
						{
							coletap[5] = recursos.pedra[x][y];
							recursos.pedra[x][y] = 0;
						}
						else
						{
							coletap[5] = calc;
							recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
						}
					}
					else
					{
						if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
						{
							coletap[3] = recursos.alimento[x][y];
							recursos.alimento[x][y] = 0;
						}
						else
						{
							coletap[3] = calc;
							recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
						}
						if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
						{
							coletap[4] = recursos.madeira[x][y];
							recursos.madeira[x][y] = 0;
						}
						else
						{
							coletap[4] = calc;
							recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
						}
						if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
						{
							coletap[5] = recursos.pedra[x][y];
							recursos.pedra[x][y] = 0;
						}
						else
						{
							coletap[5] = calc;
							recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
						}
					}
				}
			}
			printf("\nTempo após atributos contabilizados: %d\n", tempop[1]);
		}
		else
		{
			if ((coletorp[6] > coletorp[7]) && (coletorp[6] > coletorp[8]))
			{
				if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
				{
					coletap[6] = recursos.alimento[x][y];
					recursos.alimento[x][y] = 0;
				}
				else
				{
					coletap[6] = calc;
					recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
				}
				if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
				{
					coletap[7] = recursos.madeira[x][y];
					recursos.madeira[x][y] = 0;
				}
				else
				{
					coletap[7] = calc;
					recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
				}
				if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
				{
					coletap[8] = recursos.pedra[x][y];
					recursos.pedra[x][y] = 0;
				}
				else
				{
					coletap[8] = calc;
					recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
				}
			}
			else
			{
				if ((coletorp[7] > coletorp[6]) && (coletorp[7] > coletorp[8]))
				{
					tempop[2] = tempop[2] + int((tempop[2] * 0.1));
					if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
					{
						coletap[6] = recursos.alimento[x][y];
						recursos.alimento[x][y] = 0;
					}
					else
					{
						coletap[6] = calc;
						recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
					}
					if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
					{
						coletap[7] = recursos.madeira[x][y];
						recursos.madeira[x][y] = 0;
					}
					else
					{
						coletap[7] = calc;
						recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
					}
					if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
					{
						coletap[8] = recursos.pedra[x][y];
						recursos.pedra[x][y] = 0;
					}
					else
					{
						coletap[8] = calc;
						recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
					}
				}
				else
				{
					if (coletorp[8] > coletorp[6] && coletorp[8] > coletorp[7])
					{
						tempop[2] = tempop[2] - int((tempop[2] * 0.1));
						if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
						{
							coletap[6] = recursos.alimento[x][y];
							recursos.alimento[x][y] = 0;
						}
						else
						{
							coletap[6] = calc;
							recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
						}
						if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
						{
							coletap[7] = recursos.madeira[x][y];
							recursos.madeira[x][y] = 0;
						}
						else
						{
							coletap[7] = calc;
							recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
						}
						if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
						{
							coletap[8] = recursos.pedra[x][y];
							recursos.pedra[x][y] = 0;
						}
						else
						{
							coletap[8] = calc;
							recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
						}
					}
					else
					{
						if ((recursos.alimento[x][y] - calc == 0) || (recursos.alimento[x][y] - calc < 0))
						{
							coletap[6] = recursos.alimento[x][y];
							recursos.alimento[x][y] = 0;
						}
						else
						{
							coletap[6] = calc;
							recursos.alimento[x][y] = recursos.alimento[x][y] - calc;
						}
						if ((recursos.madeira[x][y] - calc == 0) || (recursos.madeira[x][y] - calc < 0))
						{
							coletap[7] = recursos.madeira[x][y];
							recursos.madeira[x][y] = 0;
						}
						else
						{
							coletap[7] = calc;
							recursos.madeira[x][y] = recursos.madeira[x][y] - calc;
						}
						if ((recursos.pedra[x][y] - calc == 0) || (recursos.pedra[x][y] - calc < 0))
						{
							coletap[8] = recursos.pedra[x][y];
							recursos.pedra[x][y] = 0;
						}
						else
						{
							coletap[8] = calc;
							recursos.pedra[x][y] = recursos.pedra[x][y] - calc;
						}
					}
				}
			}
			printf("\nTempo após atributos contabilizados: %d", tempop[2]);
		}
	}
	*vez = 0;
	printf("\n\n");
	system("Pause");
	return;
}

void posicao_jogadores()
{
	int x, y, jg = 1;
	bool v = 0;
	char c = 0;
	do
	{
		do
		{
			do
			{
				system("CLS");
				gotoxy(20, 0);
				printf("%sJOGADOR %d\n\n", C_GREEN, jg);
				printf("-- COORDENADAS DE X VÃO DE 0 A 19 --\t-- COORDENADAS DE Y VÃO DE 0 A 24 --\n\n");
				printf("\nEscolha coordenada em x: ");
				scanf_s("%d", &x);
			} while ((c = getchar() != '\n' && c != EOF) || ((x < 0) || (x > 19))); // laços para obrigar o usuários a digitar dentro do esperado
			do
			{
				gotoxy(25, 8);
				printf("  ");// aqui apenas a efeito de estética, para se o usuario digitar errado, não apagar a tela inteira
				gotoxy(0, 8);
				printf("Escolha coordenada em y: ");
				scanf_s("%d", &y);
			} while ((c = getchar() != '\n' && c != EOF) || ((y < 0) || (x > 24)));
			switch (jg)
			{
			case 1:
				mapa[x][y] = jg;
				v = 1;
				break;
			case 2:
				if (mapa[x][y] == 1)
				{
					v = 0;
				}
				else
				{
					mapa[x][y] = jg;
					v = 1;
				}
				break;
			case 3:
				if ((mapa[x][y] == 1) || (mapa[x][y] == 2))
				{
					v = 0;
				}
				else
				{
					mapa[x][y] = jg;
					v = 1;
				}
				break;
			default:
				if (((mapa[x][y] == 1) || (mapa[x][y] == 2) || (mapa[x][y] == 3)))
				{
					v = 0;
				}
				else
				{
					mapa[x][y] = jg;
					v = 1;
				}

			}

		} while (v == 0); // já este laço serve para o jogador 2 não colocar a mesma posição que o jogador 1 e sobrepô - lo na matriz
		jg++;
	} while (jg < (qtp + 1)); // e por fim este laço para finalizar a contagem dos jogadores
}


struct informacoes
{
	//informações da coleta
	void info_coleta(int* vez, int* coletorp, int* coletap, int* tempop, int* ocupadox, int* ocupadoy)
	{
		system("CLS");
		if ((recursos.ocupado[ocupadox[0]][ocupadoy[0]] == *vez) && (recursos.ocupado[ocupadox[1]][ocupadoy[1]] == *vez) && (recursos.ocupado[ocupadox[2]][ocupadoy[2]] == *vez))
		{
			gotoxy(75, 12);
			printf("---> N de Coletas: 3 <---\n");
		}
		else
		{
			if (((recursos.ocupado[ocupadox[0]][ocupadoy[0]] == *vez) && (recursos.ocupado[ocupadox[1]][ocupadoy[1]] == *vez)) || ((recursos.ocupado[ocupadox[0]][ocupadoy[0]] == *vez) && (recursos.ocupado[ocupadox[2]][ocupadoy[2]] == *vez)) || ((recursos.ocupado[ocupadox[1]][ocupadoy[1]] == *vez) && (recursos.ocupado[ocupadox[2]][ocupadoy[2]] == *vez)))
			{
				gotoxy(75, 12);
				printf("---> N de Coletas: 2 <---\n");
			}
			else
			{
				if ((recursos.ocupado[ocupadox[0]][ocupadoy[0]] == *vez) || (recursos.ocupado[ocupadox[1]][ocupadoy[1]] == *vez) || (recursos.ocupado[ocupadox[2]][ocupadoy[2]] == *vez))
				{
					gotoxy(75, 12);
					printf("---> N de Coletas: 1 <---\n");
				}
				else
				{
					gotoxy(75, 12);
					printf("---> N de Coletas: 0 <---\n");
				}
			}
		}
		gotoxy(0, 1);
		printf("< Coleta 1 >\n");
		printf("-> População designada:\n");
		printf("- Humanos: %i\n", coletorp[0]);
		printf("- Gigantes: %i\n", coletorp[1]);
		printf("- Goblins: %i\n", coletorp[2]);
		gotoxy(30, 1);
		printf("-> Recursos a serem coletados:\n");
		gotoxy(30, 2);
		printf("- Alimento: %i\n", coletap[0]);
		gotoxy(30, 3);
		printf("- Madeira: %i\n", coletap[1]);
		gotoxy(30, 4);
		printf("- Pedra: %i\n", coletap[2]);
		gotoxy(30, 5);
		printf("Turnos restantes: %i", tempop[0]);
		gotoxy(15, 8);
		printf("Posição em x: %d - Posição em y: %d", ocupadox[0], ocupadoy[0]);
		gotoxy(0, 10);
		printf("< Coleta 2 >\n");
		printf("-> População designada:\n");
		printf("- Humanos: %i\n", coletorp[3]);
		printf("- Gigantes: %i\n", coletorp[4]);
		printf("- Goblins: %i\n", coletorp[5]);
		gotoxy(30, 10);
		printf("-> Recursos a serem coletados:\n");
		gotoxy(30, 11);
		printf("- Alimento: %i\n", coletap[3]);
		gotoxy(30, 12);
		printf("- Madeira: %i\n", coletap[4]);
		gotoxy(30, 13);
		printf("- Pedra: %i\n", coletap[5]);
		gotoxy(30, 14);
		printf("Turnos restantes: %i", tempop[1]);
		gotoxy(15, 17);
		printf("Posição em x: %d - Posição em y: %d", ocupadox[1], ocupadoy[1]);
		gotoxy(0, 19);
		printf("< Coleta 3 >\n");
		printf("-> População designada:\n");
		printf("- Humanos: %i\n", coletorp[6]);
		printf("- Gigantes: %i\n", coletorp[7]);
		printf("- Goblins: %i\n", coletorp[8]);
		gotoxy(30, 19);
		printf("-> Recursos a serem coletados:\n");
		gotoxy(30, 20);
		printf("- Alimento: %i\n", coletap[6]);
		gotoxy(30, 21);
		printf("- Madeira: %i\n", coletap[7]);
		gotoxy(30, 22);
		printf("- Pedra: %i\n", coletap[8]);
		gotoxy(30, 23);
		printf("Turnos restantes: %i\n\n", tempop[2]);
		gotoxy(15, 26);
		printf("Posição em x: %d - Posição em y: %d", ocupadox[0], ocupadoy[0]);
		_getch();
	}

	void info_construcoes(bool* quartel, bool* muralha, bool* templo, int* vez)
	{
		system("cls");
		printf("Informações das Contruções:\n\n");

		if (*quartel == true)
		{
			printf("Quartel - Você já possuí!!\n");
		}
		else
		{
			if ((*quartel == false) && (vct.construcao1[2] > 0) && (*vez == 1))
			{
				printf("Quartel - Construção em andamento. Termina em : %i turnos\n", vct.construcao1[2]);
			}
			else
			{
				if ((*quartel == false) && (vct.construcao1[2] == -1) && (*vez == 1))
				{
					printf("Quartel - Ainda não construido.\n");
				}
				else
				{
					if ((*quartel == false) && (vct.construcao2[2] > 0) && (*vez == 2))
					{
						printf("Quartel - Construção em andamento. Termina em : %i turnos\n", vct.construcao2[2]);
					}
					else
					{
						if ((*quartel == false) && (vct.construcao2[2] == -1) && (*vez == 2))
						{
							printf("Quartel - Ainda não construido.\n");
						}
						else
						{
							if ((*quartel == false) && (vct.construcao3[2] > 0) && (*vez == 3))
							{
								printf("Quartel - Construção em andamento. Termina em : %i turnos\n", vct.construcao3[2]);
							}
							else
							{
								if ((*quartel == false) && (vct.construcao3[2] == -1) && (*vez == 3))
								{
									printf("Quartel - Ainda não construido.\n");
								}
								else
								{
									if ((*quartel == false) && (vct.construcao4[2] > 0) && (*vez == 4))
									{
										printf("Quartel - Construção em andamento. Termina em : %i turnos\n", vct.construcao4[2]);
									}
									else
									{
										if ((*quartel == false) && (vct.construcao4[2] == -1) && (*vez == 4))
										{
											printf("Quartel - Ainda não construido.\n");
										}
									}
								}
							}
						}

					}
				}
			}
		}

		if (*muralha == true)
		{
			printf("Muralha - Você já possuí!!\n");
		}
		else
		{
			if ((*muralha == false) && (vct.construcao1[0] > 0) && (*vez == 1))
			{
				printf("Muralha - Construção em andamento. Termina em : %i turnos\n", vct.construcao1[0]);
			}
			else
			{
				if ((*muralha == false) && (vct.construcao1[0] == -1) && (*vez == 1))
				{
					printf("Muralha - Ainda não construido.\n");
				}
				else
				{
					if ((*muralha == false) && (vct.construcao2[0] > 0) && (*vez == 2))
					{
						printf("Muralha - Construção em andamento. Termina em : %i turnos\n", vct.construcao2[0]);
					}
					else
					{
						if ((*muralha == false) && (vct.construcao2[0] == -1) && (*vez == 2))
						{
							printf("Muralha - Ainda não construido.\n");
						}
						else
						{
							if ((*muralha == false) && (vct.construcao3[0] > 0) && (*vez == 3))
							{
								printf("Muralha - Construção em andamento. Termina em : %i turnos\n", vct.construcao3[0]);
							}
							else
							{
								if ((*muralha == false) && (vct.construcao3[0] == -1) && (*vez == 3))
								{
									printf("Muralha - Ainda não construido.\n");
								}
								else
								{
									if ((*muralha == false) && (vct.construcao4[0] > 0) && (*vez == 4))
									{
										printf("Muralha - Construção em andamento. Termina em : %i turnos\n", vct.construcao4[0]);
									}
									else
									{
										if ((*muralha == false) && (vct.construcao4[0] == -1) && (*vez == 4))
										{
											printf("Muralha - Ainda não construido.\n");
										}
									}
								}
							}
						}

					}
				}
			}
		}

		if (*templo == true)
		{
			printf("Templo - Você já possuí!!\n");
		}
		else
		{
			if ((*templo == false) && (vct.construcao1[1] > 0) && (*vez == 1))
			{
				printf("Templo - Construção em andamento. Termina em : %i turnos\n", vct.construcao1[1]);
			}
			else
			{
				if ((*templo == false) && (vct.construcao1[1] == -1) && (*vez == 1))
				{
					printf("Templo - Ainda não construido.\n");
				}
				else
				{
					if ((*templo == false) && (vct.construcao2[1] > 0) && (*vez == 2))
					{
						printf("Templo - Construção em andamento. Termina em : %i turnos\n", vct.construcao2[1]);
					}
					else
					{
						if ((*templo == false) && (vct.construcao2[1] == -1) && (*vez == 2))
						{
							printf("Templo - Ainda não construido.\n");
						}
						else
						{
							if ((*templo == false) && (vct.construcao3[1] > 0) && (*vez == 3))
							{
								printf("Templo - Construção em andamento. Termina em : %i turnos\n", vct.construcao3[1]);
							}
							else
							{
								if ((*templo == false) && (vct.construcao3[1] == -1) && (*vez == 3))
								{
									printf("Templo - Ainda não construido.\n");
								}
								else
								{
									if ((*templo == false) && (vct.construcao4[1] > 0) && (*vez == 4))
									{
										printf("Templo - Construção em andamento. Termina em : %i turnos\n", vct.construcao4[1]);
									}
									else
									{
										if ((*templo == false) && (vct.construcao4[1] == -1) && (*vez == 4))
										{
											printf("Templo - Ainda não construido.\n");
										}
									}
								}
							}
						}

					}
				}
			}
		}

		if (*vez == 1)
		{

			printf("\n");
			printf("Casas: (Obs: -1 significa que não existe a respectiva casa em construção nesse momento!)\n");
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas1[1][0], vct.casas1[1][1], vct.casas1[1][2]);
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas1[2][0], vct.casas1[2][1], vct.casas1[2][2]);

		}
		if (*vez == 2)
		{

			printf("\n");
			printf("Casas: (Obs: -1 significa que não existe a respectiva casa em construção nesse momento!)\n");
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas2[1][0], vct.casas2[1][1], vct.casas2[1][2]);
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas2[2][0], vct.casas2[2][1], vct.casas2[2][2]);

		}
		if (*vez == 3)
		{

			printf("\n");
			printf("Casas: (Obs: -1 significa que não existe a respectiva casa em construção nesse momento!)\n");
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas3[1][0], vct.casas3[1][1], vct.casas3[1][2]);
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas3[2][0], vct.casas3[2][1], vct.casas3[2][2]);

		}
		if (*vez == 4)
		{

			printf("\n");
			printf("Casas: (Obs: -1 significa que não existe a respectiva casa em construção nesse momento!)\n");
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas4[1][0], vct.casas4[1][1], vct.casas4[1][2]);
			printf("Humanos: %i Turnos    Gigantes: %i Turnos   Goblins: %i Turnos\n", vct.casas4[2][0], vct.casas4[2][1], vct.casas4[2][2]);

		}


		printf("\n\n");
		printf("Ao pressionar qualquer tecla você será redirecionado ao Menu Principal!!\n");
		system("pause");
	}

	void info_gerais()
	{
		printf("Construções");
	}
	void militar(int* tipop, int* exercito, int* vez)
	{
		int i;
		printf("--------> Exército disponível: <-------- \n");
		printf("-> Humanos: %i\n-> Gigantes: %i\n-> Goblins: %i\n", tipop[0], tipop[1], tipop[2]);
		if (atacante[*vez - 1] != 0)
		{
			printf("--------> Exército enviado: <-------- \n");
			printf("-> Humanos: %i\n-> Gigantes: %i\n-> Goblins: %i\n", exercito[0], exercito[1], exercito[2]);
			printf("PLAYER ALVO DE ATAQUE: %i\n", atacante[*vez - 1]);
			printf("Tempo restante até o ataque %i\n", tempoatq[*vez - 1]);
		}
		else
		{
			printf("Você não possui ataques em andamento\n");
		}
		for (i = 0; i < 4; i++)
		{
			if (atacante[i] == *vez)
			{
				printf("Você será atacado em %i turnos por Player %i", tempoatq[i], i + 1);
				break;
			}
		}
		_getch();
		return;
	}

	void menu_info(bool* quartel, bool* muralha, bool* templo, int* vez, int* coletorp, int* coletap, int* tempo, int* ocupadox, int* ocupadoy, int* tipop, int* exercito)
	{
		int n = 0;
		system("cls");
		printf("Qual informação deseja?\n");
		printf("F1 - Coleta\n");
		printf("F2 - Construções\n");
		printf("F3 - Informações Gerais do Jogo\n");
		printf("F4 - Militar\n");
		printf("ESC - Voltar para o Menu\n");
		do
		{
			n = _getch();
			if (n == 0)
			{
				n = _getch();
			}
			else
			{
				system("cls");
				printf("Qual informação deseja?\n");
				printf("F1 - Coleta\n");
				printf("F2 - Construções\n");
				printf("F3 - Informações Gerais do Jogo;");
				printf("F4 - Militar\n");
				printf("ESC - Voltar para o Menu\n");
			}
		} while (((n < 59) || (n > 62)) && !(n == 27));

		switch (n)
		{
		case 59:
			info_coleta(vez, coletorp, coletap, tempo, ocupadox, ocupadoy);
			break;
		case 60:
			info_construcoes(quartel, muralha, templo, vez);
			break;
		case 61:
			info_gerais();
			break;
		case 62:
			militar(&tipop[0], &exercito[0], vez);
		default:
			break;
		}
	}

}; struct informacoes info;



void menu(int* alimento, int* madeira, int* pedra, int* tempop, int* coletorp, int* coletap, int* vez, int* xp, int* yp, bool* quartel, bool* templo, bool* muralha, int* hab, int* ocupadox, int* ocupadoy, int* tipop, int* atq, int* def, int* exercito)
{
	int i = 0, menu = 0;
	system("CLS");
	gotoxy(20, 0);
	printf("TURNO: %d\n", turno);
	for (i = 0; i < 4; i++)
	{
		if (atacante[i] == *vez)
		{
			gotoxy(50, 12);
			printf("VOCÊ SERÁ ATACADO EM %i TURNOS POR PLAYER %i!!!!!", tempoatq[i], i + 1);
			break;
		}
	}
	gotoxy(0, 1);
	printf("%sJOGADOR %d\n", C_GREEN, *vez);
	printf("Selecione: \n");
	printf("F1 - Coletar Recursos \n");
	printf("F2 - Construir\n");
	printf("F3 - Atacar\n");
	printf("F4 - Apenas encerrar turno\n");
	printf("F5 - Criar Soldados \n");
	printf("F6 - Informações");
	gotoxy(70, 16);
	printf("Alimento: %d\tMadeira: %d\tPedra: %d\n", *alimento, *madeira, *pedra);
	printf("Humanos: %d\tGigantes: %d\tGoblins: %d\n", hab[0], hab[1], hab[2]);
	gotoxy(20, 20);
	printf("Pressione ESC para exibir o mapa");
	gotoxy(0, 8);
	/* Aqui esta sendo executado um laco que só termina quando a tecla que o
	usuario digitou for as teclas requisitadas. */
	do
	{
		menu = _getch(); /* Aqui o programa espera o cara digitar alguma tecla
		e então apos ele apertar a funcaio _getch retorna o valor da
tecla/carctere para a variavel menu */

// Condicao de tecla(s) especial(is):
		if (menu == 0) /* Se a funcao _getch retornar zero é porque a tecla ou a
		combinacao de teclas é especial - no caso a funcao _getch
		retorna dois valores, sendo o primeiro zero. */
		{
			menu = _getch(); // Aqui a variavel tecla guarda "automaticamente" o valor do segundo retorno
		}

		// Se a 1.a _getch só retornou um numero, retorne.
		else
		{
			system("CLS");
			gotoxy(20, 0);
			printf("TURNO: %d\n", turno);
			printf("%sJOGADOR %d\n", C_GREEN, *vez);
			printf("Selecione: \n");
			printf("F1 - Coletar Recursos \n");
			printf("F2 - Construir\n");
			printf("F3 - Atacar\n");
			printf("F4 - Apenas encerrar turno\n");
			printf("F5 - Criar Soldados \n");
			printf("F6 - Informações\n");
			gotoxy(70, 16);
			printf("Alimento: %d\tMadeira: %d\tGoblins: %d\n", *alimento, *madeira, *pedra);
			printf("Humanos: %d\tGigantes: %d\tGoblins: %d\n", hab[0], hab[1], hab[2]);
			gotoxy(20, 20);
			printf("Pressione ESC para exibir o mapa");
			gotoxy(0, 8);
		}
	} while (((menu < 59) || (menu > 64)) && !(menu == 27)); //...Enquanto nao for as teclas

	switch (menu)
	{
	case 59:
		// Função de coleta de recursos;
		system("CLS");
		if (hab[0] == 0 && hab[1] == 0 && hab[2] == 0)
		{
			printf("Você não pode coletar pois não possui nenhuma raça disponível\n");
			_getch();
		}
		else
		{
			if (((hab[0] + hab[1] + hab[2]) * 0.1) < 1)
			{
				printf("Você não pode coletar pois 10 por cento da sua população é menor do que 1 e as coletas exigem no máximo 10 por cento da população\n");
				_getch();
			}
			else
			{
				if ((recursos.ocupado[ocupadox[0]][ocupadoy[0]] == *vez) && (recursos.ocupado[ocupadox[1]][ocupadoy[1]] == *vez) && (recursos.ocupado[ocupadox[2]][ocupadoy[2]] == *vez))
				{
					printf("%sVocê já está coletando mais de 3 vezes \n\n", C_GREEN);
					_getch();
				}
				else
				{
					coleta(xp, yp, coletap, tempop, coletorp, hab, vez, ocupadox, ocupadoy);
				}
			}
		}
		break;
	case 60:
		// Função de construções;;
		vct.controle = 0;
		n_constroi(vez, &menu);
		if (vct.controle == 0)
		{
			ct.construcoes(madeira, pedra, alimento, vez, quartel, templo, muralha, xp, yp);
			system("CLS");
		}
		break;
	case 61:
		// Função de ataque (apenas quando tiver quartel
		if (*quartel == false)
		{
			system("cls");
			printf("Você não possui Quartel!!\nPor Favor volte após construir um Quartel!!\n\n");
			system("pause");
		}
		else
		{
			if ((tipop[0] == 0) && (tipop[1] == 0) && (tipop[2] == 0))
			{
				system("cls");
				printf("Você não possui soldados para atacar!!\n");
				system("pause");
			}
			else
			{
				if (atacante[*vez - 1] != 0)
				{
					system("CLS");
					printf("Você já está realizando um ataque, menos violência por enquanto!\n");
					system("Pause");
				}
				ataque(vez, &tipop[0], atq, def, xp, yp, &exercito[0]);
			}
		}
		break;
	case 62:
		// Apenas adciona mais um turno na contagem e vai para o próximo jogador
		*vez = 0;
		break;
	case 63:
		// Abre uma função que converte os soldados
		converter_hab(vez, tipop, hab);

		break;
	case 64:
		// Abre uma função que tem algumas informações
		info.menu_info(quartel, muralha, templo, vez, coletorp, coletap, tempop, ocupadox, ocupadoy, tipop, exercito);
		break;
	default:
		map(); //Exibir o mapa não conta como turno, logo continua sendo a vez do jogador
		break;
	}
}




int main()
{
	setlocale(LC_ALL, "Portuguese"); // Importa as variáveis de ambiente
	int i = 0, j = 0, x, y, x1, y1, x2, y2, x3, y3, x4, y4, tr, vez = 0;
	char c = 0;
	for (i = 0; i < 4; i++)
	{
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
		x3 = 0;
		y3 = 0;
		x4 = 0;
		y4 = 0;
	}

	struct recursos_player_1
	{
		int alimento = 5;
		int madeira = 5;
		int pedra = 5;
		int hab[3] = { 10, 0, 0 };
		int ocupadox[3] = { 0, 0, 0 };
		int ocupadoy[3] = { 0, 0, 0 };
		int coleta[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //aqui armazena-se as quantidades de recurso que o player irá receber, 3 linhas são (alimento, madeira e pedra) já as colunas (coleta 1, coleta 2 e coleta 3)
		int tempo[3] = { 0, 0, 0 };
		int coletor[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };//variaveis de controle das coletas [4 linhas são: qtd de turno e os 3 tipos de habitantes, já as 3 colunas são a quantidade de coletas simultâneas]

		struct exercito
		{
			int tipo[3] = { 1000, 500, 1000 };
			int atq = 0;
			int def = 300;
			int ex[3] = { 0, 0, 0 };
		}; struct exercito ep1;

		struct construcoes
		{
			int casa[3] = { 1,0,0 }; /*(humano, gigante, goblin)*/
			bool muralha = false;
			bool quartel = true;
			bool templo = false;

		}; struct construcoes ct1;

	}; struct recursos_player_1 rp1;

	struct recursos_player_2
	{
		int alimento = 5;
		int madeira = 5;
		int pedra = 5;
		int hab[3] = { 10, 0, 0 };
		int ocupadox[3] = { 0, 0, 0 };
		int ocupadoy[3] = { 0, 0, 0 };
		int coleta[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //aqui armazena-se as quantidades de recurso que o player irá receber, 3 linhas são (alimento, madeira e pedra) já as colunas (coleta 1, coleta 2 e coleta 3)
		int tempo[3] = { 0, 0, 0 };
		int coletor[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		struct exercito
		{
			int tipo[3] = { 0, 0, 0 };
			int atq = 0;
			int def = 300;
			int ex[3] = { 1000, 1000, 500 };
		}; struct exercito ep2;

		struct construcoes
		{
			int casa[3] = { 1,0,0 };
			bool muralha = false;
			bool quartel = true;
			bool templo = false;

		}; struct construcoes ct2;
	}; struct recursos_player_2 rp2; // struct dos jogadores, tem tudo o que eles vão precisar para jogar

	struct recursos_player_3
	{
		int alimento = 5;
		int madeira = 5;
		int pedra = 5;
		int hab[3] = { 10, 0, 0 };
		int ocupadox[3] = { 0, 0, 0 };
		int ocupadoy[3] = { 0, 0, 0 };
		int coleta[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //aqui armazena-se as quantidades de recurso que o player irá receber, 3 linhas são (alimento, madeira e pedra) já as colunas (coleta 1, coleta 2 e coleta 3)
		int tempo[3] = { 0, 0, 0 };
		int coletor[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		struct exercito
		{
			int tipo[3] = { 0, 0, 0 };
			int atq = 0;
			int def = 300;
			int ex[3] = { 0, 0, 0 };
		}; struct exercito ep3;

		struct construcoes
		{
			int casa[3] = { 1,0,0 };
			bool muralha = false;
			bool quartel = false;
			bool templo = false;
		}; struct construcoes ct3;
	}; struct recursos_player_3 rp3;

	struct recursos_player_4
	{
		int alimento = 5;
		int madeira = 5;
		int pedra = 5;
		int hab[3] = { 10, 0, 0 };
		int ocupadox[3] = { 0, 0, 0 };
		int ocupadoy[3] = { 0, 0, 0 };
		int coleta[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //aqui armazena-se as quantidades de recurso que o player irá receber, 3 linhas são (alimento, madeira e pedra) já as colunas (coleta 1, coleta 2 e coleta 3)
		int tempo[3] = { 0, 0, 0 };
		int coletor[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		struct exercito
		{
			int tipo[3] = { 0, 0, 0 };
			int atq = 0;
			int def = 300;
			int ex[3] = { 0, 0, 0 };
		}; struct exercito ep4;

		struct construcoes
		{
			int casa[3] = { 1,0,0 };
			bool muralha = false;
			bool quartel = false;
			bool templo = false;
		}; struct construcoes ct4;
	}; struct recursos_player_4 rp4;

	system("CLS");
	gotoxy(65, 0);
	printf("----------| Bem Vindo |----------");
	gotoxy(65, 1);
	printf("--------------| A |--------------");
	gotoxy(65, 2);
	printf("--------| Age of Cities |--------\n\n\n\n");
	system("pause");

	srand((unsigned)time(NULL));
	do
	{
		system("CLS");
		printf("%sQuantidade de turnos: ", C_GREEN);
		scanf_s("%d", &tr);
	} while ((c = getchar() != '\n' && c != EOF) || (tr < 1));// variável local da main, pois ela vai servir de comparação para quando atingir os turnos o jogo encerrar.

	do
	{
		system("CLS");
		printf("%sQuantidade de players (Mín 2 e Máx 4): ", C_GREEN);
		scanf_s("%d", &qtp);
	} while ((c = getchar() != '\n' && c != EOF) || ((qtp < 2) || (qtp > 4)));

	posicao_jogadores(); // definição da posição dos jogadores no mapa;
	system("CLS");

	printf("%sPor favor Aguarde!!\n", C_GREEN);
	printf("Gerando recursos no mapa \n\n");

	for (int i = 0; i < 3; i++) {
		printf("Carregando");
		for (int j = 0; j < 3; j++) {
			printf(".");
			Sleep(400);
		}
		printf("\r");
		for (int j = 0; j < 50; j++)
		{
			printf(" "); // apaga a linha anterior
		}
		printf("\r");
	}

	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 25; y++)
		{
			recursos.ocupado[x][y] = 0;
			constrjg[x][y] = 0;
			switch (mapa[x][y])
			{
			case 1:
				x1 = x;
				y1 = y; // Guardando informações da posição dos jogadores em forma de dois numeros inteiros(linha - coluna)
				break;
			case 2:
				x2 = x;
				y2 = y;
				break;
			case 3:
				x3 = x;
				y3 = y;
				break;
			case 4:
				x4 = x;
				y4 = y;
				break;
			default:
				mapa[x][y] = rand() % 4;  // Randomização de recursos no mapa.
				switch (mapa[x][y])
				{
				case 0:
					mapa[x][y] = 86; // 86 Equivale a V de vazio, para posição no mapa vazia.
					recursos.alimento[x][y] = 0;
					recursos.madeira[x][y] = 0;
					recursos.pedra[x][y] = 0;
					break;
				case 1:
					mapa[x][y] = 67; // C de coleta;
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				case 2:
					mapa[x][y] = 67; // C de coleta;		> Equilibrando para ter 3x de chance a mais de gerar terrenos de coleta em comparação a terrenos vazios.
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				default:
					mapa[x][y] = 67; // C de coleta;
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				}
				break;
			}
		}
	}

	/*------------------------------ Mapa ----------------------------------------*/
	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 25; y++)
		{
			recursos.ocupado[x][y] = 0;
			switch (mapa[x][y])
			{
			case 1:
				x1 = x;
				y1 = y; // Guardando informações da posição dos jogadores em forma de dois numeros inteiros(linha - coluna)
				break;
			case 2:
				x2 = x;
				y2 = y;
				break;
			case 3:
				x3 = x;
				y3 = y;
				break;
			case 4:
				x4 = x;
				y4 = y;
				break;
			default:
				mapa[x][y] = rand() % 4;  // Randomização de recursos no mapa.
				switch (mapa[x][y])
				{
				case 0:
					mapa[x][y] = 86; // 86 Equivale a V de vazio, para posição no mapa vazia.
					recursos.alimento[x][y] = 0;
					recursos.madeira[x][y] = 0;
					recursos.pedra[x][y] = 0;
					break;
				case 1:
					mapa[x][y] = 67; // C de coleta;
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				case 2:
					mapa[x][y] = 67; // C de coleta;		> Equilibrando para ter 3x de chance a mais de gerar terrenos de coleta em comparação a terrenos vazios.
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				default:
					mapa[x][y] = 67; // C de coleta;
					recursos.alimento[x][y] = 400 + (rand() % 2000);
					recursos.madeira[x][y] = 400 + (rand() % 2000);
					recursos.pedra[x][y] = 400 + (rand() % 2000);
					break;
				}
				break;
			}
		}
	}
	/******************************************************************************/
	system("cls");
	printf("Mapa gerado com sucesso!!\n\n");
	system("pause");
	map(); // Função para imprimir o mapa na tela (ele limpa a tela primeiro), util caso precise ao longo do jogo.

	while (turno < tr) // Agora começa o jogo, a partir daqui ele sempre vai voltar
	{
		for (i = 0; i < qtp; i++)
		{
			if (vivo[i] == true)
			{
				j = j + 1;
			}
		}
		if (j < 2)
		{
			for (i = 0; i < qtp; i++)
			{
				if (vivo[i] == true)
					break;
			}
			printf("PARABÉNS PLAYER %i, Você foi o único que restou de pé\n", i - 1);
			break;
		}
		// ***************** CHEGAGEM DE GUERRA *********************
		system("CLS");

		if (atacado[0] == true)
		{
			for (i = 0; i < 4; i++)
			{
				if (atacante[i] == 1)
				{
					break;
				}
			}
			if (tempoatq[i] == 0)
			{
				if (i == 1)
				{
					// conta do player 1 x player 2
					rp1.ep1.atq = (rp1.ep1.tipo[0] * 15) + (rp1.ep1.tipo[1] * 5) + (rp1.ep1.tipo[2] * 20);
					rp1.ep1.def = (rp1.ep1.tipo[0] * 10) + (rp1.ep1.tipo[1] * 20) + (rp1.ep1.tipo[2] * 5) + 300;
					rp2.ep2.atq = (rp2.ep2.ex[0] * 15) + (rp2.ep2.ex[1] * 5) + (rp2.ep2.ex[2] * 20);
					rp2.ep2.def = (rp2.ep2.ex[0] * 10) + (rp2.ep2.ex[1] * 20) + (rp2.ep2.ex[2] * 5);
					if (rp1.ct1.templo == true)
					{
						rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
					}
					if (rp1.ct1.muralha == true)
					{
						rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.25);
					}
					if (rp2.ct2.templo == true)
					{
						rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
					}
					j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
					if (j == 0)
					{
						while (rp2.ep2.def > 0 && rp1.ep1.def > 0)
						{
							rp2.ep2.def = rp2.ep2.def - rp1.ep1.atq;
							if (rp2.ep2.def <= 0)
							{
								break;
							}
							rp1.ep1.def = rp1.ep1.def - rp2.ep2.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
						}
					}
					else
					{
						while (rp2.ep2.def > 0 && rp1.ep1.def > 0)
						{

							rp1.ep1.def = rp1.ep1.def - rp2.ep2.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
							rp2.ep2.def = rp2.ep2.def - rp1.ep1.atq;
							if (rp2.ep2.def <= 0)
							{
								break;
							}

						}
					}
					if (rp1.ep1.def <= 0)
					{
						printf("Batalha entre Player 1 e Player 2 resultou em derrota para o Player 1.\n\n PLAYER 1, GAME OVER PARA VOCÊ\n");
						_getch();
						atacado[0] = false;
						vivo[0] = false;
						atacante[1] = 0;
						rp2.alimento = rp2.alimento + rp1.alimento;
						rp2.madeira = rp2.madeira + rp1.madeira;
						rp2.pedra = rp2.pedra + rp1.pedra;
						if (rp2.ep2.ex[0] > 0)
						{
							for (j = 0; j < rp2.ep2.def / 3; j = j + 10)
							{
								rp2.ep2.ex[0] = j / 10;
							}
						}
						if (rp2.ep2.ex[1] > 0)
						{
							for (j = 0; j < rp2.ep2.def / 3; j = j + 20)
							{
								rp2.ep2.ex[1] = j / 20;
							}
						}
						if (rp2.ep2.ex[2] > 0)
						{
							for (j = 0; j < rp2.ep2.def / 3; j = j + 5)
							{
								rp2.ep2.ex[2] = j / 5;
							}
						}
						rp2.ep2.tipo[0] = rp2.ep2.tipo[0] + rp2.ep2.ex[0];
						rp2.ep2.tipo[1] = rp2.ep2.tipo[1] + rp2.ep2.ex[1];
						rp2.ep2.tipo[2] = rp2.ep2.tipo[2] + rp2.ep2.ex[2];
						printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
					}
					else
					{
						printf("Batalha entre Player 1 e Player 2 resultou em derrota para o Player 2.\n\n PLAYER 2, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
						_getch();
						atacado[0] = false;
						atacante[1] = 0;
						rp2.ep2.ex[0] = 0;
						rp2.ep2.ex[1] = 0;
						rp2.ep2.ex[2] = 0;
						if (rp1.ep1.tipo[0] > 0)
						{
							for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 10)
							{
								rp1.ep1.tipo[0] = j / 10;
							}
						}
						if (rp1.ep1.tipo[1] > 0)
						{
							for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 20)
							{
								rp1.ep1.tipo[1] = j / 20;
							}
						}
						if (rp1.ep1.tipo[2] > 0)
						{
							for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 5)
							{
								rp1.ep1.tipo[2] = j / 5;
							}
						}
						printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
					}
				}
				else
				{
					if (i == 2)
					{
						// conta do player 1 x player 3
						rp1.ep1.atq = (rp1.ep1.tipo[0] * 15) + (rp1.ep1.tipo[1] * 5) + (rp1.ep1.tipo[2] * 20);
						rp1.ep1.def = (rp1.ep1.tipo[0] * 10) + (rp1.ep1.tipo[1] * 20) + (rp1.ep1.tipo[2] * 5) + 300;
						rp3.ep3.atq = (rp3.ep3.ex[0] * 15) + (rp3.ep3.ex[1] * 5) + (rp3.ep3.ex[2] * 20);
						rp3.ep3.def = (rp3.ep3.ex[0] * 10) + (rp3.ep3.ex[1] * 20) + (rp3.ep3.ex[2] * 5);
						if (rp1.ct1.templo == true)
						{
							rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
						}
						if (rp1.ct1.muralha == true)
						{
							rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.25);
						}
						if (rp3.ct3.templo == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp3.ep3.def > 0 && rp1.ep1.def > 0)
							{
								rp3.ep3.def = rp3.ep3.def - rp1.ep1.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
								rp1.ep1.def = rp1.ep1.def - rp3.ep3.atq;
								if (rp1.ep1.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp3.ep3.def > 0 && rp1.ep1.def > 0)
							{

								rp1.ep1.def = rp1.ep1.def - rp3.ep3.atq;
								if (rp1.ep1.def <= 0)
								{
									break;
								}
								rp3.ep3.def = rp3.ep3.def - rp1.ep1.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}

							}
						}
						if (rp1.ep1.def <= 0)
						{
							printf("Batalha entre Player 1 e Player 3 resultou em derrota para o Player 1.\n\n PLAYER 1, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[0] = false;
							vivo[0] = false;
							atacante[2] = 0;
							rp3.alimento = rp3.alimento + rp1.alimento;
							rp3.madeira = rp3.madeira + rp1.madeira;
							rp3.pedra = rp3.pedra + rp1.pedra;
							if (rp3.ep3.ex[0] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 10)
								{
									rp3.ep3.ex[0] = j / 10;
								}
							}
							if (rp3.ep3.ex[1] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 20)
								{
									rp3.ep3.ex[1] = j / 20;
								}
							}
							if (rp3.ep3.ex[2] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 5)
								{
									rp3.ep3.ex[2] = j / 5;
								}
							}
							rp3.ep3.tipo[0] = rp3.ep3.tipo[0] + rp3.ep3.ex[0];
							rp3.ep3.tipo[1] = rp3.ep3.tipo[1] + rp3.ep3.ex[1];
							rp3.ep3.tipo[2] = rp3.ep3.tipo[2] + rp3.ep3.ex[2];
							printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 1 e Player 3 resultou em derrota para o Player 3.\n\n PLAYER 3, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[0] = false;
							atacante[2] = 0;
							rp3.ep3.ex[0] = 0;
							rp3.ep3.ex[1] = 0;
							rp3.ep3.ex[2] = 0;
							if (rp1.ep1.tipo[0] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 10)
								{
									rp1.ep1.tipo[0] = j / 10;
								}
							}
							if (rp1.ep1.tipo[1] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 20)
								{
									rp1.ep1.tipo[1] = j / 20;
								}
							}
							if (rp1.ep1.tipo[2] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 5)
								{
									rp1.ep1.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
						}
					}
					else
					{
						// conta do player 1 x player 4
						rp1.ep1.atq = (rp1.ep1.tipo[0] * 15) + (rp1.ep1.tipo[1] * 5) + (rp1.ep1.tipo[2] * 20);
						rp1.ep1.def = (rp1.ep1.tipo[0] * 10) + (rp1.ep1.tipo[1] * 20) + (rp1.ep1.tipo[2] * 5) + 300;
						rp4.ep4.atq = (rp4.ep4.ex[0] * 15) + (rp4.ep4.ex[1] * 5) + (rp4.ep4.ex[2] * 20);
						rp4.ep4.def = (rp4.ep4.ex[0] * 10) + (rp4.ep4.ex[1] * 20) + (rp4.ep4.ex[2] * 5);
						if (rp1.ct1.templo == true)
						{
							rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
						}
						if (rp1.ct1.muralha == true)
						{
							rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.25);
						}
						if (rp4.ct4.templo == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp4.ep4.def > 0 && rp1.ep1.def > 0)
							{
								rp4.ep4.def = rp4.ep4.def - rp1.ep1.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
								rp1.ep1.def = rp1.ep1.def - rp4.ep4.atq;
								if (rp1.ep1.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp4.ep4.def > 0 && rp1.ep1.def > 0)
							{

								rp1.ep1.def = rp1.ep1.def - rp4.ep4.atq;
								if (rp1.ep1.def <= 0)
								{
									break;
								}
								rp4.ep4.def = rp4.ep4.def - rp1.ep1.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}

							}
						}
						if (rp1.ep1.def <= 0)
						{
							printf("Batalha entre Player 1 e Player 4 resultou em derrota para o Player 1.\n\n PLAYER 1, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[0] = false;
							vivo[0] = false;
							atacante[3] = 0;
							rp4.alimento = rp4.alimento + rp1.alimento;
							rp4.madeira = rp4.madeira + rp1.madeira;
							rp4.pedra = rp4.pedra + rp1.pedra;
							if (rp4.ep4.ex[0] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 10)
								{
									rp4.ep4.ex[0] = j / 10;
								}
							}
							if (rp4.ep4.ex[1] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 20)
								{
									rp4.ep4.ex[1] = j / 20;
								}
							}
							if (rp4.ep4.ex[2] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 5)
								{
									rp4.ep4.ex[2] = j / 5;
								}
							}
							rp4.ep4.tipo[0] = rp4.ep4.tipo[0] + rp4.ep4.ex[0];
							rp4.ep4.tipo[1] = rp4.ep4.tipo[1] + rp4.ep4.ex[1];
							rp4.ep4.tipo[2] = rp4.ep4.tipo[2] + rp4.ep4.ex[2];
							printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 1 e Player 4 resultou em derrota para o Player 4.\n\n PLAYER 4, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[0] = false;
							atacante[3] = 0;
							rp4.ep4.ex[0] = 0;
							rp4.ep4.ex[1] = 0;
							rp4.ep4.ex[2] = 0;
							if (rp1.ep1.tipo[0] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 10)
								{
									rp1.ep1.tipo[0] = j / 10;
								}
							}
							if (rp1.ep1.tipo[1] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 20)
								{
									rp1.ep1.tipo[1] = j / 20;
								}
							}
							if (rp1.ep1.tipo[2] > 0)
							{
								for (j = 0; j < ((rp1.ep1.def / 3) - 300); j = j + 5)
								{
									rp1.ep1.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
						}
					}
				}
				system("Pause");
			}
			else
			{
				tempoatq[i] --;
			}
		}
		if (atacado[1] == true)
		{
			for (i = 0; i < 4; i++)
			{
				if (atacante[i] == 2)
				{
					break;
				}
			}
			if (tempoatq[i] == 0)
			{
				if (i == 0)
				{
					// conta do player 2 x player 1
					rp1.ep1.atq = (rp1.ep1.ex[0] * 15) + (rp1.ep1.ex[1] * 5) + (rp1.ep1.ex[2] * 20);
					rp1.ep1.def = (rp1.ep1.ex[0] * 10) + (rp1.ep1.ex[1] * 20) + (rp1.ep1.ex[2] * 5);
					rp2.ep2.atq = (rp2.ep2.tipo[0] * 15) + (rp2.ep2.tipo[1] * 5) + (rp2.ep2.tipo[2] * 20);
					rp2.ep2.def = (rp2.ep2.tipo[0] * 10) + (rp2.ep2.tipo[1] * 20) + (rp2.ep2.tipo[2] * 5) + 300;
					if (rp2.ct2.templo == true)
					{
						rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
					}
					if (rp2.ct2.muralha == true)
					{
						rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.25);
					}
					if (rp1.ct1.templo == true)
					{
						rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
					}
					j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
					if (j == 0)
					{
						while (rp2.ep2.def > 0 && rp1.ep1.def > 0)
						{
							rp1.ep1.def = rp1.ep1.def - rp2.ep2.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
							rp2.ep2.def = rp2.ep2.def - rp1.ep1.atq;
							if (rp2.ep2.def <= 0)
							{
								break;
							}
						}
					}
					else
					{
						while (rp2.ep2.def > 0 && rp1.ep1.def > 0)
						{

							rp2.ep2.def = rp2.ep2.def - rp1.ep1.atq;
							if (rp2.ep2.def <= 0)
							{
								break;
							}
							rp1.ep1.def = rp1.ep1.def - rp2.ep2.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}

						}
					}
					if (rp2.ep2.def <= 0)
					{
						printf("Batalha entre Player 2 e Player 1 resultou em derrota para o Player 2.\n\n PLAYER 2, GAME OVER PARA VOCÊ\n");
						_getch();
						atacado[1] = false;
						vivo[1] = false;
						atacante[0] = 0;
						rp1.alimento = rp1.alimento + rp2.alimento;
						rp1.madeira = rp1.madeira + rp2.madeira;
						rp1.pedra = rp1.pedra + rp2.pedra;
						if (rp1.ep1.ex[0] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 10)
							{
								rp1.ep1.ex[0] = j / 10;
							}
						}
						if (rp1.ep1.ex[1] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 20)
							{
								rp1.ep1.ex[1] = j / 20;
							}
						}
						if (rp1.ep1.ex[2] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 5)
							{
								rp1.ep1.ex[2] = j / 5;
							}
						}
						rp1.ep1.tipo[0] = rp1.ep1.tipo[0] + rp1.ep1.ex[0];
						rp1.ep1.tipo[1] = rp1.ep1.tipo[1] + rp1.ep1.ex[1];
						rp1.ep1.tipo[2] = rp1.ep1.tipo[2] + rp1.ep1.ex[2];
						printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
					}
					else
					{
						printf("Batalha entre Player 2 e Player 1 resultou em derrota para o Player 1.\n\n PLAYER 1, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
						_getch();
						atacado[1] = false;
						atacante[0] = 0;
						rp1.ep1.ex[0] = 0;
						rp1.ep1.ex[1] = 0;
						rp1.ep1.ex[2] = 0;
						if (rp2.ep2.tipo[0] = j > 0)
						{
							for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 10)
							{
								rp2.ep2.tipo[0] = j / 10;
							}
						}
						if (rp2.ep2.tipo[1] = j > 0)
						{
							for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 20)
							{
								rp2.ep2.tipo[1] = j / 20;
							}
						}
						if (rp2.ep2.tipo[2] = j > 0)
						{
							for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 5)
							{
								rp2.ep2.tipo[2] = j / 5;
							}
						}
						printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
					}
				}
				else
				{
					if (i == 2)
					{
						// conta do player 2 x player 3
						rp3.ep3.atq = (rp3.ep3.ex[0] * 15) + (rp3.ep3.ex[1] * 5) + (rp3.ep3.ex[2] * 20);
						rp3.ep3.def = (rp3.ep3.ex[0] * 10) + (rp3.ep3.ex[1] * 20) + (rp3.ep3.ex[2] * 5);
						rp2.ep2.atq = (rp2.ep2.tipo[0] * 15) + (rp2.ep2.tipo[1] * 5) + (rp2.ep2.tipo[2] * 20);
						rp2.ep2.def = (rp2.ep2.tipo[0] * 10) + (rp2.ep2.tipo[1] * 20) + (rp2.ep2.tipo[2] * 5) + 300;
						if (rp2.ct2.templo == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
						}
						if (rp2.ct2.muralha == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.25);
						}
						if (rp3.ct3.templo == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp2.ep2.def > 0 && rp3.ep3.def > 0)
							{
								rp2.ep2.def = rp2.ep2.def - rp3.ep3.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
								rp3.ep3.def = rp3.ep3.def - rp2.ep2.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp2.ep2.def > 0 && rp3.ep3.def > 0)
							{

								rp3.ep3.def = rp3.ep3.def - rp2.ep2.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
								rp2.ep2.def = rp2.ep2.def - rp3.ep3.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}

							}
						}
						if (rp2.ep2.def <= 0)
						{
							printf("Batalha entre Player 2 e Player 3 resultou em derrota para o Player 2.\n\n PLAYER 2, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[1] = false;
							vivo[1] = false;
							atacante[2] = 0;
							rp3.alimento = rp3.alimento + rp2.alimento;
							rp3.madeira = rp3.madeira + rp2.madeira;
							rp3.pedra = rp3.pedra + rp2.pedra;
							if (rp3.ep3.ex[0] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 10)
								{
									rp3.ep3.ex[0] = j / 10;
								}
							}
							if (rp3.ep3.ex[1] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 20)
								{
									rp3.ep3.ex[1] = j / 20;
								}
							}
							if (rp3.ep3.ex[2] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 5)
								{
									rp3.ep3.ex[2] = j / 5;
								}
							}
							rp3.ep3.tipo[0] = rp3.ep3.tipo[0] + rp3.ep3.ex[0];
							rp3.ep3.tipo[1] = rp3.ep3.tipo[1] + rp3.ep3.ex[1];
							rp3.ep3.tipo[2] = rp3.ep3.tipo[2] + rp3.ep3.ex[2];
							printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 2 e Player 3 resultou em derrota para o Player 3.\n\n PLAYER 3, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[1] = false;
							atacante[2] = 0;
							rp3.ep3.ex[0] = 0;
							rp3.ep3.ex[1] = 0;
							rp3.ep3.ex[2] = 0;
							if (rp2.ep2.tipo[0] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 10)
								{
									rp2.ep2.tipo[0] = j / 10;
								}
							}
							if (rp2.ep2.tipo[1] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 20)
								{
									rp2.ep2.tipo[1] = j / 20;
								}
							}
							if (rp2.ep2.tipo[2] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 5)
								{
									rp2.ep2.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
						}
					}
					else
					{
						// conta do player 2 x player 4
						rp4.ep4.atq = (rp4.ep4.ex[0] * 15) + (rp4.ep4.ex[1] * 5) + (rp4.ep4.ex[2] * 20);
						rp4.ep4.def = (rp4.ep4.ex[0] * 10) + (rp4.ep4.ex[1] * 20) + (rp4.ep4.ex[2] * 5);
						rp2.ep2.atq = (rp2.ep2.tipo[0] * 15) + (rp2.ep2.tipo[1] * 5) + (rp2.ep2.tipo[2] * 20);
						rp2.ep2.def = (rp2.ep2.tipo[0] * 10) + (rp2.ep2.tipo[1] * 20) + (rp2.ep2.tipo[2] * 5) + 300;
						if (rp2.ct2.templo == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
						}
						if (rp2.ct2.muralha == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.25);
						}
						if (rp4.ct4.templo == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp2.ep2.def > 0 && rp4.ep4.def > 0)
							{
								rp2.ep2.def = rp2.ep2.def - rp4.ep4.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
								rp4.ep4.def = rp4.ep4.def - rp4.ep4.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp2.ep2.def > 0 && rp4.ep4.def > 0)
							{

								rp4.ep4.def = rp4.ep4.def - rp2.ep2.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
								rp2.ep2.def = rp2.ep2.def - rp4.ep4.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
							}
						}
						if (rp2.ep2.def <= 0)
						{
							printf("Batalha entre Player 2 e Player 4 resultou em derrota para o Player 2.\n\n PLAYER 2, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[1] = false;
							vivo[1] = false;
							atacante[3] = 0;
							rp4.alimento = rp4.alimento + rp2.alimento;
							rp4.madeira = rp4.madeira + rp2.madeira;
							rp4.pedra = rp4.pedra + rp2.pedra;
							if (rp4.ep4.ex[0] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 10)
								{
									rp4.ep4.ex[0] = j / 10;
								}
							}
							if (rp4.ep4.ex[1] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 20)
								{
									rp4.ep4.ex[1] = j / 20;
								}
							}
							if (rp4.ep4.ex[2] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 5)
								{
									rp4.ep4.ex[2] = j / 5;
								}
							}
							rp4.ep4.tipo[0] = rp4.ep4.tipo[0] + rp4.ep4.ex[0];
							rp4.ep4.tipo[1] = rp4.ep4.tipo[1] + rp4.ep4.ex[1];
							rp4.ep4.tipo[2] = rp4.ep4.tipo[2] + rp4.ep4.ex[2];
							printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 2 e Player 4 resultou em derrota para o Player 4.\n\n PLAYER 4, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[1] = false;
							atacante[3] = 0;
							rp4.ep4.ex[0] = 0;
							rp4.ep4.ex[1] = 0;
							rp4.ep4.ex[2] = 0;
							if (rp2.ep2.tipo[0] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 10)
								{
									rp2.ep2.tipo[0] = j / 10;
								}
							}
							if (rp2.ep2.tipo[2] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 20)
								{
									rp2.ep2.tipo[1] = j / 20;
								}
							}
							if (rp2.ep2.tipo[3] > 0)
							{
								for (j = 0; j < ((rp2.ep2.def / 3) - 300); j = j + 5)
								{
									rp2.ep2.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
						}
					}
				}
				system("Pause");
			}
			else
			{
				tempoatq[i] --;
			}
		}
		if (atacado[2] == true)
		{
			for (i = 0; i < 4; i++)
			{
				if (atacante[i] == 3)
				{
					break;
				}
			}
			if (tempoatq[i] == 0)
			{
				if (i == 0)
				{
					// conta do player 3 x player 1
					rp1.ep1.atq = (rp1.ep1.ex[0] * 15) + (rp1.ep1.ex[1] * 5) + (rp1.ep1.ex[2] * 20);
					rp1.ep1.def = (rp1.ep1.ex[0] * 10) + (rp1.ep1.ex[1] * 20) + (rp1.ep1.ex[2] * 5);
					rp3.ep3.atq = (rp3.ep3.tipo[0] * 15) + (rp3.ep3.tipo[1] * 5) + (rp3.ep3.tipo[2] * 20);
					rp3.ep3.def = (rp3.ep3.tipo[0] * 10) + (rp3.ep3.tipo[1] * 20) + (rp3.ep3.tipo[2] * 5) + 300;
					if (rp3.ct3.templo == true)
					{
						rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
					}
					if (rp3.ct3.muralha == true)
					{
						rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.25);
					}
					if (rp1.ct1.templo == true)
					{
						rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
					}
					j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
					if (j == 0)
					{
						while (rp3.ep3.def > 0 && rp1.ep1.def > 0)
						{
							rp3.ep3.def = rp3.ep3.def - rp1.ep1.atq;
							if (rp3.ep3.def <= 0)
							{
								break;
							}
							rp1.ep1.def = rp1.ep1.def - rp1.ep1.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
						}
					}
					else
					{
						while (rp3.ep3.def > 0 && rp1.ep1.def > 0)
						{

							rp1.ep1.def = rp1.ep1.def - rp3.ep3.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
							rp3.ep3.def = rp3.ep3.def - rp1.ep1.atq;
							if (rp3.ep3.def <= 0)
							{
								break;
							}

						}
					}
					if (rp3.ep3.def <= 0)
					{
						printf("Batalha entre Player 3 e Player 1 resultou em derrota para o Player 3.\n\n PLAYER 3, GAME OVER PARA VOCÊ\n");
						_getch();
						atacado[2] = false;
						vivo[2] = false;
						atacante[0] = 0;
						rp1.alimento = rp1.alimento + rp3.alimento;
						rp1.madeira = rp1.madeira + rp3.madeira;
						rp1.pedra = rp1.pedra + rp3.pedra;
						if (rp1.ep1.ex[0] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 10)
							{
								rp1.ep1.ex[0] = j / 10;
							}
						}
						if (rp1.ep1.ex[1] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 20)
							{
								rp1.ep1.ex[1] = j / 20;
							}
						}
						if (rp1.ep1.ex[2] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 5)
							{
								rp1.ep1.ex[2] = j / 5;
							}
						}
						rp1.ep1.tipo[0] = rp1.ep1.tipo[0] + rp1.ep1.ex[0];
						rp1.ep1.tipo[1] = rp1.ep1.tipo[1] + rp1.ep1.ex[1];
						rp1.ep1.tipo[2] = rp1.ep1.tipo[2] + rp1.ep1.ex[2];
						printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
					}
					else
					{
						printf("Batalha entre Player 3 e Player 1 resultou em derrota para o Player 1.\n\n PLAYER 1, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
						_getch();
						atacado[2] = false;
						atacante[0] = 0;
						rp1.ep1.ex[0] = 0;
						rp1.ep1.ex[1] = 0;
						rp1.ep1.ex[2] = 0;
						if (rp3.ep3.tipo[0] > 0)
						{
							for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 10)
							{
								rp3.ep3.tipo[0] = j / 10;
							}
						}
						if (rp3.ep3.tipo[1] > 0)
						{
							for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 20)
							{
								rp3.ep3.tipo[1] = j / 20;
							}
						}
						if (rp3.ep3.tipo[2] > 0)
						{
							for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 5)
							{
								rp3.ep3.tipo[2] = j / 5;
							}
						}
						printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
					}
				}
				else
				{
					if (i == 1)
					{
						// conta do player 3 x player 2
						rp2.ep2.atq = (rp2.ep2.ex[0] * 15) + (rp2.ep2.ex[1] * 5) + (rp2.ep2.ex[2] * 20);
						rp2.ep2.def = (rp2.ep2.ex[0] * 10) + (rp2.ep2.ex[1] * 20) + (rp2.ep2.ex[2] * 5);
						rp3.ep3.atq = (rp3.ep3.tipo[0] * 15) + (rp3.ep3.tipo[1] * 5) + (rp3.ep3.tipo[2] * 20);
						rp3.ep3.def = (rp3.ep3.tipo[0] * 10) + (rp3.ep3.tipo[1] * 20) + (rp3.ep3.tipo[2] * 5) + 300;
						if (rp3.ct3.templo == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
						}
						if (rp3.ct3.muralha == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.25);
						}
						if (rp2.ct2.templo == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp3.ep3.def > 0 && rp2.ep2.def > 0)
							{
								rp3.ep3.def = rp3.ep3.def - rp2.ep2.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
								rp2.ep2.def = rp2.ep2.def - rp2.ep2.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp3.ep3.def > 0 && rp2.ep2.def > 0)
							{

								rp2.ep2.def = rp2.ep2.def - rp3.ep3.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
								rp3.ep3.def = rp3.ep3.def - rp2.ep2.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}

							}
						}
						if (rp3.ep3.def <= 0)
						{
							printf("Batalha entre Player 3 e Player 2 resultou em derrota para o Player 3.\n\n PLAYER 3, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[2] = false;
							vivo[2] = false;
							atacante[1] = 0;
							rp2.alimento = rp2.alimento + rp3.alimento;
							rp2.madeira = rp2.madeira + rp3.madeira;
							rp2.pedra = rp2.pedra + rp3.pedra;
							if (rp2.ep2.ex[0] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 10)
								{
									rp2.ep2.ex[0] = j / 10;
								}
							}
							if (rp2.ep2.ex[1] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 20)
								{
									rp2.ep2.ex[1] = j / 20;
								}
							}
							if (rp2.ep2.ex[2] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 5)
								{
									rp2.ep2.ex[2] = j / 5;
								}
							}
							rp2.ep2.tipo[0] = rp2.ep2.tipo[0] + rp2.ep2.ex[0];
							rp2.ep2.tipo[1] = rp2.ep2.tipo[1] + rp2.ep2.ex[1];
							rp2.ep2.tipo[2] = rp2.ep2.tipo[2] + rp2.ep2.ex[2];
							printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 3 e Player 2 resultou em derrota para o Player 2.\n\n PLAYER 2, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[2] = false;
							atacante[0] = 0;
							rp2.ep2.ex[0] = 0;
							rp2.ep2.ex[1] = 0;
							rp2.ep2.ex[2] = 0;
							if (rp3.ep3.tipo[0] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 10)
								{
									rp3.ep3.tipo[0] = j / 10;
								}
							}
							if (rp3.ep3.tipo[1] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 20)
								{
									rp3.ep3.tipo[1] = j / 20;
								}
							}
							if (rp3.ep3.tipo[2] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 5)
								{
									rp3.ep3.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
						}
					}
					else
					{
						// conta do player 3 x player 4
						rp4.ep4.atq = (rp4.ep4.ex[0] * 15) + (rp4.ep4.ex[1] * 5) + (rp4.ep4.ex[2] * 20);
						rp4.ep4.def = (rp4.ep4.ex[0] * 10) + (rp4.ep4.ex[1] * 20) + (rp4.ep4.ex[2] * 5);
						rp3.ep3.atq = (rp3.ep3.tipo[0] * 15) + (rp3.ep3.tipo[1] * 5) + (rp3.ep3.tipo[2] * 20);
						rp3.ep3.def = (rp3.ep3.tipo[0] * 10) + (rp3.ep3.tipo[1] * 20) + (rp3.ep3.tipo[2] * 5) + 300;
						if (rp3.ct3.templo == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
						}
						if (rp3.ct3.muralha == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.25);
						}
						if (rp4.ct4.templo == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp3.ep3.def > 0 && rp4.ep4.def > 0)
							{
								rp3.ep3.def = rp3.ep3.def - rp4.ep4.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
								rp4.ep4.def = rp4.ep4.def - rp4.ep4.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp3.ep3.def > 0 && rp4.ep4.def > 0)
							{

								rp4.ep4.def = rp4.ep4.def - rp3.ep3.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
								rp3.ep3.def = rp3.ep3.def - rp4.ep4.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}

							}
						}
						if (rp3.ep3.def <= 0)
						{
							printf("Batalha entre Player 3 e Player 4 resultou em derrota para o Player 3.\n\n PLAYER 3, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[2] = false;
							vivo[2] = false;
							atacante[3] = 0;
							rp4.alimento = rp4.alimento + rp3.alimento;
							rp4.madeira = rp4.madeira + rp3.madeira;
							rp4.pedra = rp4.pedra + rp3.pedra;
							if (rp4.ep4.ex[0] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 10)
								{
									rp4.ep4.ex[0] = j / 10;
								}
							}
							if (rp4.ep4.ex[1] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 20)
								{
									rp4.ep4.ex[1] = j / 20;
								}
							}
							if (rp4.ep4.ex[2] > 0)
							{
								for (j = 0; j < rp4.ep4.def / 3; j = j + 5)
								{
									rp4.ep4.ex[2] = j / 5;
								}
							}
							rp4.ep4.tipo[0] = rp4.ep4.tipo[0] + rp4.ep4.ex[0];
							rp4.ep4.tipo[1] = rp4.ep4.tipo[1] + rp4.ep4.ex[1];
							rp4.ep4.tipo[2] = rp4.ep4.tipo[2] + rp4.ep4.ex[2];
							printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 3 e Player 4 resultou em derrota para o Player 4.\n\n PLAYER 4, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[2] = false;
							atacante[3] = 0;
							rp4.ep4.ex[0] = 0;
							rp4.ep4.ex[1] = 0;
							rp4.ep4.ex[2] = 0;
							if (rp3.ep3.tipo[0] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 10)
								{
									rp3.ep3.tipo[0] = j / 10;
								}
							}
							if (rp3.ep3.tipo[1] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 20)
								{
									rp3.ep3.tipo[1] = j / 20;
								}
							}
							if (rp3.ep3.tipo[2] > 0)
							{
								for (j = 0; j < ((rp3.ep3.def / 3) - 300); j = j + 5)
								{
									rp3.ep3.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
						}
					}
				}
				system("Pause");
			}
			else
			{
				tempoatq[i] --;
			}
		}
		if (atacado[3] == true)
		{
			for (i = 0; i < 4; i++)
			{
				if (atacante[i] == 4)
				{
					break;
				}
			}
			if (tempoatq[i] == 0)
			{
				if (i == 0)
				{
					// conta do player 4 x player 1
					rp1.ep1.atq = (rp1.ep1.ex[0] * 15) + (rp1.ep1.ex[1] * 5) + (rp1.ep1.ex[2] * 20);
					rp1.ep1.def = (rp1.ep1.ex[0] * 10) + (rp1.ep1.ex[1] * 20) + (rp1.ep1.ex[2] * 5);
					rp4.ep4.atq = (rp4.ep4.tipo[0] * 15) + (rp4.ep4.tipo[1] * 5) + (rp4.ep4.tipo[2] * 20);
					rp4.ep4.def = (rp4.ep4.tipo[0] * 10) + (rp4.ep4.tipo[1] * 20) + (rp4.ep4.tipo[2] * 5) + 300;
					if (rp4.ct4.templo == true)
					{
						rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
					}
					if (rp4.ct4.muralha == true)
					{
						rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.25);
					}
					if (rp1.ct1.templo == true)
					{
						rp1.ep1.def = rp1.ep1.def + (rp1.ep1.def * 0.1);
					}
					j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
					if (j == 0)
					{
						while (rp4.ep4.def > 0 && rp1.ep1.def > 0)
						{
							rp4.ep4.def = rp4.ep4.def - rp1.ep1.atq;
							if (rp4.ep4.def <= 0)
							{
								break;
							}
							rp1.ep1.def = rp1.ep1.def - rp1.ep1.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
						}
					}
					else
					{
						while (rp4.ep4.def > 0 && rp1.ep1.def > 0)
						{

							rp1.ep1.def = rp1.ep1.def - rp4.ep4.atq;
							if (rp1.ep1.def <= 0)
							{
								break;
							}
							rp4.ep4.def = rp4.ep4.def - rp1.ep1.atq;
							if (rp4.ep4.def <= 0)
							{
								break;
							}

						}
					}
					if (rp4.ep4.def <= 0)
					{
						printf("Batalha entre Player 4 e Player 1 resultou em derrota para o Player 4.\n\n PLAYER 4, GAME OVER PARA VOCÊ\n");
						_getch();
						atacado[3] = false;
						vivo[3] = false;
						atacante[0] = 0;
						rp1.alimento = rp1.alimento + rp4.alimento;
						rp1.madeira = rp1.madeira + rp4.madeira;
						rp1.pedra = rp1.pedra + rp4.pedra;
						if (rp1.ep1.ex[0] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 10)
							{
								rp1.ep1.ex[0] = j / 10;
							}
						}
						if (rp1.ep1.ex[1] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 20)
							{
								rp1.ep1.ex[1] = j / 20;
							}
						}
						if (rp1.ep1.ex[2] > 0)
						{
							for (j = 0; j < rp1.ep1.def / 3; j = j + 5)
							{
								rp1.ep1.ex[2] = j / 5;
							}
						}
						rp1.ep1.tipo[0] = rp1.ep1.tipo[0] + rp1.ep1.ex[0];
						rp1.ep1.tipo[1] = rp1.ep1.tipo[1] + rp1.ep1.ex[1];
						rp1.ep1.tipo[2] = rp1.ep1.tipo[2] + rp1.ep1.ex[2];
						printf("JOGADOR 1 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp1.ep1.tipo[0], rp1.ep1.tipo[1], rp1.ep1.tipo[2]);
					}
					else
					{
						printf("Batalha entre Player 4 e Player 1 resultou em derrota para o Player 1.\n\n PLAYER 1, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
						_getch();
						atacado[3] = false;
						atacante[0] = 0;
						rp1.ep1.ex[0] = 0;
						rp1.ep1.ex[1] = 0;
						rp1.ep1.ex[2] = 0;
						if (rp4.ep4.tipo[0] > 0)
						{
							for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 10)
							{
								rp4.ep4.tipo[0] = j / 10;
							}
						}
						if (rp4.ep4.tipo[1] > 0)
						{
							for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 20)
							{
								rp4.ep4.tipo[1] = j / 20;
							}
						}
						if (rp4.ep4.tipo[2] > 0)
						{
							for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 5)
							{
								rp4.ep4.tipo[2] = j / 5;
							}
						}
						printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
					}

				}
				else
				{
					if (i == 1)
					{
						// conta do player 4 x player 2
						rp2.ep2.atq = (rp2.ep2.ex[0] * 15) + (rp2.ep2.ex[1] * 5) + (rp2.ep2.ex[2] * 20);
						rp2.ep2.def = (rp2.ep2.ex[0] * 10) + (rp2.ep2.ex[1] * 20) + (rp2.ep2.ex[2] * 5);
						rp4.ep4.atq = (rp4.ep4.tipo[0] * 15) + (rp4.ep4.tipo[1] * 5) + (rp4.ep4.tipo[2] * 20);
						rp4.ep4.def = (rp4.ep4.tipo[0] * 10) + (rp4.ep4.tipo[1] * 20) + (rp4.ep4.tipo[2] * 5) + 300;
						if (rp4.ct4.templo == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
						}
						if (rp4.ct4.muralha == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.25);
						}
						if (rp2.ct2.templo == true)
						{
							rp2.ep2.def = rp2.ep2.def + (rp2.ep2.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp4.ep4.def > 0 && rp2.ep2.def > 0)
							{
								rp4.ep4.def = rp4.ep4.def - rp2.ep2.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
								rp2.ep2.def = rp2.ep2.def - rp2.ep2.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp4.ep4.def > 0 && rp2.ep2.def > 0)
							{

								rp2.ep2.def = rp2.ep2.def - rp4.ep4.atq;
								if (rp2.ep2.def <= 0)
								{
									break;
								}
								rp4.ep4.def = rp4.ep4.def - rp2.ep2.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}

							}
						}
						if (rp4.ep4.def <= 0)
						{
							printf("Batalha entre Player 4 e Player 2 resultou em derrota para o Player 4.\n\n PLAYER 4, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[3] = false;
							vivo[3] = false;
							atacante[1] = 0;
							rp2.alimento = rp2.alimento + rp4.alimento;
							rp2.madeira = rp2.madeira + rp4.madeira;
							rp2.pedra = rp2.pedra + rp4.pedra;
							if (rp2.ep2.ex[0] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 10)
								{
									rp2.ep2.ex[0] = j / 10;
								}
							}
							if (rp2.ep2.ex[1] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 20)
								{
									rp2.ep2.ex[1] = j / 20;
								}
							}
							if (rp2.ep2.ex[2] > 0)
							{
								for (j = 0; j < rp2.ep2.def / 3; j = j + 5)
								{
									rp2.ep2.ex[2] = j / 5;
								}
							}
							rp2.ep2.tipo[0] = rp2.ep2.tipo[0] + rp2.ep2.ex[0];
							rp2.ep2.tipo[1] = rp2.ep2.tipo[1] + rp2.ep2.ex[1];
							rp2.ep2.tipo[2] = rp2.ep2.tipo[2] + rp2.ep2.ex[2];
							printf("JOGADOR 2 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp2.ep2.tipo[0], rp2.ep2.tipo[1], rp2.ep2.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 4 e Player 2 resultou em derrota para o Player 2.\n\n PLAYER 2, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[3] = false;
							atacante[1] = 0;
							rp2.ep2.ex[0] = 0;
							rp2.ep2.ex[1] = 0;
							rp2.ep2.ex[2] = 0;
							if (rp4.ep4.tipo[0] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 10)
								{
									rp4.ep4.tipo[0] = j / 10;
								}
							}
							if (rp4.ep4.tipo[1] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 20)
								{
									rp4.ep4.tipo[1] = j / 20;
								}
							}
							if (rp4.ep4.tipo[2] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 5)
								{
									rp4.ep4.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
						}
					}
					else
					{
						// conta do player 4 x player 3
						rp3.ep3.atq = (rp3.ep3.ex[0] * 15) + (rp3.ep3.ex[1] * 5) + (rp3.ep3.ex[2] * 20);
						rp3.ep3.def = (rp3.ep3.ex[0] * 10) + (rp3.ep3.ex[1] * 20) + (rp3.ep3.ex[2] * 5);
						rp4.ep4.atq = (rp4.ep4.tipo[0] * 15) + (rp4.ep4.tipo[1] * 5) + (rp4.ep4.tipo[2] * 20);
						rp4.ep4.def = (rp4.ep4.tipo[0] * 10) + (rp4.ep4.tipo[1] * 20) + (rp4.ep4.tipo[2] * 5) + 300;
						if (rp4.ct4.templo == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.1);
						}
						if (rp4.ct4.muralha == true)
						{
							rp4.ep4.def = rp4.ep4.def + (rp4.ep4.def * 0.25);
						}
						if (rp3.ct3.templo == true)
						{
							rp3.ep3.def = rp3.ep3.def + (rp3.ep3.def * 0.1);
						}
						j = rand() % 1; //número aleatório é gerado pois em batalhas muito apertadas, até quem começa a atacar pode decidir a batalha, então é gerado um número de 0 a 1 pra decidir quem ataca
						if (j == 0)
						{
							while (rp4.ep4.def > 0 && rp3.ep3.def > 0)
							{
								rp4.ep4.def = rp4.ep4.def - rp3.ep3.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}
								rp3.ep3.def = rp3.ep3.def - rp3.ep3.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
							}
						}
						else
						{
							while (rp4.ep4.def > 0 && rp3.ep3.def > 0)
							{

								rp3.ep3.def = rp3.ep3.def - rp4.ep4.atq;
								if (rp3.ep3.def <= 0)
								{
									break;
								}
								rp4.ep4.def = rp4.ep4.def - rp3.ep3.atq;
								if (rp4.ep4.def <= 0)
								{
									break;
								}

							}
						}
						if (rp4.ep4.def <= 0)
						{
							printf("Batalha entre Player 4 e Player 3 resultou em derrota para o Player 4.\n\n PLAYER 4, GAME OVER PARA VOCÊ\n");
							_getch();
							atacado[3] = false;
							vivo[3] = false;
							atacante[2] = 0;
							rp3.alimento = rp3.alimento + rp4.alimento;
							rp3.madeira = rp3.madeira + rp4.madeira;
							rp3.pedra = rp3.pedra + rp4.pedra;
							if (rp3.ep3.ex[0] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 10)
								{
									rp3.ep3.ex[0] = j / 10;
								}
							}
							if (rp3.ep3.ex[1] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 20)
								{
									rp3.ep3.ex[1] = j / 20;
								}
							}
							if (rp3.ep3.ex[2] > 0)
							{
								for (j = 0; j < rp3.ep3.def / 3; j = j + 5)
								{
									rp3.ep3.ex[2] = j / 5;
								}
							}
							rp3.ep3.tipo[0] = rp3.ep3.tipo[0] + rp3.ep3.ex[0];
							rp3.ep3.tipo[1] = rp3.ep3.tipo[1] + rp3.ep3.ex[1];
							rp3.ep3.tipo[2] = rp3.ep3.tipo[2] + rp3.ep3.ex[2];
							printf("JOGADOR 3 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp3.ep3.tipo[0], rp3.ep3.tipo[1], rp3.ep3.tipo[2]);
						}
						else
						{
							printf("Batalha entre Player 4 e Player 3 resultou em derrota para o Player 3.\n\n PLAYER 3, VOCÊ PERDEU TODO O SEU EXERCITO ENVIADO!!\n");
							_getch();
							atacado[3] = false;
							atacante[2] = 0;
							rp3.ep3.ex[0] = 0;
							rp3.ep3.ex[1] = 0;
							if (rp4.ep4.tipo[0] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 10)
								{
									rp4.ep4.tipo[0] = j / 10;
								}
							}
							if (rp4.ep4.tipo[1] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 20)
								{
									rp4.ep4.tipo[1] = j / 20;
								}
							}
							if (rp4.ep4.tipo[2] > 0)
							{
								for (j = 0; j < ((rp4.ep4.def / 3) - 300); j = j + 5)
								{
									rp4.ep4.tipo[2] = j / 5;
								}
							}
							printf("JOGADOR 4 RESTOU COM EXÉRCITO TOTAL\n Humanos: %i\n Gigantes: %i\n Goblins: %i\n", rp4.ep4.tipo[0], rp4.ep4.tipo[1], rp4.ep4.tipo[2]);
						}
					}
				}
				system("Pause");
			}
			else
			{
				tempoatq[i] --;
			}

		}

		/****************************** Checagem de alimentos************************/
		rp1.alimento = rp1.alimento - (rp1.hab[0] + rp1.hab[1] + rp1.hab[2]);
		rp2.alimento = rp2.alimento - (rp2.hab[0] + rp2.hab[1] + rp2.hab[2]);
		rp3.alimento = rp3.alimento - (rp3.hab[0] + rp3.hab[1] + rp3.hab[2]);
		rp4.alimento = rp4.alimento - (rp4.hab[0] + rp4.hab[1] + rp4.hab[2]);

		//se o player estiver atacando os soldados gastam o dobro de alimento cada
		if (atacante[0] > 0)
		{
			rp1.alimento = rp1.alimento - (2 * (rp1.ep1.ex[0] + rp1.ep1.ex[1] + rp1.ep1.ex[2]));

		}
		if (atacante[1] > 0)
		{
			rp2.alimento = rp2.alimento - (2 * (rp2.ep2.ex[0] + rp2.ep2.ex[1] + rp2.ep2.ex[2]));

		}
		if (atacante[2] > 0)
		{
			rp3.alimento = rp3.alimento - (2 * (rp3.ep3.ex[0] + rp3.ep3.ex[1] + rp3.ep3.ex[2]));

		}
		if (atacante[3] > 0)
		{
			rp4.alimento = rp4.alimento - (2 * (rp4.ep4.ex[0] + rp4.ep4.ex[1] + rp4.ep4.ex[2]));

		}
		/****************************************************************************************/

		/************************** Checagem de Habitantes***************************************/
		if ((rp1.hab[0] <= 0) && (rp1.hab[1] <= 0) && (rp1.hab[2] <= 0))
		{
			vivo[0] = false;
		}
		if ((rp2.hab[0] <= 0) && (rp2.hab[1] <= 0) && (rp2.hab[2] <= 0))
		{
			vivo[1] = false;
		}
		if ((rp3.hab[0] <= 0) && (rp3.hab[1] <= 0) && (rp3.hab[2] <= 0))
		{
			vivo[2] = false;
		}
		if ((rp4.hab[0] <= 0) && (rp4.hab[1] <= 0) && (rp4.hab[2] <= 0))
		{
			vivo[3] = false;
		}
		/*****************************************************************************************/

		//a cada turno que o alimento for <= 0 é descontado 1 de cada habitante
		if (rp1.alimento <= 0)
		{
			rp1.hab[0] = rp1.hab[0] - 1;
			rp1.hab[1] = rp1.hab[1] - 1;
			rp1.hab[2] = rp1.hab[2] - 1;
		}
		if (rp2.alimento <= 0)
		{
			rp2.hab[0] = rp2.hab[0] - 1;
			rp2.hab[1] = rp2.hab[1] - 1;
			rp2.hab[2] = rp2.hab[2] - 1;
		}
		if (rp3.alimento <= 0)
		{
			rp3.hab[0] = rp3.hab[0] - 1;
			rp3.hab[1] = rp3.hab[1] - 1;
			rp3.hab[2] = rp3.hab[2] - 1;
		}
		if (rp4.alimento <= 0)
		{
			rp4.hab[0] = rp4.hab[0] - 1;
			rp4.hab[1] = rp4.hab[1] - 1;
			rp4.hab[2] = rp4.hab[2] - 1;
		}
		/****************************************************************************/

		/****************** Checagem de construções ***********************/
		//player 1
		if (vct.construcao1[0] == turno)
		{
			rp1.ct1.muralha = true;
		}
		if (vct.construcao1[1] == turno)
		{
			rp1.ct1.templo = true;
		}
		if (vct.construcao1[2] == turno)
		{
			rp1.ct1.quartel = true;
		}
		if (vct.casas1[0][1] == turno)
		{
			rp1.ct1.casa[0] = rp1.ct1.casa[0] + 1;
		}
		if (vct.casas1[0][2] == turno)
		{
			rp1.ct1.casa[0] = rp1.ct1.casa[0] + 1;
		}
		if (vct.casas1[1][1] == turno)
		{
			rp1.ct1.casa[1] = rp1.ct1.casa[1] + 1;
		}
		if (vct.casas1[1][2] == turno)
		{
			rp1.ct1.casa[1] = rp1.ct1.casa[1] + 1;
		}
		if (vct.casas1[2][1] == turno)
		{
			rp1.ct1.casa[2] = rp1.ct1.casa[2] + 1;
		}
		if (vct.casas1[2][2] == turno)
		{
			rp1.ct1.casa[2] = rp1.ct1.casa[2] + 1;
		}



		//player 2
		if (vct.construcao2[0] == turno)
		{
			rp1.ct1.muralha = true;
		}
		if (vct.construcao2[1] == turno)
		{
			rp2.ct2.templo = true;
		}
		if (vct.construcao2[2] == turno)
		{
			rp2.ct2.quartel = true;
		}
		if (vct.casas2[0][1] == turno)
		{
			rp2.ct2.casa[0] = rp2.ct2.casa[0] + 1;
		}
		if (vct.casas2[0][2] == turno)
		{
			rp2.ct2.casa[0] = rp2.ct2.casa[0] + 1;
		}
		if (vct.casas2[1][1] == turno)
		{
			rp2.ct2.casa[1] = rp2.ct2.casa[1] + 1;
		}
		if (vct.casas2[1][2] == turno)
		{
			rp2.ct2.casa[1] = rp2.ct2.casa[1] + 1;
		}
		if (vct.casas2[2][1] == turno)
		{
			rp2.ct2.casa[2] = rp2.ct2.casa[2] + 1;
		}
		if (vct.casas2[2][2] == turno)
		{
			rp2.ct2.casa[2] = rp2.ct2.casa[2] + 1;
		}



		//player 3
		if (vct.construcao3[0] == turno)
		{
			rp3.ct3.muralha = true;
		}
		if (vct.construcao3[1] == turno)
		{
			rp3.ct3.templo = true;
		}
		if (vct.construcao3[2] == turno)
		{
			rp3.ct3.quartel = true;
		}
		if (vct.casas3[0][1] == turno)
		{
			rp3.ct3.casa[0] = rp3.ct3.casa[0] + 1;
		}
		if (vct.casas3[0][2] == turno)
		{
			rp3.ct3.casa[0] = rp3.ct3.casa[0] + 1;
		}
		if (vct.casas3[1][1] == turno)
		{
			rp3.ct3.casa[1] = rp3.ct3.casa[1] + 1;
		}
		if (vct.casas3[1][2] == turno)
		{
			rp3.ct3.casa[1] = rp3.ct3.casa[1] + 1;
		}
		if (vct.casas3[2][1] == turno)
		{
			rp3.ct3.casa[2] = rp1.ct1.casa[2] + 1;
		}
		if (vct.casas3[2][2] == turno)
		{
			rp3.ct3.casa[2] = rp3.ct3.casa[2] + 1;
		}



		//player 4
		if (vct.construcao4[0] == turno)
		{
			rp4.ct4.muralha = true;
		}
		if (vct.construcao4[1] == turno)
		{
			rp4.ct4.templo = true;
		}
		if (vct.construcao4[2] == turno)
		{
			rp4.ct4.quartel = true;
		}
		if (vct.casas4[0][1] == turno)
		{
			rp4.ct4.casa[0] = rp4.ct4.casa[0] + 1;
		}
		if (vct.casas4[0][2] == turno)
		{
			rp4.ct4.casa[0] = rp4.ct4.casa[0] + 1;
		}
		if (vct.casas4[1][1] == turno)
		{
			rp4.ct4.casa[1] = rp4.ct4.casa[1] + 1;
		}
		if (vct.casas4[1][2] == turno)
		{
			rp4.ct4.casa[1] = rp4.ct4.casa[1] + 1;
		}
		if (vct.casas4[2][1] == turno)
		{
			rp4.ct4.casa[2] = rp4.ct4.casa[2] + 1;
		}
		if (vct.casas4[2][2] == turno)
		{
			rp4.ct4.casa[2] = rp4.ct4.casa[2] + 1;
		}

		/*******************************************************************/

		//CHECAGEM DAS COLETAS

		//PLAYER 1

		if (recursos.ocupado[rp1.ocupadox[0]][rp1.ocupadoy[0]] == 1)
		{
			if (rp1.tempo[0] == 0)
			{
				rp1.alimento = rp1.alimento + rp1.coleta[0][0];
				rp1.madeira = rp1.madeira + rp1.coleta[0][1];
				rp1.pedra = rp1.pedra + rp1.coleta[0][2];
				rp1.hab[0] = rp1.hab[0] + rp1.coletor[0][0];
				rp1.hab[1] = rp1.hab[1] + rp1.coletor[0][1];
				rp1.hab[2] = rp1.hab[2] + rp1.coletor[0][2];
				rp1.coletor[0][0] = 0;
				rp1.coletor[0][1] = 0;
				rp1.coletor[0][2] = 0;
				recursos.ocupado[rp1.ocupadox[0]][rp1.ocupadoy[0]] = 0;
			}
			else
			{
				rp1.tempo[0] --;
			}
		}
		if (recursos.ocupado[rp1.ocupadox[1]][rp1.ocupadoy[1]] == 1)
		{
			if (rp1.tempo[1] == 0)
			{
				rp1.alimento = rp1.alimento + rp1.coleta[1][0];
				rp1.madeira = rp1.madeira + rp1.coleta[1][1];
				rp1.pedra = rp1.pedra + rp1.coleta[1][2];
				rp1.hab[0] = rp1.hab[0] + rp1.coletor[1][0];
				rp1.hab[1] = rp1.hab[1] + rp1.coletor[1][1];
				rp1.hab[2] = rp1.hab[2] + rp1.coletor[1][2];
				rp1.coletor[1][0] = 0;
				rp1.coletor[1][1] = 0;
				rp1.coletor[1][2] = 0;
				recursos.ocupado[rp1.ocupadox[1]][rp1.ocupadoy[1]] = 0;
			}
			else
			{
				rp1.tempo[1] --;
			}
		}
		if (recursos.ocupado[rp1.ocupadox[2]][rp1.ocupadoy[2]] == 1)
		{
			if (rp1.tempo[2] == 0)
			{
				rp1.alimento = rp1.alimento + rp1.coleta[2][0];
				rp1.madeira = rp1.madeira + rp1.coleta[2][1];
				rp1.pedra = rp1.pedra + rp1.coleta[2][2];
				rp1.hab[0] = rp1.hab[0] + rp1.coletor[2][0];
				rp1.hab[1] = rp1.hab[1] + rp1.coletor[2][1];
				rp1.hab[2] = rp1.hab[2] + rp1.coletor[2][2];
				rp1.coletor[2][0] = 0;
				rp1.coletor[2][1] = 0;
				rp1.coletor[2][2] = 0;
				recursos.ocupado[rp1.ocupadox[2]][rp1.ocupadoy[2]] = 0;
			}
			else
			{
				rp1.tempo[2] --;
			}
		}

		//PLAYER 2

		if (recursos.ocupado[rp2.ocupadox[0]][rp2.ocupadoy[0]] == 2)
		{
			if (rp2.tempo[0] == 0)
			{
				rp2.alimento = rp2.alimento + rp2.coleta[0][0];
				rp2.madeira = rp2.madeira + rp2.coleta[0][1];
				rp2.pedra = rp2.pedra + rp2.coleta[0][2];
				rp2.hab[0] = rp2.hab[0] + rp2.coletor[0][0];
				rp2.hab[1] = rp2.hab[1] + rp2.coletor[0][1];
				rp2.hab[2] = rp2.hab[2] + rp2.coletor[0][2];
				rp2.coletor[0][0] = 0;
				rp2.coletor[0][1] = 0;
				rp2.coletor[0][2] = 0;
				recursos.ocupado[rp2.ocupadox[0]][rp2.ocupadoy[0]] = 0;
			}
			else
			{

				rp2.tempo[0] --;
			}
		}
		if (recursos.ocupado[rp2.ocupadox[1]][rp2.ocupadoy[1]] == 2)
		{
			if (rp2.tempo[1] == 0)
			{
				rp2.alimento = rp2.alimento + rp2.coleta[1][0];
				rp2.madeira = rp2.madeira + rp2.coleta[1][1];
				rp2.pedra = rp2.pedra + rp2.coleta[1][2];
				rp2.hab[0] = rp2.hab[0] + rp2.coletor[1][0];
				rp2.hab[1] = rp2.hab[1] + rp2.coletor[1][1];
				rp2.hab[2] = rp2.hab[2] + rp2.coletor[1][2];
				rp2.coletor[1][0] = 0;
				rp2.coletor[1][1] = 0;
				rp2.coletor[1][2] = 0;
				recursos.ocupado[rp2.ocupadox[1]][rp2.ocupadoy[1]] = 0;
			}
			else
			{
				rp2.tempo[1] --;
			}
		}
		if (recursos.ocupado[rp2.ocupadox[2]][rp2.ocupadoy[2]] == 2)
		{
			if (rp2.tempo[2] == 0)
			{
				rp2.alimento = rp2.alimento + rp2.coleta[2][0];
				rp2.madeira = rp2.madeira + rp2.coleta[2][1];
				rp2.pedra = rp2.pedra + rp2.coleta[2][2];
				rp2.hab[0] = rp2.hab[0] + rp2.coletor[2][0];
				rp2.hab[1] = rp2.hab[1] + rp2.coletor[2][1];
				rp2.hab[2] = rp2.hab[2] + rp2.coletor[2][2];
				rp2.coletor[2][0] = 0;
				rp2.coletor[2][1] = 0;
				rp2.coletor[2][2] = 0;
				recursos.ocupado[rp2.ocupadox[2]][rp2.ocupadoy[2]] = 0;
			}
			else
			{
				rp2.tempo[2] --;
			}
		}

		//PLAYER 3

		if (recursos.ocupado[rp3.ocupadox[0]][rp3.ocupadoy[0]] == 3)
		{
			if (rp3.tempo[0] == 0)
			{
				rp3.alimento = rp3.alimento + rp3.coleta[0][0];
				rp3.madeira = rp3.madeira + rp3.coleta[0][1];
				rp3.pedra = rp3.pedra + rp3.coleta[0][2];
				rp3.hab[0] = rp3.hab[0] + rp3.coletor[0][0];
				rp3.hab[1] = rp3.hab[1] + rp3.coletor[0][1];
				rp3.hab[2] = rp3.hab[2] + rp3.coletor[0][2];
				rp3.coletor[0][0] = 0;
				rp3.coletor[0][1] = 0;
				rp3.coletor[0][2] = 0;
				recursos.ocupado[rp3.ocupadox[0]][rp3.ocupadoy[0]] = 0;
			}
			else
			{
				rp3.tempo[0] --;
			}
		}
		if (recursos.ocupado[rp3.ocupadox[1]][rp3.ocupadoy[1]] == 3)
		{
			if (rp3.tempo[1] == 0)
			{
				rp3.alimento = rp3.alimento + rp3.coleta[1][0];
				rp3.madeira = rp3.madeira + rp3.coleta[1][1];
				rp3.pedra = rp3.pedra + rp3.coleta[1][2];
				rp3.hab[0] = rp3.hab[0] + rp3.coletor[1][0];
				rp3.hab[1] = rp3.hab[1] + rp3.coletor[1][1];
				rp3.hab[2] = rp3.hab[2] + rp3.coletor[1][2];
				rp3.coletor[1][0] = 0;
				rp3.coletor[1][1] = 0;
				rp3.coletor[1][2] = 0;
				recursos.ocupado[rp3.ocupadox[1]][rp3.ocupadoy[1]] = 0;
			}
			else
			{
				rp3.tempo[1] --;
			}
		}
		if (recursos.ocupado[rp3.ocupadox[2]][rp3.ocupadoy[2]] == 3)
		{
			if (rp3.tempo[2] == 0)
			{
				rp3.alimento = rp3.alimento + rp3.coleta[2][0];
				rp3.madeira = rp3.madeira + rp3.coleta[2][1];
				rp3.pedra = rp3.pedra + rp3.coleta[2][2];
				rp3.hab[0] = rp3.hab[0] + rp3.coletor[2][0];
				rp3.hab[1] = rp3.hab[1] + rp3.coletor[2][1];
				rp3.hab[2] = rp3.hab[2] + rp3.coletor[2][2];
				rp3.coletor[2][0] = 0;
				rp3.coletor[2][1] = 0;
				rp3.coletor[2][2] = 0;
				recursos.ocupado[rp3.ocupadox[2]][rp3.ocupadoy[2]] = 0;
			}
			else
			{
				rp3.tempo[2] --;
			}
		}

		//PLAYER 4

		if (recursos.ocupado[rp4.ocupadox[0]][rp4.ocupadoy[0]] == 4)
		{
			if (rp4.tempo[0] == 0)
			{
				rp4.alimento = rp4.alimento + rp4.coleta[0][0];
				rp4.madeira = rp4.madeira + rp4.coleta[0][1];
				rp4.pedra = rp4.pedra + rp4.coleta[0][2];
				rp4.hab[0] = rp4.hab[0] + rp4.coletor[0][0];
				rp4.hab[1] = rp4.hab[1] + rp4.coletor[0][1];
				rp4.hab[2] = rp4.hab[2] + rp4.coletor[0][2];
				rp4.coletor[0][0] = 0;
				rp4.coletor[0][1] = 0;
				rp4.coletor[0][2] = 0;
				recursos.ocupado[rp4.ocupadox[0]][rp4.ocupadoy[0]] = 0;
			}
			else
			{
				rp4.tempo[0] --;
			}
		}
		if (recursos.ocupado[rp4.ocupadox[1]][rp4.ocupadoy[1]] == 4)
		{
			if (rp4.tempo[1] == 0)
			{
				rp4.alimento = rp4.alimento + rp4.coleta[1][0];
				rp4.madeira = rp4.madeira + rp4.coleta[1][1];
				rp4.pedra = rp4.pedra + rp4.coleta[1][2];
				rp4.hab[0] = rp4.hab[0] + rp4.coletor[1][0];
				rp4.hab[1] = rp4.hab[1] + rp4.coletor[1][1];
				rp4.hab[2] = rp4.hab[2] + rp4.coletor[1][2];
				rp4.coletor[1][0] = 0;
				rp4.coletor[1][1] = 0;
				rp4.coletor[1][2] = 0;
				recursos.ocupado[rp4.ocupadox[1]][rp4.ocupadoy[1]] = 0;
			}
			else
			{
				rp4.tempo[1] --;
			}
		}
		if (recursos.ocupado[rp4.ocupadox[2]][rp4.ocupadoy[2]] == 4)
		{
			if (rp4.tempo[2] == 0)
			{
				rp4.alimento = rp4.alimento + rp4.coleta[2][0];
				rp4.madeira = rp4.madeira + rp4.coleta[2][1];
				rp4.pedra = rp4.pedra + rp4.coleta[2][2];
				rp4.hab[0] = rp4.hab[0] + rp4.coletor[2][0];
				rp4.hab[1] = rp4.hab[1] + rp4.coletor[2][1];
				rp4.hab[2] = rp4.hab[2] + rp4.coletor[2][2];
				rp4.coletor[2][0] = 0;
				rp4.coletor[2][1] = 0;
				rp4.coletor[2][2] = 0;
				recursos.ocupado[rp4.ocupadox[2]][rp4.ocupadoy[2]] = 0;
			}
			else
			{
				rp4.tempo[2] --;
			}
		}

		vez = 1;

		if (vivo[0] == false)
		{
			system("cls");
			printf("Player 1 está morto!!\n");
			printf("Pressione qualquer tecla para ir ao próximo player\n");
			system("pause");
		}
		else
		{
			while (vez == 1)
			{
				menu(&rp1.alimento, &rp1.madeira, &rp1.pedra, &rp1.tempo[0], &rp1.coletor[0][0], &rp1.coleta[0][0], &vez, &x1, &y1, &rp1.ct1.quartel, &rp1.ct1.templo, &rp1.ct1.muralha, &rp1.hab[0], &rp1.ocupadox[0], &rp1.ocupadoy[0], &rp1.ep1.tipo[0], &rp1.ep1.atq, &rp1.ep1.def, &rp1.ep1.ex[0]);

			}
		}

		vez = 2;
		if (vivo[1] == false)
		{
			system("cls");
			printf("Player 2 está morto!!\n");
			printf("Pressione qualquer tecla para ir ao próximo player\n");
			system("pause");
		}
		else
		{
			while (vez == 2)
			{
				menu(&rp2.alimento, &rp2.madeira, &rp2.pedra, &rp2.tempo[0], &rp2.coletor[0][0], &rp2.coleta[0][0], &vez, &x2, &y2, &rp2.ct2.quartel, &rp2.ct2.templo, &rp2.ct2.muralha, &rp2.hab[0], &rp2.ocupadox[0], &rp2.ocupadoy[0], &rp2.ep2.tipo[0], &rp2.ep2.atq, &rp2.ep2.def, &rp2.ep2.ex[0]);

			}
		}
		if (qtp > 2)
		{
			vez = 3;
			if (vivo[2] == false)
			{
				system("cls");
				printf("Player 3 está morto!!\n");
				printf("Pressione qualquer tecla para ir ao próximo player\n");
				system("pause");
			}
			else
			{
				while (vez == 3)
				{
					menu(&rp3.alimento, &rp3.madeira, &rp3.pedra, &rp3.tempo[0], &rp3.coletor[0][0], &rp3.coleta[0][0], &vez, &x3, &y3, &rp3.ct3.quartel, &rp3.ct3.templo, &rp3.ct3.muralha, &rp3.hab[0], &rp3.ocupadox[0], &rp3.ocupadoy[0], &rp3.ep3.tipo[0], &rp3.ep3.atq, &rp3.ep3.def, &rp3.ep3.ex[0]);

				}
			}
			if (qtp > 3)
			{
				vez = 4;
				if (vivo[3] == false)
				{
					system("cls");
					printf("Player 4 está morto!!\n");
					printf("Pressione qualquer tecla para ir ao próximo player\n");
					system("pause");
				}
				else
				{
					while (vez == 4)
					{
						menu(&rp4.alimento, &rp4.madeira, &rp4.pedra, &rp4.tempo[0], &rp4.coletor[0][0], &rp4.coleta[0][0], &vez, &x4, &y4, &rp4.ct4.quartel, &rp4.ct4.templo, &rp4.ct4.muralha, &rp4.hab[0], &rp4.ocupadox[0], &rp4.ocupadoy[0], &rp4.ep4.tipo[0], &rp4.ep4.atq, &rp4.ep4.def, &rp4.ep4.ex[0]);

					}
				}
			}
		}
		turno++; // Todas as funçoes deve retornar pra cá no final, para podermos contar mais um turno e retornar ao menu;
	}

	printf("\n\n ------------ O JOGO ACABOU ------------\n\n");
	system("Pause");
	return 0;
}
