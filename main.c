#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"

int main() {
    Tarefa *lista = NULL;
    int opcao, id, prioridade, idFim;
    char descricao[100];

    do {
        printf("\n--- GERENCIADOR DE TAREFAS ---\n");
        printf("1. Inserir tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Mover prioridade para in�cio\n");
        printf("4. Inverter intervalo\n");
        printf("5. Exibir tarefas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                printf("ID: ");
                scanf("%d", &id);
                getchar();
                printf("Descri��o: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0; // Remove o \n do final
                printf("Prioridade (1=Alta, 2=M�dia, 3=Baixa): ");
                scanf("%d", &prioridade);
                InserirTarefa(&lista, id, descricao, prioridade);
                break;
            case 2:
                printf("ID da tarefa a remover: ");
                scanf("%d", &id);
                RemoverTarefa(&lista, id);
                break;
            case 3:
                printf("Prioridade a mover para o in�cio (1=Alta, 2=M�dia, 3=Baixa): ");
                scanf("%d", &prioridade);
                MoverPrioridadeParaInicio(&lista, prioridade);
                break;
            case 4:
                printf("ID do in�cio do intervalo: ");
                scanf("%d", &id);
                printf("ID do fim do intervalo: ");
                scanf("%d", &idFim);
                InverterIntervalo(&lista, id, idFim);
                break;
            case 5:
                ExibirTarefas(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while(opcao != 0);

    // Libera a mem�ria da lista ao sair
    Tarefa *atual = lista;
    while (atual != NULL) {
        Tarefa *prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    return 0;
}
