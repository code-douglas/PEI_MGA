#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_CASAS 100
#define MESES 12
#define LIMITE_CONSUMO 15.0

typedef struct
{
  int id;
  char morador[50];
  int moradores;
  float consumo[MESES];
} Residencia;

void menu();
void cadastrarCasa(Residencia casas[], int *quantidade);
void registrarConsumoMensal(Residencia casas[], int quantidade);
void exibirCasasAcimaMedia(Residencia casas[], int quantidade);
void exibirCasasAbaixoMedia(Residencia casas[], int quantidade);

int main()
{
  setlocale(LC_ALL, "Portuguese");
  Residencia casas[MAX_CASAS];
  int quantidadeCasas = 0;

  for (int i = 0; i < MAX_CASAS; i++)
  {
    casas[i].id = 0;
    casas[i].moradores = 0;
    strcpy(casas[i].morador, "");
    for (int j = 0; j < MESES; j++)
    {
      casas[i].consumo[j] = 0.0;
    }
  }

  int opcao;
  do
  {
    menu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao)
    {
    case 1:
      cadastrarCasa(casas, &quantidadeCasas);
      fflush(stdin);
      break;
    case 2:
      registrarConsumoMensal(casas, quantidadeCasas);
      fflush(stdin);
      break;
    case 3:
      exibirCasasAcimaMedia(casas, quantidadeCasas);
      fflush(stdin);
      break;
    case 4:
      exibirCasasAbaixoMedia(casas, quantidadeCasas);
      fflush(stdin);
      break;
    case 0:
      printf("Encerrando programa...\n");
      break;
    default:
      printf("Opção inválida! Tente novamente\n");
      break;
    }
  } while (opcao != 0);
}

void menu()
{
  printf("\nMenu de Opções\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima do limite de consumo\n");
  printf("4 - Exibir casas abaixo da média\n");
  printf("0 - Sair\n");
}

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  if (*quantidade >= MAX_CASAS)
  {
    printf("Capacidade máxima de casas atingida!\n");
    return;
  }

  Residencia novaCasa;
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id);
  fflush(stdin);

  printf("Digite o nome do morador principal: ");
  fgets(novaCasa.morador, 50, stdin);
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0';

  printf("Digite a quantidade de moradores: ");
  scanf("%d", &novaCasa.moradores);

  for (int i = 0; i < MESES; i++)
  {
    novaCasa.consumo[i] = 0.0;
  }

  casas[*quantidade] = novaCasa;
  (*quantidade)++;
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int quantidade)
{
  int id, mes;
  float consumo;
  printf("Digite o ID da casa: ");
  scanf("%d", &id);

  int encontrada = 0;
  for (int i = 0; i < quantidade; i++)
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o mês (1-12): ");
      scanf("%d", &mes);

      if (mes < 1 || mes > 12)
      {
        printf("Mês inválido! Tente novamente.\n");
        return;
      }

      printf("Digite o consumo em metros cúbicos: ");
      scanf("%f", &consumo);

      if (consumo > LIMITE_CONSUMO)
      {
        printf("Atenção: o consumo informado (%.2f) excede o limite recomendado de %.2f.\n", consumo, LIMITE_CONSUMO);
      }

      casas[i].consumo[mes - 1] = consumo;
      printf("Consumo registrado com sucesso!\n");
      return;
    }
  }

  if (!encontrada)
  {
    printf("Casa com ID %d não encontrada.\n", id);
  }
}

void exibirCasasAcimaMedia(Residencia casas[], int quantidade)
{
  printf("\nResidências com consumo mensal acima do limite de %.2f m³:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++)
  {
    for (int j = 0; j < MESES; j++)
    {
      if (casas[i].consumo[j] > LIMITE_CONSUMO)
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | Mês: %d | Consumo: %.2f m³\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
      }
    }
  }

  if (!encontrou)
  {
    printf("Nenhuma residência com consumo mensal acima do limite de %.2f m³.\n", LIMITE_CONSUMO);
  }
}

void exibirCasasAbaixoMedia(Residencia casas[], int quantidade)
{
  printf("\nResidências com consumo mensal abaixo do limite de %.2f m³:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++)
  {
    for (int j = 0; j < MESES; j++)
    {
      if (casas[i].consumo[j] < LIMITE_CONSUMO)
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | Mês: %d | Consumo: %.2f m³\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
        break;
      }
    }
  }

  if (!encontrou)
  {
    printf("Nenhuma residência com consumo mensal abaixo do limite de %.2f m³.\n", LIMITE_CONSUMO);
  }
}
