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

int main () {

  setlocale(LC_ALL, "Portuguese");

  Residencia casas[MAX_CASAS] = {0};
  int quantidadeCasas = 0;
  int opcao;
  
  do {
    menu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch (opcao) {
    case 1:
      cadastrarCasa(casas, &quantidadeCasas);
      fflush(stdin);
      break;
    case 0:
      printf("Encerrando programa... \n");
      fflush(stdin);
      break;
    
    default:
      printf("Opção invalida! Tente novamente");
      break;
    }
  } while (opcao != 0);
};

void menu() {
  printf("\nMenu de Opções\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima da média\n");
  printf("4 - Exibir casas abaixo da média\n");
  printf("0 - Sair\n");
};

void cadastrarCasa(Residencia casas[], int *quantidade) {
    if (*quantidade >= MAX_CASAS) {
        printf("Capacidade máxima de casas atingida!\n");
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