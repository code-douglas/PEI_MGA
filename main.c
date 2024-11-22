#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_CASAS 100
#define MESES 12
#define LIMITE_CONSUMO 15.0

typedef struct {
  int id; // ID unico
  char morador[50]; // Morador responsavel
  int moradores; // Quantidade de moradores
  float consumo[MESES]; // Consumo mensal
} Residencia;

void menu();
void cadastrarCasa(Residencia casas[], int *quantidade);
void registrarConsumoMensal(Residencia casas[], int *quantidade);

int main() {

  setlocale(LC_ALL, "Portuguese");

  Residencia casas[MAX_CASAS] = {0};
  int quantidadeCasas = 0;
  int opcao;
  
  do {
    menu();
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
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

void menu() {
  printf("\nMenu de Op��es\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima da m�dia\n");
  printf("4 - Exibir casas abaixo da m�dia\n");
  printf("0 - Sair\n");
};

void cadastrarCasa(Residencia casas[], int *quantidade) {
  if (*quantidade >= MAX_CASAS) {
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

  for (int i = 0; i < MESES; i++) {
    novaCasa.consumo[i] = 0.0;
  }

  casas[*quantidade] = novaCasa;
  (*quantidade)++;
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int *quantidade) {
  int id, mes;
  float consumo;
  printf("Digite o ID da casa: ");
  scanf("%d", &id);
  fflush(stdin);

  int encontrada = 0;
  for(int i = 0; i < *quantidade; i++) {
    if(casas[i].id == id) {
      encontrada = 1;
      printf("Digite o m�s (1-12): ");
      scanf("%d", &mes);

      if (mes < 1 || mes > 12) {
        printf("M�s inv�lido! Tente novamente.\n");
        return;
      }

      printf("Digite o consumo em metros c�bicos: ");
      scanf("%f", &consumo);
      casas[i].consumo[mes - 1] = consumo;
      printf("Consumo registrado com sucesso!\n");
    }
  }

  if (!encontrada) {
    printf("Casa com ID %d n�o encontrada.\n", id);
  }
}
