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
void registrarConsumoMensal(Residencia casas[], int *quantidade);
void exibirCasasAcimaMedia(Residencia casas[], int quantidade, float media);
void exibirCasasAbaixoMedia(Residencia casas[], int quantidade, float media);

int main()
{
  setlocale(LC_ALL, "Portuguese");
  Residencia casas[MAX_CASAS] = {0};
  int quantidadeCasas = 0;
  int opcao;

  do
  {
    menu();
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);
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
    case 3:
    {
      float media;
      printf("Digite a m�dia desejada: ");
      scanf("%f", &media);
      exibirCasasAcimaMedia(casas, quantidadeCasas, media);
      break;
    }
    case 4:
    {
      float media;
      printf("Digite a m�dia desejada: ");
      scanf("%f", &media);
      exibirCasasAbaixoMedia(casas, quantidadeCasas, media);
      break;
    }
    case 0:
      printf("Encerrando programa... \n");
      fflush(stdin);
      break;
    default:
      printf("Op��o inv�lida! Tente novamente\n");
      break;
    }
  } while (opcao != 0);
}

void menu()
{
  printf("\nMenu de Op��es\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima da m�dia\n");
  printf("4 - Exibir casas abaixo da m�dia\n");
  printf("0 - Sair\n");
}

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  if (*quantidade >= MAX_CASAS)
  {
    printf("Capacidade m�xima de casas atingida!\n");
    return;
  }

  Residencia novaCasa;
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id);
  fflush(stdin);

  printf("Digite o nome do morador principal: ");
  fflush(stdin);
  fgets(novaCasa.morador, 50, stdin);
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0';

  printf("Digite a quantidade de moradores: ");
  fflush(stdin);
  scanf("%d", &novaCasa.moradores);

  for (int i = 0; i < MESES; i++)
  {
    novaCasa.consumo[i] = 0.0;
  }

  casas[*quantidade] = novaCasa;
  (*quantidade)++;
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int *quantidade)
{
  int id, mes;
  float consumo;
  printf("Digite o ID da casa: ");
  scanf("%d", &id);
  fflush(stdin);

  int encontrada = 0;
  for (int i = 0; i < *quantidade; i++)
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o m�s (1-12): ");
      scanf("%d", &mes);

      if (mes < 1 || mes > 12)
      {
        printf("M�s inv�lido! Tente novamente.\n");
        return;
      }

      printf("Digite o consumo em metros c�bicos: ");
      scanf("%f", &consumo);
      if (consumo > LIMITE_CONSUMO)
      {
        printf("Consumo m�ximo permitido � %.2f. Registro ajustado para %.2f.\n", LIMITE_CONSUMO, LIMITE_CONSUMO);
        consumo = LIMITE_CONSUMO;
      }
      casas[i].consumo[mes - 1] = consumo;
      printf("Consumo registrado com sucesso!\n");
      return;
    }
  }

  if (!encontrada)
  {
    printf("Casa com ID %d n�o encontrada.\n", id);
  }
}

void exibirCasasAcimaMedia(Residencia casas[], int quantidade, float media)
{
  printf("\nResid�ncias com consumo acima da m�dia mensal de %.2f m�:\n", media);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++)
  {
    float totalConsumo = 0.0;

    for (int j = 0; j < MESES; j++)
    {
      totalConsumo += casas[i].consumo[j];
    }

    float mediaResidencia = totalConsumo / MESES;

    if (mediaResidencia > media)
    {
      encontrou = 1;
      printf("ID: %d | Morador: %s | Consumo M�dio Anual: %.2f m�\n",
             casas[i].id, casas[i].morador, mediaResidencia);
    }
  }

  if (!encontrou)
  {
    printf("Nenhuma resid�ncia com consumo acima da m�dia especificada.\n");
  }
}

void exibirCasasAbaixoMedia(Residencia casas[], int quantidade, float media)
{
  printf("\nResid�ncias com consumo abaixo ou dentro da m�dia mensal de %.2f m�:\n", media);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++)
  {
    float totalConsumo = 0.0;

    for (int j = 0; j < MESES; j++)
    {
      totalConsumo += casas[i].consumo[j];
    }

    float mediaResidencia = totalConsumo / MESES;

    if (mediaResidencia <= media)
    {
      encontrou = 1;
      printf("ID: %d | Morador: %s | Consumo M�dio Anual: %.2f m�\n",
             casas[i].id, casas[i].morador, mediaResidencia);
    }
  }

  if (!encontrou)
  {
    printf("Nenhuma resid�ncia com consumo abaixo ou dentro da m�dia especificada.\n");
  }
}
