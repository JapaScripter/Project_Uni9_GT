#include <stdio.h>
#include <string.h>
#define TAM 10

typedef struct {
  int id;
  char descricao[100];
  int prioridade;
} Tarefa;

Tarefa tarefas[TAM];
int primeiro = 0, ultimo = 0, total = 0;

int isEmpty() {
  return total == 0;
}

int isFull() {
  return total == TAM;
}

void push(Tarefa tarefa) {
  if (isFull()) {
    printf("A pilha de prioridades está cheia.\n");
  } else {
    int i;
    for (i = total - 1; i >= 0; i--) {
      if (tarefa.prioridade > tarefas[i].prioridade) {
        tarefas[i + 1] = tarefas[i];
      } else {
        break;
      }
    }
    tarefas[i + 1] = tarefa;
    total++;
  }
}

Tarefa pop() {
  if (isEmpty()) {
    printf("A pilha de prioridades está vazia.\n");
    Tarefa emptyTask = {0, "", 0};
    return emptyTask;
  } else {
    Tarefa tarefa = tarefas[total - 1];
    total--;
    return tarefa;
  }
}

void inserirTarefa(int id, char descricao[], int prioridade) {
  if (isFull()) {
    printf("A lista de tarefas está cheia.\n");
  } else {
    Tarefa novaTarefa;
    novaTarefa.id = id;
    strncpy(novaTarefa.descricao, descricao, sizeof(novaTarefa.descricao) - 1);
    novaTarefa.descricao[sizeof(novaTarefa.descricao) - 1] = '\0';  
    novaTarefa.prioridade = prioridade;
    push(novaTarefa);
  }
}

void retirarTarefa() {
  if (isEmpty()) {
    printf("A lista de tarefas está vazia.\n");
  } else {
    Tarefa tarefa = pop();
    printf("Tarefa retirada: %d - %s\n", tarefa.id, tarefa.descricao);
  }
}

void listarTarefas() {
  int i;
  printf("Lista de Tarefas:\n");
  for (i = total - 1; i >= 0; i--) {
    printf("%d - %s (Prioridade: %d)\n", tarefas[i].id, tarefas[i].descricao, tarefas[i].prioridade);
  }
}

int pesquisaBinaria(int id) {
  int inicio = 0;
  int fim = total - 1;

  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;

    if (tarefas[meio].id == id) {
      return meio;
    } else if (tarefas[meio].id < id) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }

  return -1;
}

void trocarTarefas(Tarefa *t1, Tarefa *t2) {
  Tarefa temp = *t1;
  *t1 = *t2;
  *t2 = temp;
}

void bubbleSort() {
  int i, j;

  for (i = 0; i < total - 1; i++) {
    for (j = 0; j < total - i - 1; j++) {
      if (tarefas[j].id > tarefas[j + 1].id) {
        trocarTarefas(&tarefas[j], &tarefas[j + 1]);
      }
    }
  }

  printf("Tarefas ordenadas com sucesso.\n");
}

int menu() {
  int opcao;
  printf("\n-------------\n");
  printf("\nGerenciador de Tarefas");
  printf("\n1 - Inserir Tarefa");
  printf("\n2 - Retirar Tarefa");
  printf("\n3 - Listar Tarefas");
  printf("\n4 - Pesquisar Tarefa");
  printf("\n5 - Ordenar Tarefas (Bubble Sort)");
  printf("\n0 - Sair");
  printf("\n\nEscolha uma opção: ");
  scanf("%d", &opcao);

  return opcao;
}

int main(void) {
  int opcao;

  do {
    opcao = menu();
    switch (opcao) {
      case 1:
        {
          int id, prioridade;
          char descricao[100];
          printf("Digite o ID da tarefa: ");
          scanf("%d", &id);
          printf("Digite a descrição da tarefa: ");
          scanf(" %[^\n]", descricao);
          printf("Digite a prioridade da tarefa: ");
          scanf("%d", &prioridade);
          inserirTarefa(id, descricao, prioridade);
          break;
        }
      case 2:
        retirarTarefa();
        break;
      case 3:
        listarTarefas();
        break;
      case 4:
        {
          int id;
          printf("Digite o ID da tarefa a pesquisar: ");
          scanf("%d", &id);
          int posicao = pesquisaBinaria(id);
          if (posicao != -1) {
            printf("Tarefa encontrada: %d - %s (Prioridade: %d)\n", tarefas[posicao].id, tarefas[posicao].descricao, tarefas[posicao].prioridade);
          } else {
            printf("Tarefa não encontrada.\n");
          }
          break;
        }
      case 5:
        bubbleSort();
        break;
      case 0:
        printf("Saindo...\n");
        break;
      default:
        printf("Opção inválida\n");
    }
  } while (opcao != 0);
  
  return 0;
}
