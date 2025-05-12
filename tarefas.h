#ifndef TAREFAS_H
#define TAREFAS_H

typedef struct Tarefa {
    int id;
    char descricao[100];
    int prioridade; // 1 = alta, 2 = média, 3 = baixa
    struct Tarefa *anterior;
    struct Tarefa *proximo;
} Tarefa;

    void InserirTarefa(Tarefa **lista, int id, char *descricao, int prioridade);
    void RemoverTarefa(Tarefa **lista, int id);
    void MoverPrioridadeParaInicio(Tarefa **lista, int prioridade);
    void InverterIntervalo(Tarefa **lista, int idInicio, int idFim);
    void ExibirTarefas(Tarefa *lista);

#endif