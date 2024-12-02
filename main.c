#include <stdio.h>  // Biblioteca para entrada e saída padrão
#include <locale.h> // Biblioteca para configurar localização
#include <string.h> // Biblioteca para manipulação de strings

#define MAX_CASAS 100       // Número máximo de casas que podem ser cadastradas
#define MESES 12            // Número de meses no ano
#define LIMITE_CONSUMO 15.0 // Limite recomendado de consumo mensal em m³

typedef struct // Estrutura que define uma residência
{
  int id;               // ID único da residência
  char morador[50];     // Nome do morador principal
  int moradores;        // Número de moradores na casa
  float consumo[MESES]; // Consumo mensal de água em m³
} Residencia;

void menu();                                                     // Exibe o menu de opções
void cadastrarCasa(Residencia casas[], int *quantidade);         // Cadastra uma nova casa
void registrarConsumoMensal(Residencia casas[], int quantidade); // Registra consumo mensal de uma casa
void exibirCasasAcimaMedia(Residencia casas[], int quantidade);  // Mostra casas com consumo acima do limite
void exibirCasasAbaixoMedia(Residencia casas[], int quantidade); // Mostra casas com consumo abaixo do limite

int main()
{
  setlocale(LC_ALL, "Portuguese"); // Configura localização para o idioma português
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

  int opcao; // Variável para armazenar a escolha do usuário no menu
  do
  {
    menu(); // Exibe o menu de opções
    printf("Escolha uma opção: ");
    scanf("%d", &opcao); // Lê a opção escolhida pelo usuário
    fflush(stdin);       // Limpa o buffer de entrada

    switch (opcao) // Executa a ação com base na opção escolhida
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
      printf("Opção inválida! Tente novamente\n"); // Trata opções inválidas
      break;
    }
  } while (opcao != 0); // Continua até que o usuário escolha sair
}

void menu()
{
  printf("\nMenu de Opções\n"); // Exibe as opções disponíveis no menu
  printf("1 - Cadastrar casa\n");
  printf("2 - Registrar consumo mensal\n");
  printf("3 - Exibir casas acima do limite de consumo\n");
  printf("4 - Exibir casas abaixo da média\n");
  printf("0 - Sair\n");
}

void cadastrarCasa(Residencia casas[], int *quantidade)
{
  if (*quantidade >= MAX_CASAS) // Verifica se a capacidade máxima foi atingida
  {
    printf("Capacidade máxima de casas atingida!\n");
    return;
  }

  Residencia novaCasa; // Cria uma nova casa para cadastrar
  printf("Digite o ID da casa: ");
  scanf("%d", &novaCasa.id); // Lê o ID da casa
  fflush(stdin);

  printf("Digite o nome do morador principal: ");
  fgets(novaCasa.morador, 50, stdin);                       // Lê o nome do morador principal
  novaCasa.morador[strcspn(novaCasa.morador, "\n")] = '\0'; // Remove o caractere de nova linha

  printf("Digite a quantidade de moradores: ");
  scanf("%d", &novaCasa.moradores); // Lê a quantidade de moradores

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
  scanf("%d", &id); // Lê o ID da casa para registro de consumo

  int encontrada = 0;
  for (int i = 0; i < quantidade; i++) // Procura pela casa com o ID informado
  {
    if (casas[i].id == id)
    {
      encontrada = 1;
      printf("Digite o mês (1-12): ");
      scanf("%d", &mes); // Lê o mês do consumo

      if (mes < 1 || mes > 12) // Valida o mês informado
      {
        printf("Mês inválido! Tente novamente.\n");
        return;
      }

      printf("Digite o consumo em metros cúbicos: ");
      scanf("%f", &consumo); // Lê o valor do consumo

      if (consumo > LIMITE_CONSUMO) // Exibe aviso caso o consumo exceda o limite
      {
        printf("Atenção: o consumo informado (%.2f) excede o limite recomendado de %.2f.\n", consumo, LIMITE_CONSUMO);
      }

      casas[i].consumo[mes - 1] = consumo; // Registra o consumo no mês indicado
      printf("Consumo registrado com sucesso!\n");
      return;
    }
  }

  if (!encontrada) // Informa caso o ID não seja encontrado
  {
    printf("Casa com ID %d não encontrada.\n", id);
  }
}

void exibirCasasAcimaMedia(Residencia casas[], int quantidade)
{
  printf("\nResidências com consumo mensal acima do limite de %.2f m³:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++) // Percorre todas as casas
  {
    for (int j = 0; j < MESES; j++) // Verifica o consumo de cada mês
    {
      if (casas[i].consumo[j] > LIMITE_CONSUMO) // Verifica se o consumo está acima do limite
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | Mês: %d | Consumo: %.2f m³\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
      }
    }
  }

  if (!encontrou) // Informa caso nenhuma casa tenha consumo acima do limite
  {
    printf("Nenhuma residência com consumo mensal acima do limite de %.2f m³.\n", LIMITE_CONSUMO);
  }
}

void exibirCasasAbaixoMedia(Residencia casas[], int quantidade)
{
  printf("\nResidências com consumo mensal abaixo do limite de %.2f m³:\n", LIMITE_CONSUMO);
  int encontrou = 0;

  for (int i = 0; i < quantidade; i++) // Percorre todas as casas
  {
    for (int j = 0; j < MESES; j++) // Verifica o consumo de cada mês
    {
      if (casas[i].consumo[j] < LIMITE_CONSUMO) // Verifica se o consumo está abaixo do limite
      {
        encontrou = 1;
        printf("ID: %d | Morador: %s | Mês: %d | Consumo: %.2f m³\n",
               casas[i].id, casas[i].morador, j + 1, casas[i].consumo[j]);
        break; // Exibe apenas uma entrada por casa
      }
    }
  }

  if (!encontrou) // Informa caso nenhuma casa tenha consumo abaixo do limite
  {
    printf("Nenhuma residência com consumo mensal abaixo do limite de %.2f m³.\n", LIMITE_CONSUMO);
  }
}
