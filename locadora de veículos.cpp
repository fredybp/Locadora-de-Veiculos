/*Nomes: Ana Luisa Bavati e Frederico Bechara De Paola          RAs: 13022165 e 13099965
Opcionais funcionando: (1, 2, 3, 4, 5)
Valor do projeto: 15 pontos*/



#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include <time.h>

#include <cstdlib>
#include <iostream>
#include <windows.h>

enum DOS_COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
};

void gotoxy(int coluna, int linha) // Usar funcao gotoxy onde x é a coluna e y a linha
{
	COORD point;
	point.X = coluna; point.Y = linha;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
//--------------------------------------------------- 
void textcolor(DOS_COLORS iColor) // usar  a funcao textcolor, cor do texto
{
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= iColor);
}

// -------------------------------------------------------------------------
void backcolor(DOS_COLORS iColor) // funcao backcolor , cor de fundoc
{
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x000F;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= (iColor << 4));
}


struct carro
{
	time_t data;

	char marca[50];
	char modelo[50];
	char chassis[50];
	float km;
	struct carro *prox;
};

struct clientes
{
	char nome[50];
	int codigo;
	struct carro *prox_carros_emprestados;
	struct clientes *prox;
};

struct carro *insere_carro(struct carro **car);

struct clientes *insere_cliente(struct clientes *client);


int remove_carro(struct carro **car, int carro_retirar);

int remove_cliente(struct clientes **client, int cliente_retirar, struct clientes **cliente_removido);

void imprimir_carro(struct carro *car);

void imprimir_clientes(struct clientes *client);

struct carro *alugar_carro(struct carro *car, struct clientes *client);

struct carro *devolver_carro(struct carro *car, struct clientes *client);

void imprimir_carros_alugados(struct clientes *client, int codigo_cliente);

int atualizar_carro(struct carro **car, int carro_atualizar);

int atualizar_clientes(struct clientes **client, int cliente_atualizar);

void imprimir_tudo(struct clientes *client);

void imprimir_carro_semposicao(struct carro *car);

void imprimir_clientes_semposicao(struct clientes *client);

time_t lerdata(void);

void navegar_carros(struct carro *car);

void navegar_clientes(struct clientes *client);

void contar_carros_alugados(struct clientes *client);

void cores();

int recuperar_cliente(struct clientes **client, struct clientes **clientes_removidos);

void navegar(struct clientes *client, struct carro *car);

void ler_dados(struct carro **car, struct clientes **client);

void gravar_dados(struct carro *car, struct clientes *client);

void main()
{
	struct carro *car = NULL;
	struct clientes *client = NULL;
	struct carro *car_emprestados = NULL;
	int carro_remover;
	int op_menu;
	int cliente_remover;
	int carro_atualizar;
	int cliente_atualizar;
	struct clientes *clientes_removidos = NULL;
	int codigo_cliente;


	do{
		system("cls");

		printf("------------------------------------------------------------------------------\n");
		printf("                     GERENCIADOR DE UMA LOCADORA DE CARROS                    \n");
		printf("------------------------------------------------------------------------------\n");
		printf("\n\nSelecione uma opcao a baixo:\n");

		printf("1 - Inserir carro \n");
		printf("2 - Remover carro \n");
		printf("3 - Inserir cliente\n");
		printf("4 - Remover Cliente\n");
		printf("5 - Atualizar carro\n");
		printf("6 - Atualizar cliente\n");
		printf("7 - Alugar carro\n");
		printf("8 - Devolver carro\n");
		printf("9 - Imprimir carros alugados por um cliente\n");
		printf("10 - Imprimir a lista de carros disponiveis da Locadora\n");
		printf("11 - Imprimir a lista de todos os clientes com os respectivos carros alocados\n");
		printf("12 - Imprimir a quantidade de carros alugados e o valor da conta de um determinado cliente\n");
		printf("13 - Navegar pelos registros de clientes\n");
		printf("14 - Navegar pelos registros de carros \n");
		printf("15 - Alterar cores do programa \n");
		printf("16 - Recuperacao de clientes ja apagados. \n");
		printf("17 - Ler dados de arquivo \n");
		printf("18 - Gravar dados em arquivo \n");
		printf("99 - Sair do programa\n\n");
		printf("Opcao: ");
		scanf("%d", &op_menu);
		switch (op_menu){
		case 1:
			system("cls"); //Limpar tela;
			printf("-------------------------------------------------------------------------------\n");
			printf("                        Opcao 1 - Inserir carro\n");
			printf("-------------------------------------------------------------------------------\n");
			car = insere_carro(&car);
			imprimir_carro(car);
			break;

		case 2:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                          Opcao 2 - Remover carro\n");
			printf("-------------------------------------------------------------------------------\n");
			if (car == NULL){
				printf("\nNao eh possivel remover nenhum carro!!\n\n");
				system("pause");
			}
			else{
				imprimir_carro(car);
				printf("Digite o numero do carro que deseja remover: ");
				scanf("%d", &carro_remover);
				remove_carro(&car, carro_remover);
			}
			break;


		case 3:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                      Opcao  3 - Inserir cliente\n");
			printf("-------------------------------------------------------------------------------\n");
			client = insere_cliente(client);
			break;

		case 4:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                        Opcao 4 - Remover Cliente\n");
			printf("-------------------------------------------------------------------------------\n");
			imprimir_clientes(client);
			if (client == NULL)
			{
				printf("\nNao eh possivel remover nenhum cliente!!\n\n");
				system("pause");
			}
			else{
				printf("\nDigite a posicao do cliente que deseja remover:\nOpcao: ");
				scanf("%d", &cliente_remover);
				remove_cliente(&client, cliente_remover, &clientes_removidos);
			}
			break;

		case 5:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                          Opcao 5 - Atualizar carro\n");
			printf("-------------------------------------------------------------------------------\n");
			if (car == NULL){
				printf("\nNao ha carros cadastrados!\n\n");
				system("pause");

			}
			else{
				imprimir_carro(car);
				printf("\nDigite o numero do carro que deseja atualizar:\nOpcao: ");
				scanf("%d", &carro_atualizar);

				atualizar_carro(&car, carro_atualizar);
			}
			break;

		case 6:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                      Opcao 6 - Atualizar cliente\n");
			printf("-------------------------------------------------------------------------------\n");
			if (client == NULL){
				printf("\n Nao ha clientes cadastrados!\n\n");
				system("pause");
			}
			else{
				imprimir_clientes(client);
				printf("\nDigite a posicao do cliente que deseja atualizar:\nOpcao: ");
				scanf("%d", &cliente_atualizar);
				atualizar_clientes(&client, cliente_atualizar);
			}
			break;

		case 7:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                        Opcao 7 - Alugar carro\n");
			printf("-------------------------------------------------------------------------------\n");
			car = alugar_carro(car, client);
			break;

		case 8:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                      Opcao 8 - Devolver carro\n");
			printf("-------------------------------------------------------------------------------\n");
			car = devolver_carro(car, client);
			break;

		case 9:
			system("cls");
			printf("------------------------------------------------------------------------------\n");
			printf("           Opcao 9 - Imprimir carros alugados por um cliente\n");
			printf("------------------------------------------------------------------------------\n");


			printf("Qual cliente deseja mostrar os carros alugados?");

			imprimir_clientes_semposicao(client);

			printf("\nResposta (codigo): ");
			scanf("%i", &codigo_cliente);

			imprimir_carros_alugados(client, codigo_cliente);
			break;


		case 10:
			system("cls"); //Limpar tela;
			printf("------------------------------------------------------------------------------\n");
			printf("       Opcao 10 - Imprimir a lista de carros disponíveis da Locadora          \n");
			printf("------------------------------------------------------------------------------\n");
			imprimir_carro(car);
			printf("\n");
			system("pause");
			break;

		case 11:
			system("cls"); //Limpar tela;
			printf("-------------------------------------------------------------------------------\n");
			printf("     Opcao 11 - Imprimir a lista de todos os clientes com os respectivos       \n");
			printf("                               carros alocados\n");
			printf("-------------------------------------------------------------------------------\n");
			imprimir_tudo(client);
			break;

		case 12:
			system("cls"); //Limpar tela;
			printf("-------------------------------------------------------------------------------\n");
			printf("     Opcao 12 -   Imprimir a quantidade de carros alugados e o valor da        \n");
			printf("                         conta de um determinado cliente\n");
			printf("-------------------------------------------------------------------------------\n");
			contar_carros_alugados(client);
			break;


		case 13:
			system("cls");

			printf("-------------------------------------------------------------------------------\n");
			printf("              Opcao 13 - Navegar pelos registros de clientes                   \n");
			printf("-------------------------------------------------------------------------------\n");
			navegar_clientes(client);
			break;

		case 14:
			system("cls");

			printf("-------------------------------------------------------------------------------\n");
			printf("              Opcao 14 - Navegar pelos registros de carros                     \n");
			printf("-------------------------------------------------------------------------------\n");
			navegar_carros(car);
			break;

		case 15:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                     Opcao 15 - Alterar Cores do Programa                      \n");
			printf("-------------------------------------------------------------------------------\n");
			cores();

			break;

		case 16:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("               Opcao 16 - Recuperacao de clientes ja apagados.                 \n");
			printf("-------------------------------------------------------------------------------\n");
			imprimir_clientes_semposicao(clientes_removidos);
			recuperar_cliente(&client, &clientes_removidos);

			break;

		case 17:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                          Opcao 17 - Ler dados de arquivo                      \n");
			printf("-------------------------------------------------------------------------------\n");
			ler_dados(&car, &client);

			break;

		case 18:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                          Opcao 17 - Gravar dados de arquivo                   \n");
			printf("-------------------------------------------------------------------------------\n");
			gravar_dados(car, client);

			break;


		case 99:
			system("cls");
			printf("-------------------------------------------------------------------------------\n");
			printf("                          Opcao 99 - Sair do Programa                          \n");
			printf("-------------------------------------------------------------------------------\n\n");
			break;

		default:
			printf("Opcao invalida.");
			system("pause");
			break;

		}

	} while (op_menu != 99);
	printf("\n\n");
	system("pause");
}

struct carro *insere_carro(struct carro **car)
{
	struct carro *novo = (struct carro *)malloc(sizeof(struct carro));
	struct carro *aux = *car;

	if (!novo)
	{
		printf("Erro");
	}
	else
	{

		novo->data = lerdata();
		printf("Digite a marca: ");
		fflush(stdin);
		gets(novo->marca);
		printf("Digite o modelo: ");
		fflush(stdin);
		gets(novo->modelo);
		printf("Digite o chassis: ");
		fflush(stdin);
		gets(novo->chassis);
		printf("Digite a kilometragem: ");
		scanf("%f", &novo->km);
	}

	for (aux = *car; aux != NULL; aux = aux->prox)
	{
		if (strcmp(aux->chassis, novo->chassis) == 0)
		{
			system("cls");
			printf("\n Esse carro ja foi cadastrado!\n Digite as informacoes de outro carro:\n\n");

			novo->data = lerdata();
			printf("Digite a marca: ");
			fflush(stdin);
			gets(novo->marca);
			printf("Digite o modelo: ");
			fflush(stdin);
			gets(novo->modelo);
			printf("Digite o chassis: ");
			fflush(stdin);
			gets(novo->chassis);
			printf("Digite a kilometragem: ");
			scanf("%f", &novo->km);

		}


	}

	novo->prox = (*car);
	(*car) = novo;
	return novo;
}
void imprimir_carro(struct carro *car){
	struct carro *aux = car;
	int i = 1;


	int y2 = 5;
	int y3 = 5;

	int x2 = 8;
	int x3 = 38;

	if (aux == NULL)
	{
		printf("\n           Lista De Carros Vazia!!!           \n\n");

	}

	else{
		for (aux = car; aux != NULL; aux = aux->prox){

			if (i % 2 == 0)
			{
				gotoxy(x3, y3);
				printf("Carro    %d \n", i);
				gotoxy(x3, y3 + 1);
				printf("Marca:   %s \n", aux->marca);
				gotoxy(x3, y3 + 2);
				printf("Modelo:  %s \n", aux->modelo);
				gotoxy(x3, y3 + 3);
				printf("Chassis: %s \n", aux->chassis);

				y3 = y3 + 5;
			}

			else
			{

				gotoxy(x2, y2);
				printf("Carro    %d \n", i);
				gotoxy(x2, y2 + 1);
				printf("Marca:   %s \n", aux->marca);
				gotoxy(x2, y2 + 2);
				printf("Modelo:  %s \n", aux->modelo);
				gotoxy(x2, y2 + 3);
				printf("Chassis: %s \n", aux->chassis);
				y2 = y2 + 5;

			}

			i++;
		}
	}
	x2 = 0;
	y2 = y2 + 3;
	gotoxy(x2, y2);
}
int remove_carro(struct carro **car, int carro_retirar)
{
	struct carro *atual = *car;
	struct carro *anterior = NULL;
	int cont = 1;
	int x = carro_retirar;


	while ((atual != NULL) && (cont < x))
	{
		anterior = atual;
		atual = atual->prox;
		cont++;
	}
	if (atual == NULL)
	{
		printf("\n\n\n  Posicao nao existe!!\n\n");
		system("pause");
		return(0);
	}
	if (anterior != NULL)
	{
		anterior->prox = atual->prox;
	}
	else
	{
		*car = atual->prox;
	}
	free(atual);
	return 1;
}
struct clientes *insere_cliente(struct clientes *client)
{
	struct clientes *novo;
	struct clientes *aux = client;
	novo = (struct clientes *)malloc(sizeof(struct clientes));

	printf("Digite o nome do cliente: ");
	fflush(stdin);
	gets(novo->nome);

	printf("Digite o codigo de cliente: ");
	scanf("%d", &novo->codigo);

	for (aux = client; aux != NULL; aux = aux->prox){

		if (novo->codigo == aux->codigo)
		{
			printf("Codigo em uso!!\n");
			printf("Digite outro codigo para o cliente: ");
			scanf("%d", &novo->codigo);
		}

	}

	novo->prox_carros_emprestados = NULL;
	novo->prox = client;
	return novo;
}
void imprimir_clientes(struct clientes *client)
{
	struct clientes *aux = client;
	int i = 1;
	int y2 = 5;
	int y3 = 5;

	int x2 = 8;
	int x3 = 38;

	if (aux == NULL)
	{
		printf("\n              Lista De Clientes Vazia!!!          \n\n");

	}

	else{

		while (aux != NULL) {
			if (i % 2 == 0)
			{
				gotoxy(x3, y3);
				printf("Posicao: %d \n", i);
				gotoxy(x3, y3 + 1);
				printf("Nome: %s \n", aux->nome);
				gotoxy(x3, y3 + 2);
				printf("Codigo: %d \n", aux->codigo);
				y3 = y3 + 4;
			}

			else
			{
				gotoxy(x2, y2);
				printf("Posicao: %d \n", i);
				gotoxy(x2, y2 + 1);
				printf("Nome: %s \n", aux->nome);
				gotoxy(x2, y2 + 2);
				printf("Codigo: %d \n", aux->codigo);
				y2 = y2 + 4;

			}

			i++;
			aux = aux->prox;
		}
	}
	x2 = 0;
	y2 = y2 + 2;
	gotoxy(x2, y2);
}
struct carro *alugar_carro(struct carro *car, struct clientes *client)
{
	struct carro *alugado;
	struct carro *alugado_anterior;
	struct clientes *cliente_aux;
	int cliente_escolhido;
	char carro_escolhido[50];

	printf(" Qual cliente alugou um carro?\n");
	imprimir_clientes_semposicao(client);
	printf(" Resposta (codigo do cliente): ");
	scanf("%i", &cliente_escolhido);

	system("cls");
	printf("\n Qual dos carros o cliente alugou?\n");
	imprimir_carro_semposicao(car);
	printf(" Resposta (chassis): ");
	fflush(stdin);
	gets(carro_escolhido);

	alugado_anterior = NULL;

	for (alugado = car; alugado != NULL; alugado = alugado->prox) {
		if (strcmp(alugado->chassis, carro_escolhido) == 0) {
			break;
		}
		alugado_anterior = alugado;
	}
	if (alugado != NULL) {
		for (cliente_aux = client; cliente_aux != NULL; cliente_aux = cliente_aux->prox) {
			if (cliente_aux->codigo == cliente_escolhido) {
				break;
			}
		}
		if (cliente_aux != NULL) {

			if (alugado_anterior != NULL) {
				alugado_anterior->prox = alugado->prox;
			}
			else {
				car = alugado->prox;
			}
			printf("\nDigite a data que o carro que o carro esta sendo alugado: \n\n");
			alugado->data = lerdata();
			alugado->prox = cliente_aux->prox_carros_emprestados;
			cliente_aux->prox_carros_emprestados = alugado;
		}
		else {
			printf("Cliente nao encontrado: %d\n", cliente_escolhido);
		}
	}
	else {
		printf("Nao existe carro com o chassis %s\n", carro_escolhido);
	}
	return car;


}
void imprimir_carros_alugados(struct clientes *client, int codigo_cliente) {

	struct clientes *aux = client;
	struct carro *atual;
	atual = NULL;

	if (aux == NULL)
	{
		printf("\n               Lista De Carros Vazia!!!           \n\n");

	}

	else{




		for (aux = client; aux != NULL; aux = aux->prox) {
			if (aux->codigo == codigo_cliente) {
				atual = aux->prox_carros_emprestados;
				break;
			}
		}

		system("cls");

		printf("\n Carros alocados pelo cliente %i\n", aux->codigo);


		if (atual != NULL)
		{
			while (atual != NULL)
			{
				printf("\nMarca: %s\n", atual->marca);
				printf("Modelo: %s\n", atual->modelo);
				printf("Chassis: %s\n", atual->chassis);

				atual = atual->prox;
			}
		}
		else
		{
			printf("Nenhum carro alugado!\n");
		}

	}
	system("pause");
}

int remove_cliente(struct clientes **client, int cliente_retirar, struct clientes **cliente_removido)
{
	struct clientes *atual = *client;
	struct clientes *anterior = NULL;
	int cont = 1;



	while ((atual != NULL) && (cont < cliente_retirar))
	{
		anterior = atual;
		atual = atual->prox;
		cont++;
	}
	if (atual == NULL)
	{
		printf("\n Cliente nao existe!! \n\n");
		system("pause");
		return(0);

	}
	if (atual->prox_carros_emprestados != NULL)
	{
		system("cls");
		printf("\n\n                Nao foi possivel remover o cliente!!\n");
		printf("\n  O cliente possui carros alugados, eh necessario devolve-los primeiro!\n");
		printf("\n\n");
		system("pause");
		return 0;
	}

	else{
		if (anterior != NULL)
		{
			anterior->prox = atual->prox;
		}
		else
		{
			*client = atual->prox;
		}
		atual->prox = *cliente_removido;
		*cliente_removido = atual;
		return 1;
	}

}


int atualizar_carro(struct carro **car, int carro_atualizar)
{
	struct carro *atual = *car;

	int cont = 1;
	int x = carro_atualizar;
	int opcao_alterar;

		while ((atual != NULL) && (cont < x))
		{

			atual = atual->prox;
			cont++;
		}
		if (atual == NULL)
		{

			printf("\nPosicao nao existe\n\n");
			system("pause");
			return(0);
		}
		else
		{
			system("cls");
			gotoxy(5, 5);
			printf(" Digite a opcao que deseja alterar:\n1 - Marca\n2 - Modelo\n3 - Chassi\n4 - Kilometragem\nOpcao:");
			scanf("%d", &opcao_alterar);

			if (opcao_alterar == 1){
				printf("\n Digite a marca: ");
				fflush(stdin);
				gets(atual->marca);
				return 1;
			}
			if (opcao_alterar == 2){
				printf("\n Digite o modelo: ");
				fflush(stdin);
				gets(atual->modelo);
				return 1;
			}
			if (opcao_alterar == 3){
				printf("\n Digite o chassis: ");
				fflush(stdin);
				gets(atual->chassis);
				return 1;
			}
			if (opcao_alterar == 4){
				printf("\n Digite a kilometragem: ");
				scanf("%f", &atual->km);
				return 1;
			}

			else
			{
				printf("Opcao Invalida!\n\n");
				system("pause");
				return 1;
			}
		}
		

	}




int atualizar_clientes(struct clientes **client, int cliente_atualizar)
{
	struct clientes *atual = *client;

	int cont = 1;
	int x = cliente_atualizar;
	int opcao_alterar;

		while ((atual != NULL) && (cont < x))
		{

			atual = atual->prox;
			cont++;
		}
		if (atual == NULL)
		{

			printf("Posicao nao existe\n\n");
			system("pause");
			return(0);
		}
		else
		{
			system("cls");
			printf("\n Digite a opcao que deseja alterar:\n1 - Nome\n2 - Codigo:\n\nOpcao:");
			scanf("%d", &opcao_alterar);
			if (opcao_alterar == 1){
				printf("Digite o nome: ");
				fflush(stdin);
				gets(atual->nome);
				return 1;
			}
			if (opcao_alterar == 2){

				printf("Digite o codigo: ");
				fflush(stdin);
				scanf("%d", &atual->codigo);
				return 1;
			}

			else
			{
				printf("\nOpcao Invalida!\n");
				system("pause");
				return 1;
			}


		}
		
	}


void contar_carros_alugados(struct clientes *client) {

	struct clientes *aux;
	struct carro *atual;
	int codigo_cliente;
	int i;
	double dias;
	time_t now;
	double valor_diaria;
	double valor_total;

	if (client == NULL){
		printf("\n Nao existem clientes cadastrados!\n\n");
		system("pause");
	}

	else{

		printf("Qual cliente deseja mostrar os carros alugados?");
		imprimir_clientes(client);

		printf("\nResposta (codigo): ");
		scanf("%i", &codigo_cliente);

		atual = NULL;

		for (aux = client; aux != NULL; aux = aux->prox) {
			if (aux->codigo == codigo_cliente) {
				atual = aux->prox_carros_emprestados;
				break;
			}
		}

		i = 0;
		dias = 0;
		now = time(NULL);
		printf("\nNumero de carros alocados pelo cliente %i: ", aux->codigo);
		while (atual != NULL) {
			dias += (double)(difftime(now, atual->data) + 86399) / 86400;   //arrendondamento para o numero de dias.
			i++;
			atual = atual->prox;

		}

		printf("Numero de carros: %i\n", i);
		printf("Diarias: %i\n", dias);

		printf("Quanto 'e o valor da diaria?\nResposta: ");
		scanf("%f", &valor_diaria);

		valor_total = valor_diaria * dias;

		printf("\n\nValor total do cliente %i e: %.2f\n\n", codigo_cliente, valor_total);

		system("pause");
	}
}
time_t lerdata(void) {

	tm data;
	time_t t;

	printf("Digite a data (XX/XX/XXXX): ");
	fflush(stdin);
	scanf("%d/%d/%d", &data.tm_mday, &data.tm_mon, &data.tm_year);
	printf("Digite o horario (XX:XX): ");
	fflush(stdin);
	scanf("%d:%d", &data.tm_hour, &data.tm_min);

	data.tm_year -= 1900;
	data.tm_mon--;

	data.tm_isdst = 0;
	data.tm_sec = 0;
	data.tm_wday = 0;
	data.tm_yday = 0;

	t = mktime(&data);
	return t;
}


struct carro *devolver_carro(struct carro *car, struct clientes *client) {

	struct clientes *cliente_atual;
	struct clientes *cliente_aux;
	struct carro *carro_atual;
	struct carro *carro_anterior;
	char carro_devolver[50];
	int codigo_cliente;
	char tanque_cheio;
	float litro_combustivel;
	float faltando;
	float pagar;

	imprimir_clientes_semposicao(client);
	printf("Digite o codigo do cliente\nCodigo: ");
	scanf("%d", &codigo_cliente);

	imprimir_carros_alugados(client, codigo_cliente);

	printf("Selecione o carro que o cliente deseja devolver\nOpcao(chassis):");
	fflush(stdin);
	gets(carro_devolver);

	cliente_atual = NULL;
	cliente_aux = client;

	carro_atual = car;
	carro_anterior = NULL;

	while (cliente_aux != NULL)
	{
		if (cliente_aux->codigo == codigo_cliente){

			cliente_atual = cliente_aux;
		}

		cliente_aux = cliente_aux->prox;
	}


	if (cliente_atual != NULL)
	{
		carro_atual = cliente_atual->prox_carros_emprestados;
		carro_anterior = NULL;


		while (carro_atual != NULL)
		{
			if (strcmp(carro_atual->chassis, carro_devolver) == 0)
			{
				if (carro_anterior != NULL)
				{
					carro_anterior->prox = carro_atual->prox;
				}
				else
				{
					cliente_atual->prox_carros_emprestados = carro_atual->prox;
				}

				carro_atual->prox = car;
				car = carro_atual;

			}
			carro_anterior = carro_atual;
			carro_atual = carro_atual->prox;

		}
		printf("O tanque do carro esta cheio?\nResposta (S/N): ");
		fflush(stdin);
		scanf("%c", &tanque_cheio);
		do{
			if (tanque_cheio == 's' || tanque_cheio == 'S') {

				printf("So cobre do cliente a diaria.");

				system("pause");

			}
			if (tanque_cheio == 'n' || tanque_cheio == 'N') {

				printf("O tanque nao esta cheio. Quanto esta o litro do combustivel?\nResposta: ");
				scanf("%f", &litro_combustivel);
				printf("\nE quantos litros de combustivel estao faltando no tanque do carro?\nResposta: ");
				scanf("%f", &faltando);
				pagar = faltando * litro_combustivel;
				printf("\n\nO cliente tem que pagar %.2f por nao ter entregado o carro com o tanque cheio!\n", pagar);
				system("pause");
			}
			else {

				printf("Opcao invalida");
				system("pause");
			}

		} while (tanque_cheio != 's' && tanque_cheio != 'S' && tanque_cheio != 'n' && tanque_cheio != 'N');
	}






	else
	{
		printf("Cliente nao encontrado!\n");
	}

	return car;
}

void imprimir_tudo(struct clientes *client)
{
	struct clientes  *aux_cliente = client;
	struct carro  *aux_carro;


	aux_carro = NULL;

	system("cls");

	if (aux_cliente == NULL)
	{

		printf("\n             Lista de Clientes Vazia!!!  \n\n");
		
	}
	else{
		while (aux_cliente != NULL)
		{
			printf("----------------------------------------------------------------------------");
			printf("\n Cliente : %s     Codigo do cliente : %i\n\n", aux_cliente->nome, aux_cliente->codigo);

			if (aux_cliente->prox_carros_emprestados != NULL)
			{
				aux_carro = aux_cliente->prox_carros_emprestados;
				printf("Carros alugados por ele(a): \n");
				while (aux_carro != NULL)
				{

					printf("\n Marca: %s   Modelo: %s   Chassis: %s\n", aux_carro->marca, aux_carro->modelo, aux_carro->chassis);

					aux_carro = aux_carro->prox;
				}
				printf("----------------------------------------------------------------------------");
				printf("\n");
			}
			else
			{
				printf("\n Este cliente nao tem nenhum carro alocado.\n");
				printf("----------------------------------------------------------------------------\n");
			}

			aux_cliente = aux_cliente->prox;

		}
	}
	printf("\n");
	system("pause");
}

void imprimir_carro_semposicao(struct carro *car)
{
	struct carro *aux = car;
	int i = 1;


	int y2 = 5;
	int y3 = 5;

	int x2 = 8;
	int x3 = 38;

	if (aux == NULL)
	{
		printf("\n              Lista de Carros Vazia!!            \n\n");

	}
	else{

		for (aux = car; aux != NULL; aux = aux->prox){

			if (i % 2 == 0)
			{
				gotoxy(x3, y3);
				printf("Marca:   %s \n", aux->marca);
				gotoxy(x3, y3 + 1);
				printf("Modelo:  %s \n", aux->modelo);
				gotoxy(x3, y3 + 2);
				printf("Chassis: %s \n", aux->chassis);

				y3 = y3 + 5;
			}

			else
			{

				gotoxy(x2, y2);
				printf("Marca:   %s \n", aux->marca);
				gotoxy(x2, y2 + 1);
				printf("Modelo:  %s \n", aux->modelo);
				gotoxy(x2, y2 + 2);
				printf("Chassis: %s \n", aux->chassis);
				y2 = y2 + 5;

			}

			i++;
		}
	}
	x2 = 0;
	y2 = y2 + 3;
	gotoxy(x2, y2);
}



void imprimir_clientes_semposicao(struct clientes *client){

	struct clientes *aux = client;
	int i = 1;
	int y2 = 5;
	int y3 = 5;

	int x2 = 8;
	int x3 = 38;

	if (aux == NULL){

		printf("\n             Lista de Clientes Vazia!!!          \n\n");
	}
	else{
		while (aux != NULL) {
			if (i % 2 == 0)
			{
				gotoxy(x3, y3);
				printf("Nome: %s \n", aux->nome);
				gotoxy(x3, y3 + 1);
				printf("Codigo: %d \n", aux->codigo);
				y3 = y3 + 4;
			}

			else
			{
				gotoxy(x2, y2);
				printf("Nome: %s \n", aux->nome);
				gotoxy(x2, y2 + 1);
				printf("Codigo: %d \n", aux->codigo);
				y2 = y2 + 4;

			}

			i++;
			aux = aux->prox;
		}

		x2 = 0;
		y2 = y2 + 2;
		gotoxy(x2, y2);
	}
}




void cores()
{

	char texto = 0;
	char fundo = 0;
	int op_menu;

	printf("Selecione qual das opcoes deseja alterar a cor:\n");
	printf("1 - Alterar a cor do texto\n2 - Alterar a cor de fundo\n");
	scanf("%d", &op_menu);

	if (op_menu == 1)
	{
		system("cls");
		printf("\n--------------- Alterar Cor do Texto --------------------\n\n");

		printf("0 = Preto            8 = Cinza Escuro\n");
		printf("1 = Azul             9 = Azul claro\n");
		printf("2 = Verde            A = Verde claro\n");
		printf("3 = Verde agua       B = Verde - agua claro\n");
		printf("4 = Vermelho         C = Vermelho claro\n");
		printf("5 = Roxo             D = Lilas\n");
		printf("6 = Marron           E = Amarelo claro\n");
		printf("7 = Cinza claro      F = Branco  \n");
		printf("\nSelecione a cor desejada:\n\nOpcao:");
		fflush(stdin);
		scanf("%c", &texto);

		if (texto == '0')
		{
			textcolor(BLACK);
		}
		if (texto == '1')
		{
			textcolor(BLUE);
		}
		if (texto == '2')
		{
			textcolor(GREEN);
		}
		if (texto == '3')
		{
			textcolor(CYAN);
		}
		if (texto == '4')
		{
			textcolor(RED);
		}
		if (texto == '5')
		{
			textcolor(MAGENTA);
		}
		if (texto == '6')
		{
			textcolor(BROWN);
		}
		if (texto == '7')
		{
			textcolor(LIGHT_GRAY);
		}
		if (texto == '8')
		{
			textcolor(DARK_GRAY);
		}
		if (texto == '9')
		{
			textcolor(LIGHT_BLUE);
		}
		if (texto == 'A')
		{
			textcolor(LIGHT_GREEN);
		}
		if (texto == 'B')
		{
			textcolor(LIGHT_CYAN);
		}
		if (texto == 'C')
		{
			textcolor(LIGHT_RED);
		}
		if (texto == 'D')
		{
			textcolor(LIGHT_MAGENTA);
		}
		if (texto == 'E')
		{
			textcolor(YELLOW);
		}
		if (texto == 'F')
		{
			textcolor(WHITE);
		}
		else
		{
			printf("COR INVALIDA!!");

		}

	}
	if (op_menu == 2)
	{
		system("cls");
		printf("\n--------------- Alterar Cor de Fundo --------------------\n\n");

		printf("0 = Preto            8 = Cinza Escuro\n");
		printf("1 = Azul             9 = Azul claro\n");
		printf("2 = Verde            A = Verde claro\n");
		printf("3 = Verde agua       B = Verde - agua claro\n");
		printf("4 = Vermelho         C = Vermelho claro\n");
		printf("5 = Roxo             D = Lilas\n");
		printf("6 = Marron           E = Amarelo claro\n");
		printf("7 = Cinza claro      F = Branco  \n");
		printf("\nSelecione a cor desejada:\n\nOpcao:");
		fflush(stdin);
		scanf("%c", &texto);

		if (texto == '0')
		{
			backcolor(BLACK);
		}
		if (texto == '1')
		{
			backcolor(BLUE);
		}
		if (texto == '2')
		{
			backcolor(GREEN);
		}
		if (texto == '3')
		{
			backcolor(CYAN);
		}
		if (texto == '4')
		{
			backcolor(RED);
		}
		if (texto == '5')
		{
			backcolor(MAGENTA);
		}
		if (texto == '6')
		{
			backcolor(BROWN);
		}
		if (texto == '7')
		{
			backcolor(LIGHT_GRAY);
		}
		if (texto == '8')
		{
			backcolor(DARK_GRAY);
		}
		if (texto == '9')
		{
			backcolor(LIGHT_BLUE);
		}
		if (texto == 'A')
		{
			backcolor(LIGHT_GREEN);
		}
		if (texto == 'B')
		{
			backcolor(LIGHT_CYAN);
		}
		if (texto == 'C')
		{
			backcolor(LIGHT_RED);
		}
		if (texto == 'D')
		{
			backcolor(LIGHT_MAGENTA);
		}
		if (texto == 'E')
		{
			backcolor(YELLOW);
		}
		if (texto == 'F')
		{
			backcolor(WHITE);
		}
		else
		{
			printf("COR INVALIDA!!");

		}
	}





	system("cls");



}


int recuperar_cliente(struct clientes **client, struct clientes **clientes_removidos)
{
	struct clientes *atual;
	struct clientes *anterior;
	int codigo_removido;

	atual = *clientes_removidos;
	anterior = NULL;



	if (*clientes_removidos == NULL)
	{
		printf("\n      Nao foi removido nenhum cliente!!\n\n");

		system("pause");
		return 0;

	}
	else{
		printf("Digite o codigo do cliente removido, que deseja recuperar:\n");
		scanf("%d", &codigo_removido);

		while ((atual != NULL) && (codigo_removido != atual->codigo))
		{
			anterior = atual;
			atual = atual->prox;
		}

		if (atual == NULL) {

			printf("Nao existe cliente removido com esse codigo!\n");
			return 0;

		}
		else {

			if (anterior != NULL)
			{
				anterior->prox = atual->prox;
			}
			else
			{
				*clientes_removidos = atual->prox;
			}
			atual->prox = *client;
			*client = atual;
			return 1;


		}
	}
}


void navegar_carros(struct carro *car)
{
	struct carro *atual;
	struct carro *anterior;
	struct carro *corrente;
	char opcao_carro;



	if (car == NULL)
	{
		printf("Nao existem carro registrados!\n");
		system("pause");
	}
	else {
		printf("\nPara a navegacao pelos registros de carros utilizaremos as teclas A e P do teclado:\n");
		printf("A ira voltar ao carro anterior\n");
		printf("P ira para o proximo carro\n");
		printf("F ira voltar para o menu.\n");


		corrente = car;


		do{
			printf("\nCarro corrente\n");
			printf("Marca: %s\n", corrente->marca);
			printf("Modelo: %s\n", corrente->modelo);
			printf("Chassis: %s\n", corrente->chassis);
			printf("Kilometros: %i\n", corrente->km);


			printf("\n\n");
			printf("Opcao: ");
			fflush(stdin);
			scanf("%c", &opcao_carro);

			if (opcao_carro == 'p' || opcao_carro == 'P') {
				if (corrente->prox != NULL) {
					corrente = corrente->prox;
				}
				else
				{
					printf("\nEste e o ultimo carro.\n");
				}
			}
			else if (opcao_carro == 'a' || opcao_carro == 'A') {

				atual = car;
				anterior = NULL;


				while ((atual != NULL) && (atual != corrente))
				{
					anterior = atual;
					atual = atual->prox;
				}

				if (anterior != NULL) {
					corrente = anterior;
				}
				else {

					printf("\nEste e o primeiro carro.\n");
				}


			}
			else if (opcao_carro != 'f' && opcao_carro != 'F') {
				printf("Opcao %c invalida.\n", opcao_carro);

			}


		} while (opcao_carro != 'f' && opcao_carro != 'F');






	}





}

void navegar_clientes(struct clientes *client)
{
	struct clientes *atual;
	struct clientes *anterior;
	struct clientes *corrente;
	char opcao_cliente;



	if (client == NULL)
	{
		printf("Nao existem clientes registrados!\n");
		system("pause");
	}
	else {
		printf("\nPara a navegacao pelos registros de clientes utilizaremos as teclas A e P do teclado:\n");
		printf("A ira voltar ao cliente anterior\n");
		printf("P ira para o proximo cliente\n");
		printf("F ira voltar para o menu.\n");


		corrente = client;


		do{
			printf("\nCliente corrente\n");
			printf("Nome: %s\n", corrente->nome);
			printf("Codigo: %i\n", corrente->codigo);

			printf("\n\n");
			printf("Opcao: ");
			fflush(stdin);
			scanf("%c", &opcao_cliente);

			if (opcao_cliente == 'p' || opcao_cliente == 'P') {
				if (corrente->prox != NULL) {
					corrente = corrente->prox;
				}
				else
				{
					printf("\nEste e o ultimo cliente.\n");
				}
			}
			else if (opcao_cliente == 'a' || opcao_cliente == 'A') {

				atual = client;
				anterior = NULL;


				while ((atual != NULL) && (atual != corrente))
				{
					anterior = atual;
					atual = atual->prox;
				}

				if (anterior != NULL) {
					corrente = anterior;
				}
				else {

					printf("\nEste e o primeiro cliente.\n");
				}


			}
			else if (opcao_cliente != 'f' && opcao_cliente != 'F') {
				printf("Opcao %c invalida.\n", opcao_cliente);

			}


		} while (opcao_cliente != 'f' && opcao_cliente != 'F');






	}
}

void ler_dados(struct carro **car, struct clientes **client)
{
	FILE *dados;
	struct clientes *atual_cliente;
	struct clientes *anterior_cliente;
	struct carro *atual_carro;
	struct carro *anterior_carro;
	char tipo_dados;
	tm data;

	anterior_cliente = NULL;
	atual_cliente = *client;


	while (atual_cliente != NULL) {

		anterior_cliente = atual_cliente;
		atual_cliente = atual_cliente->prox;
		free(anterior_cliente);

	}

	anterior_carro = NULL;
	atual_carro = *car;


	while (atual_carro != NULL) {

		anterior_carro = atual_carro;
		atual_carro = atual_carro->prox;
		free(anterior_carro);

	}

	atual_carro = NULL;
	atual_cliente = NULL;
	anterior_carro = NULL;
	anterior_cliente = NULL;


	dados = fopen("locadora.txt", "r");
	if (dados == NULL) {
		printf("Erro ao abrir arquivo.");
		return;
	}
	while (!feof(dados)){
		tipo_dados = fgetc(dados);

		if (tipo_dados == '1') {
			atual_carro = (struct carro *) malloc(sizeof(struct carro));
			fscanf(dados, " %s %s %s %f %i/%i/%i %i:%i\n",
				atual_carro->marca,
				atual_carro->modelo,
				atual_carro->chassis,
				&atual_carro->km,
				&data.tm_mday,
				&data.tm_mon,
				&data.tm_year,
				&data.tm_hour,
				&data.tm_min);
			data.tm_year -= 1900;
			data.tm_mon--;
			data.tm_isdst = 0;
			data.tm_sec = 0;
			data.tm_wday = 0;
			data.tm_yday = 0;
			atual_carro->data = mktime(&data);
			atual_carro->prox = anterior_carro;
			anterior_carro = atual_carro;
		}
		else if (tipo_dados == '2') {
			atual_cliente = (struct clientes *) malloc(sizeof(struct clientes));
			fscanf(dados, " %i ", &atual_cliente->codigo);
			fgets(atual_cliente->nome, sizeof(atual_cliente->nome), dados);
			atual_cliente->nome[strlen(atual_cliente->nome) - 1] = '\0';
			atual_cliente->prox_carros_emprestados = NULL;
			atual_cliente->prox = anterior_cliente;
			anterior_cliente = atual_cliente;

		}
		else if (tipo_dados == '3') {
			atual_carro = (struct carro *) malloc(sizeof(struct carro));
			fscanf(dados, " %s %s %s %f %i/%i/%i %i:%i\n",
				atual_carro->marca,
				atual_carro->modelo,
				atual_carro->chassis,
				&atual_carro->km,
				&data.tm_mday,
				&data.tm_mon,
				&data.tm_year,
				&data.tm_hour,
				&data.tm_min);
			data.tm_year -= 1900;
			data.tm_mon--;
			data.tm_isdst = 0;
			data.tm_sec = 0;
			data.tm_wday = 0;
			data.tm_yday = 0;
			atual_carro->data = mktime(&data);
			if (atual_cliente != NULL) {
				atual_carro->prox = atual_cliente->prox_carros_emprestados;
				atual_cliente->prox_carros_emprestados = atual_carro;
			}
			else {

				printf("\nEncontrado carro de cliente sem um cliente!\n");
				free(atual_carro);
				system("pause");

			}
		}
	}

	fclose(dados);


	*client = anterior_cliente;
	*car = anterior_carro;
}

void gravar_dados(struct carro *car, struct clientes *client) {

	FILE *dados;
	tm *data;

	dados = fopen("locadora.txt", "w");
	if (dados == NULL) {

		printf("Erro ao criar o arquivo\n");

	}
	else {

		while (car != NULL) {

			data = localtime(&car->data);

			fprintf(dados, "1 %s %s %s %f %s\n",
				car->marca,
				car->modelo,
				car->chassis,
				car->km,
				asctime(data));

			car = car->prox;
		}

		while (client != NULL) {

			fprintf(dados, "2 %i %s\n", client->codigo, client->nome);
			car = client->prox_carros_emprestados;
			while (car != NULL) {

				data = localtime(&car->data);

				fprintf(dados, "3 %s %s %s %f %s\n",
					car->marca,
					car->modelo,
					car->chassis,
					car->km,
					asctime(data));

				car = car->prox;
			}

			client = client->prox;

		}

		fclose(dados);


	}

}
