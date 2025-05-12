#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tarefas.h" 

void InserirTarefa(Tarefa **lista, int id, char *descricao, int prioridade) {
    Tarefa *nova = (Tarefa *) malloc(sizeof(Tarefa));
    if (!nova) {
        printf("Erro ao alocar mem�ria!\n");
        return;
    }

    nova->id = id;
    strncpy(nova->descricao, descricao, 99);
    nova->descricao[99] = '\0';
    nova->prioridade = prioridade;
    nova->anterior = NULL;
    nova->proximo = NULL;

    if (*lista == NULL) {
        *lista = nova;
    } else {
        Tarefa *atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = nova;
        nova->anterior = atual;
    }
}

void RemoverTarefa(Tarefa **lista, int id) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Tarefa *atual = *lista;

    // Procura a tarefa com o id informado
    while (atual != NULL && atual->id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Tarefa com id %d n�o encontrada!\n", id);
        return;
    }

    // Se for o primeiro n�
    if (atual->anterior == NULL) {
        *lista = atual->proximo;
        if (*lista != NULL) {
            (*lista)->anterior = NULL;
        }
    } else {
        atual->anterior->proximo = atual->proximo;
    }

    // Se n�o for o �ltimo n�
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    free(atual);
    printf("Tarefa com id %d removida com sucesso!\n", id);
}

void MoverPrioridadeParaInicio(Tarefa **lista, int prioridade) {
    if (*lista == NULL) return;

    Tarefa *atual = *lista;
    Tarefa *primeiro = NULL; // Primeiro da sublista de prioridade X
    Tarefa *ultimo = NULL;   // �ltimo da sublista de prioridade X

    // Percorre a lista e separa a sublista de prioridade X
    while (atual != NULL) {
        Tarefa *proximo = atual->proximo;
        if (atual->prioridade == prioridade) {
            // Remove 'atual' da lista principal
            if (atual->anterior != NULL)
                atual->anterior->proximo = atual->proximo;
            else
                *lista = atual->proximo; // Atual era o primeiro da lista

            if (atual->proximo != NULL)
                atual->proximo->anterior = atual->anterior;

            // Adiciona 'atual' ao final da sublista de prioridade X
            atual->anterior = ultimo;
            atual->proximo = NULL;
            if (ultimo != NULL)
                ultimo->proximo = atual;
            else
                primeiro = atual; // Primeiro da sublista

            ultimo = atual;
        }
        atual = proximo;
    }

    // Se encontrou tarefas com a prioridade X, insere a sublista no in�cio
    if (primeiro != NULL) {
        if (*lista != NULL) {
            primeiro->anterior = NULL;
            ultimo->proximo = *lista;
            (*lista)->anterior = ultimo;
        }
        *lista = primeiro;
    }
}

void InverterIntervalo(Tarefa **lista, int idInicio, int idFim) {
    if (*lista == NULL || idInicio == idFim) return;

    Tarefa *inicio = NULL, *fim = NULL, *atual = *lista;

    // Encontrar os n�s de in�cio e fim
    while (atual != NULL) {
        if (atual->id == idInicio) inicio = atual;
        if (atual->id == idFim) fim = atual;
        atual = atual->proximo;
    }

    // Se n�o encontrou ambos, n�o faz nada
    if (inicio == NULL || fim == NULL) return;

    // Garante que 'inicio' vem antes de 'fim'
    Tarefa *temp = inicio;
    while (temp != NULL && temp != fim) temp = temp->proximo;
    if (temp == NULL) return; // 'fim' n�o est� depois de 'inicio'

    // Salva os ponteiros para reconectar depois
    Tarefa *antes = inicio->anterior;
    Tarefa *depois = fim->proximo;

    // Inverte os ponteiros dentro do intervalo
    atual = inicio;
    Tarefa *prev = depois;
    while (atual != depois) {
        Tarefa *prox = atual->proximo;
        atual->proximo = prev;
        atual->anterior = prox;
        prev = atual;
        atual = prox;
    }

    // Reconecta com o restante da lista
    if (antes != NULL)
        antes->proximo = fim;
    else
        *lista = fim;

    fim->anterior = antes;

    if (depois != NULL)
        depois->anterior = inicio;
    inicio->proximo = depois;
}

void ExibirTarefas(Tarefa *lista) {
    if (lista == NULL) {
        printf("Lista de tarefas vazia!\n");
        return;
    }

    printf("Lista de Tarefas:\n");
    Tarefa *atual = lista;
    while (atual != NULL) {
        printf("ID: %d | Descri��o: %s | Prioridade: ", atual->id, atual->descricao);
        if (atual->prioridade == 1)
            printf("Alta");
        else if (atual->prioridade == 2)
            printf("M�dia");
        else if (atual->prioridade == 3)
            printf("Baixa");
        else
            printf("Desconhecida");
        printf("\n");
        atual = atual->proximo;
    }
}
