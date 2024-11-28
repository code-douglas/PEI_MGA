#include <stdio.h>
#include <locale.h>
#include <string.h>

// Define o n�mero m�ximo de resid�ncias que podem ser registradas no programa.
#define MAX_CASAS 100

// Define a quantidade de meses considerados para o consumo mensal (um ano inteiro).
#define MESES 12

// Define o limite de consumo permitido (em litros, quilowatts ou outra unidade relevante)
// para determinar se uma resid�ncia excedeu ou n�o o consumo estipulado.
#define LIMITE_CONSUMO 15.0

// Define a estrutura Residencia, que armazena informa��es sobre uma resid�ncia,
// incluindo um ID �nico, o nome do morador respons�vel, a quantidade de moradores
// e um vetor com o consumo mensal de �gua ou energia el�trica ao longo dos meses.
typedef struct
{
  int id;               // ID unico
  char morador[50];     // Morador responsavel
  int moradores;        // Quantidade de moradores
  float consumo[MESES]; // Consumo mensal
} Residencia;

// Exibe as op��es dispon�veis no programa, permitindo ao usu�rio navegar pelas funcionalidades do programa
void menu();

// Adiciona uma nova resid�ncia ao array de resid�ncias.
// Recebe o array de estruturas `casas` e um ponteiro para a vari�vel que controla a quantidade
// atual de resid�ncias cadastradas, atualizando-a conforme o cadastro de im�veis na utiliza��o do programa.
void cadastrarCasa(Residencia casas[], int *quantidade);

// Permite registrar o consumo mensal de uma resid�ncia espec�fica.
// Recebe o array de resid�ncias `casas` e o ponteiro para a quantidade de resid�ncias cadastradas,
// garantindo que o consumo seja associado � resid�ncia correta.
void registrarConsumoMensal(Residencia casas[], int *quantidade);

int main()
{
  // Seta o idioma do programa em Portugu�s
  setlocale(LC_ALL, "Portuguese");

  // Declara e inicializa um array de estruturas `Residencia` com capacidade para armazenar at� `MAX_CASAS` resid�ncias.
  // O inicializador `{0}` garante que todos os campos das estruturas no array sejam inicializados com valores padr�o:
  // IDs e inteiros como 0, strings vazias (morador), e valores de consumo como 0.0.
  Residencia casas[MAX_CASAS] = {0};

  // Vari�vel que armazena a quantidade atual de resid�ncias cadastradas no programa.
  // Inicializada com 0, pois nenhuma casa est� cadastrada no in�cio.
  int quantidadeCasas = 0;

  // Vari�vel usada para armazenar a op��o selecionada pelo usu�rio no menu do programa.
  int opcao;

  // Estrutura principal de controle do programa usando um la�o `do-while`.
  // O la�o garante que o menu seja exibido pelo menos uma vez e continua rodando
  // enquanto a op��o selecionada pelo usu�rio (`opcao`) for diferente de 0.

  do
  {
    menu();
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    // O `fflush(stdin)` � usado para limpar o buffer de entrada ap�s o uso do `scanf`
    fflush(stdin);

    switch (opcao)
    {
    case 1:
      cadastrarCasa(casas, &quantidadeCasas);
      fflush(stdin);
      break;
    case 2:
      registrarConsumoMensal(casas, &quantidadeCasas);
      break;
    case 0:
      printf("Encerrando programa... \n");
      fflush(stdin);
      break;
    default:
      printf("Op��o inv�lida! Tente novamente");
      break;
    }
  } while (opcao != 0);
};

// Fun��o que exibe as op��es disponiveis no menu

void menu()
{
  printf("\nMenu de Op��es\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima da m�dia\n");
  printf("4 - Exibir casas abaixo da m�dia\n");
  printf("0 - Sair\n");
};

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  // Valida��o para garantir que a quantidade de casas cadastradas n�o seja ultrapassada
  if (*quantidade >= MAX_CASAS)
  {
    printf("Capacidade m�xima de casas atingida!\n");
    return;
  }

  // Este bloco de c�digo coleta o ID �nico de uma nova resid�ncia a ser cadastrada.
  // Ele declara uma vari�vel tempor�ria `novaCasa` do tipo `Residencia`,
  // exibe uma mensagem solicitando o ID ao usu�rio, armazena o valor inserido no campo `id`

  Residencia novaCasa;
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id);
  fflush(stdin);

  // Este bloco coleta o nome do morador principal da nova resid�ncia.
  // Ele exibe uma mensagem solicitando o nome, limpa o buffer de entrada com `fflush(stdin)`,
  printf("Digite o nome do morador principal: ");
  fflush(stdin);
  fgets(novaCasa.morador, 50, stdin);
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0';

  // Este bloco coleta a quantidade de moradores da nova resid�ncia.
  // Ele exibe uma mensagem solicitando o nome, limpa o buffer de entrada com `fflush(stdin)`,
  printf("Digite a quantidade de moradores: ");
  fflush(stdin);
  scanf("%d", &novaCasa.moradores);

  // Este bloco inicializa o vetor `consumo` da estrutura `novaCasa`,
  // que armazena os consumos mensais da resid�ncia.
  for (int i = 0; i < MESES; i++)
  {
    novaCasa.consumo[i] = 0.0;
  }

  // Este bloco adiciona a nova resid�ncia ao array `casas` na posi��o indicada pela vari�vel `quantidade`.
  // O valor de `novaCasa` � atribu�do � posi��o correspondente no array, e ent�o a quantidade de casas cadastradas
  casas[*quantidade] = novaCasa;
  (*quantidade)++;
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int *quantidade)
{
  // Define as variaveis ID, MES, CONSUMO
  int id, mes;
  float consumo;
  // Solicita o ID do im�vel que ter� o consumo registrado
  printf("Digite o ID da casa: ");
  scanf("%d", &id);
  fflush(stdin);

  int encontrada = 0;
  // Este bloco de c�digo busca uma resid�ncia pelo seu ID no array `casas`.
  for (int i = 0; i < *quantidade; i++)
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o m�s (1-12): ");
      scanf("%d", &mes);

      if (mes < 1 || mes > 12)
      {
        // Tratativa de erro caso o m�s digitado n�o esteja entre 1-12
        printf("M�s inv�lido! Tente novamente.\n");
        return;
      }
      // Solicita o consumo que ser� atribuido ao im�vel com o ID solicitado previamente
      printf("Digite o consumo em metros c�bicos: ");
      scanf("%f", &consumo);
      casas[i].consumo[mes - 1] = consumo;
      printf("Consumo registrado com sucesso!\n");
    }
  }
  // Tratativa para caso o ID nao existe ou seja digitado de forma incorreta
  if (!encontrada)
  {
    printf("Casa com ID %d n�o encontrada.\n", id);
  }
}
