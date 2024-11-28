#include <stdio.h>
#include <locale.h>
#include <string.h>

// Define o número máximo de residências que podem ser registradas no programa.
#define MAX_CASAS 100

// Define a quantidade de meses considerados para o consumo mensal (um ano inteiro).
#define MESES 12

// Define o limite de consumo permitido (em litros, quilowatts ou outra unidade relevante)
// para determinar se uma residência excedeu ou não o consumo estipulado.
#define LIMITE_CONSUMO 15.0

// Define a estrutura Residencia, que armazena informações sobre uma residência,
// incluindo um ID único, o nome do morador responsável, a quantidade de moradores
// e um vetor com o consumo mensal de água ou energia elétrica ao longo dos meses.
typedef struct
{
  int id;               // ID unico
  char morador[50];     // Morador responsavel
  int moradores;        // Quantidade de moradores
  float consumo[MESES]; // Consumo mensal
} Residencia;

// Exibe as opções disponíveis no programa, permitindo ao usuário navegar pelas funcionalidades do programa
void menu();

// Adiciona uma nova residência ao array de residências.
// Recebe o array de estruturas `casas` e um ponteiro para a variável que controla a quantidade
// atual de residências cadastradas, atualizando-a conforme o cadastro de imóveis na utilização do programa.
void cadastrarCasa(Residencia casas[], int *quantidade);

// Permite registrar o consumo mensal de uma residência específica.
// Recebe o array de residências `casas` e o ponteiro para a quantidade de residências cadastradas,
// garantindo que o consumo seja associado à residência correta.
void registrarConsumoMensal(Residencia casas[], int *quantidade);

int main()
{
  // Seta o idioma do programa em Português
  setlocale(LC_ALL, "Portuguese");

  // Declara e inicializa um array de estruturas `Residencia` com capacidade para armazenar até `MAX_CASAS` residências.
  // O inicializador `{0}` garante que todos os campos das estruturas no array sejam inicializados com valores padrão:
  // IDs e inteiros como 0, strings vazias (morador), e valores de consumo como 0.0.
  Residencia casas[MAX_CASAS] = {0};

  // Variável que armazena a quantidade atual de residências cadastradas no programa.
  // Inicializada com 0, pois nenhuma casa está cadastrada no início.
  int quantidadeCasas = 0;

  // Variável usada para armazenar a opção selecionada pelo usuário no menu do programa.
  int opcao;

  // Estrutura principal de controle do programa usando um laço `do-while`.
  // O laço garante que o menu seja exibido pelo menos uma vez e continua rodando
  // enquanto a opção selecionada pelo usuário (`opcao`) for diferente de 0.

  do
  {
    menu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    // O `fflush(stdin)` é usado para limpar o buffer de entrada após o uso do `scanf`
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
      printf("Opção inválida! Tente novamente");
      break;
    }
  } while (opcao != 0);
};

// Função que exibe as opções disponiveis no menu

void menu()
{
  printf("\nMenu de Opções\n");
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima da média\n");
  printf("4 - Exibir casas abaixo da média\n");
  printf("0 - Sair\n");
};

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  // Validação para garantir que a quantidade de casas cadastradas não seja ultrapassada
  if (*quantidade >= MAX_CASAS)
  {
    printf("Capacidade máxima de casas atingida!\n");
    return;
  }

  // Este bloco de código coleta o ID único de uma nova residência a ser cadastrada.
  // Ele declara uma variável temporária `novaCasa` do tipo `Residencia`,
  // exibe uma mensagem solicitando o ID ao usuário, armazena o valor inserido no campo `id`

  Residencia novaCasa;
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id);
  fflush(stdin);

  // Este bloco coleta o nome do morador principal da nova residência.
  // Ele exibe uma mensagem solicitando o nome, limpa o buffer de entrada com `fflush(stdin)`,
  printf("Digite o nome do morador principal: ");
  fflush(stdin);
  fgets(novaCasa.morador, 50, stdin);
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0';

  // Este bloco coleta a quantidade de moradores da nova residência.
  // Ele exibe uma mensagem solicitando o nome, limpa o buffer de entrada com `fflush(stdin)`,
  printf("Digite a quantidade de moradores: ");
  fflush(stdin);
  scanf("%d", &novaCasa.moradores);

  // Este bloco inicializa o vetor `consumo` da estrutura `novaCasa`,
  // que armazena os consumos mensais da residência.
  for (int i = 0; i < MESES; i++)
  {
    novaCasa.consumo[i] = 0.0;
  }

  // Este bloco adiciona a nova residência ao array `casas` na posição indicada pela variável `quantidade`.
  // O valor de `novaCasa` é atribuído à posição correspondente no array, e então a quantidade de casas cadastradas
  casas[*quantidade] = novaCasa;
  (*quantidade)++;
  printf("Casa cadastrada com sucesso!\n");
}

void registrarConsumoMensal(Residencia casas[], int *quantidade)
{
  // Define as variaveis ID, MES, CONSUMO
  int id, mes;
  float consumo;
  // Solicita o ID do imóvel que terá o consumo registrado
  printf("Digite o ID da casa: ");
  scanf("%d", &id);
  fflush(stdin);

  int encontrada = 0;
  // Este bloco de código busca uma residência pelo seu ID no array `casas`.
  for (int i = 0; i < *quantidade; i++)
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o mês (1-12): ");
      scanf("%d", &mes);

      if (mes < 1 || mes > 12)
      {
        // Tratativa de erro caso o mês digitado não esteja entre 1-12
        printf("Mês inválido! Tente novamente.\n");
        return;
      }
      // Solicita o consumo que será atribuido ao imóvel com o ID solicitado previamente
      printf("Digite o consumo em metros cúbicos: ");
      scanf("%f", &consumo);
      casas[i].consumo[mes - 1] = consumo;
      printf("Consumo registrado com sucesso!\n");
    }
  }
  // Tratativa para caso o ID nao existe ou seja digitado de forma incorreta
  if (!encontrada)
  {
    printf("Casa com ID %d não encontrada.\n", id);
  }
}
