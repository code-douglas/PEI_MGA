#include <stdio.h>  // Biblioteca para entrada e sa�da padr�o
#include <locale.h> // Biblioteca para configurar localiza��o
#include <string.h> // Biblioteca para manipula��o de strings

#define MAX_CASAS 100       // N�mero m�ximo de casas que podem ser cadastradas
#define MESES 12            // N�mero de meses no ano
#define LIMITE_CONSUMO 15.0 // Limite recomendado de consumo mensal em m�

typedef struct // Estrutura que define uma resid�ncia
{
  int id;               // ID �nico da resid�ncia
  char morador[50];     // Nome do morador principal
  int moradores;        // N�mero de moradores na casa
  float consumo[MESES]; // Consumo mensal de �gua em m�
} Residencia;

void menu();                                                     // Exibe o menu de op��es
void cadastrarCasa(Residencia casas[], int *quantidade);         // Cadastra uma nova casa
void registrarConsumoMensal(Residencia casas[], int quantidade); // Registra consumo mensal de uma casa
void exibirCasasAcimaMedia(Residencia casas[], int quantidade);  // Mostra casas com consumo acima do limite
void exibirCasasAbaixoMedia(Residencia casas[], int quantidade); // Mostra casas com consumo abaixo do limite

int main()
{
  setlocale(LC_ALL, "Portuguese"); // Configura localiza��o para o idioma portugu�s
  Residencia casas[MAX_CASAS];     // Array para armazenar casas cadastradas
  int quantidadeCasas = 0;         // Contador de casas cadastradas

  for (int i = 0; i < MAX_CASAS; i++) // Inicializa os dados de todas as casas
  {
    casas[i].id = 0;
    casas[i].moradores = 0;
    strcpy(casas[i].morador, "");
    for (int j = 0; j < MESES; j++)
    {
      casas[i].consumo[j] = 0.0;
    }
  }

  int opcao; // Vari�vel para armazenar a escolha do usu�rio no menu
  do
  {
    menu(); // Exibe o menu de op��es
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao); // L� a op��o escolhida pelo usu�rio
    fflush(stdin);       // Limpa o buffer de entrada

    switch (opcao) // Executa a a��o com base na op��o escolhida
    {
    case 1:
      cadastrarCasa(casas, &quantidadeCasas); // Cadastra uma nova casa
      fflush(stdin);
      break;
    case 2:
      registrarConsumoMensal(casas, quantidadeCasas); // Registra consumo mensal
      fflush(stdin);
      break;
    case 3:
      exibirCasasAcimaMedia(casas, quantidadeCasas); // Exibe casas com consumo acima do limite
      fflush(stdin);
      break;
    case 4:
      exibirCasasAbaixoMedia(casas, quantidadeCasas); // Exibe casas com consumo abaixo do limite
      fflush(stdin);
      break;
    case 0:
      printf("Encerrando programa...\n"); // Encerra o programa
      break;
    default:
      printf("Op��o inv�lida! Tente novamente\n"); // Trata op��es inv�lidas
      break;
    }
  } while (opcao != 0); // Continua at� que o usu�rio escolha sair
}

void menu()
{
  printf("\nMenu de Op��es\n"); // Exibe as op��es dispon�veis no menu
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima do limite de consumo\n");
  printf("4 - Exibir casas abaixo da m�dia\n");
  printf("0 - Sair\n");
}

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  if (*quantidade >= MAX_CASAS) // Verifica se a capacidade m�xima foi atingida
  {
    printf("Capacidade m�xima de casas atingida!\n");
    return;
  }

  Residencia novaCasa; // Cria uma nova casa para cadastrar
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id); // L� o ID da casa
  fflush(stdin);

  printf("Digite o nome do morador principal: ");
  fgets(novaCasa.morador, 50, stdin);                       // L� o nome do morador principal
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0'; // Remove o caractere de nova linha

  printf("Digite a quantidade de moradores: ");
  scanf("%d", &novaCasa.moradores); // L� a quantidade de moradores

  for (int i = 0; i < MESES; i++) // Inicializa o consumo mensal como zero
  {
    novaCasa.consumo[i] = 0.0;
  }

  casas[*quantidade] = novaCasa; // Adiciona a nova casa ao array de casas
  (*quantidade)++;               // Incrementa o contador de casas
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int quantidade)
{
  int id, mes;
  float consumo;
  printf("Digite o ID da casa: ");
  scanf("%d", &id); // L� o ID da casa para registro de consumo

  int encontrada = 0;
  for (int i = 0; i < quantidade; i++) // Procura pela casa com o ID informado
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o m�s (1-12): ");
      scanf("%d", &mes); // L� o m�s do consumo

      if (mes < 1 || mes > 12) // Valida o m�s informado
      {
        printf("M�s inv�lido! Tente novamente.\n");
        return;
      }

      printf("Digite o consumo em metros c�bicos: ");
      scanf("%f", &consumo); // L� o valor do consumo

      if (consumo > LIMITE_CONSUMO) // Exibe aviso caso o consumo exceda o limite
      {
        printf("Aten��o: o consumo informado (%.2f) excede o limite recomendado de %.2f.\n", consumo, LIMITE_CONSUMO);
      }

      casas[i].consumo[mes - 1] = consumo; // Registra o consumo no m�s indicado
      printf("Consumo registrado com sucesso!\n");
      return;
    }
  }

  if (!encontrada) // Informa caso o ID n�o seja encontrado
  {
    printf("Casa com ID %d n�o encontrada.\n", id);
  }
}

void exibirCasasAcimaMedia(Residencia casas[], int quantidade)
{
  printf("\nResid�ncias com consumo mensal acima do limite de %.2f m�:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++) // Percorre todas as casas
  {
    for (int j = 0; j < MESES; j++) // Verifica o consumo de cada m�s
    {
      if (casas[i].consumo[j] > LIMITE_CONSUMO) // Verifica se o consumo est� acima do limite
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | M�s: %d | Consumo: %.2f m�\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
      }
    }
  }

  if (!encontrou) // Informa caso nenhuma casa tenha consumo acima do limite
  {
    printf("Nenhuma resid�ncia com consumo mensal acima do limite de %.2f m�.\n", LIMITE_CONSUMO);
  }
}

void exibirCasasAbaixoMedia(Residencia casas[], int quantidade)
{
  printf("\nResid�ncias com consumo mensal abaixo do limite de %.2f m�:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++) // Percorre todas as casas
  {
    for (int j = 0; j < MESES; j++) // Verifica o consumo de cada m�s
    {
      if (casas[i].consumo[j] < LIMITE_CONSUMO) // Verifica se o consumo est� abaixo do limite
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | M�s: %d | Consumo: %.2f m�\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
        break; // Exibe apenas uma entrada por casa
      }
    }
  }

  if (!encontrou) // Informa caso nenhuma casa tenha consumo abaixo do limite
  {
    printf("Nenhuma resid�ncia com consumo mensal abaixo do limite de %.2f m�.\n", LIMITE_CONSUMO);
  }
}
