# Gerenciador De Tarefas

## Dados da Turma <br>
Dia da semana: Sexta Feira <br>
Período: Noturno <br>

### Integrantes

|RA| NOME COMPLETO| CURSO | TURMA |
| ------------ | ------------ | ------------ | ------------ |
|3021103570|Breno Mendes Moura|TADS|05A|
|3021100282|Victor de souza bernardo|TADS|05A|
|3021104031|Cesar Augusto Martins Vallim|TADS|05A|
|3021103269|Elias Yuri Yoshy Miyashiro|TADS|05A|
|3022201058|Acsa Cristina Sena|TADS|02A|
|3022200274|Matheus souza Martins|TADS|05A|

<hr>
<br>
<br>

![image](https://github.com/BrenoMendesMoura/GerenciadorDeTarefas/assets/80074264/5ae3b881-801b-4b37-a1b5-91b139fec0eb)


<hr>

## Explicação do código realizado em c++

### Bibliotecas e typedef struct
Utilizamos 2 bibliotecas para a realização do código, sendo elas:
- `<stdio.h>`, para entrada e saída de mensagens no console.
- `<string.h>`, para manipulação de dados do tipo string.

A utilidade do typedef struct é criar um novo tipo de dados com um nome mais fácil de usar e entender, simplificando a declaração de variáveis da estrutura.

A partir disso declaramos as variáveis globais que utilizamos ao decorrer do código.
```c
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
```


<hr>
<br>
<br>

### IsFull e IsEmpty
Essas duas funções são usadas em todo o código, a ideia principal é realizar uma verificação em uma estrutura de condição para determinar se a fila ou pilha está cheia ou vazia.

```c
int isEmpty() {
  return total == 0;
}

int isFull() {
  return total == TAM;
}
```

<hr>
<br>
<br>

### Pilha


Copiamos o *pilha* que o professor enviou na segunda-feira e adaptamos ao código, A prioridade é levada em consideração apenas na inserção, para manter as tarefas ordenadas na pilha de acordo com sua prioridade.
por padrão, sem ordenar com o método bolha, o resultado deveria ser algo nesse estilo:


|id| Tarefa| Prioridade
| ------------ | ------------ | ------------ |
|4|Estudar para AV1|8|
|1|Desenrolar a prova do dia 30-05|9|
|5|Fazer o projeto da faculdade|10|


Observe que o ID não está ordenado, mas a lista de prioridade está em empilhado de forma crescente.


```c
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
```


<hr>
<br>
<br>

### Fila

O projeto foi baseado no código do dia 12/05 sobre fila, ele foi a base para realizarmos o gerenciador de tarefas. Portanto, talvez haja uma similaridade com o código feito no replit.

- sizeof, é utilizado para evitar que estoure o buffer;
- strncpy é utilizado para copiar a descrição para a variável descrição;
- \0 é uma formatação para aceitar apenas string válida.

```c
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
```

<hr>
<br>
<br>

### Listar e pesquisar Tarefas

Para listar, utilizamos uma estrutura de repetição para ordenar do último ao primeiro de acordo com o decremento da variável ```i```.

A pesquisa binária começa calculando o índice médio da lista, faz a soma do inicio, fim e divide pela quantidade de variáveis(2).
O código entra em looping, realizando essa mesma verificação até que encontre o ID pesquisado.

```c
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
```


<hr>
<br>
<br>

### Ordenação - Método bolha

A ordenação foi baseada no código do dia 14/04, o método bolha percorre repetidamente a lista até que encontre um valor menor. Após encontrar um valor menor, ele realiza a troca de posição no índice.


```c
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
```



<hr>
<br>
<br>

### Função principal - Menu e switch case

Nesse bloco final nós temos 2 funções, todas as funções secundárias se encontram aqui.

- Primeira função: Menu;

- Segunda função: Main.

A primeira função é repetida toda vez que a variável opção é chamada, até que escolha a opção de sair.

```c
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
```
