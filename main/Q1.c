#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;             // Identificador do processo
    int burst_time;     // Tempo de execução necessário
    int remaining_time; // Tempo restante de execução
    int waiting_time;   // Tempo de espera acumulado
    int turnaround_time; // Tempo de retorno
} Process;


float calcularTempoMedioEspera(Process processes[], int n) {
    float tempo_medio_espera = 0;
    for (int i = 0; i < n; i++) {
        tempo_medio_espera += processes[i].waiting_time;
    }
    return tempo_medio_espera / n;
}


float calcularTempoMedioRetorno(Process processes[], int n) {
    float tempo_medio_retorno = 0;
    for (int i = 0; i < n; i++) {
        tempo_medio_retorno += processes[i].turnaround_time;
    }
    return tempo_medio_retorno / n;
}


void roundRobin(Process processes[], int n, int quantum) {
    int tempo_atual = 0;
    int processo_atual = 0;
    int processos_concluidos = 0;

    while (processos_concluidos < n) {
        if (processes[processo_atual].remaining_time > 0) {
            
            int tempo_executado = (processes[processo_atual].remaining_time < quantum)
                                      ? processes[processo_atual].remaining_time
                                      : quantum;

            
            processes[processo_atual].remaining_time -= tempo_executado;
            tempo_atual += tempo_executado;

            
            for (int i = 0; i < n; i++) {
                if (i != processo_atual && processes[i].remaining_time > 0) {
                    processes[i].waiting_time += tempo_executado;
                }
            }

            /
            if (processes[processo_atual].remaining_time == 0) {
                processes[processo_atual].turnaround_time = tempo_atual;
                processos_concluidos++;
            }
        }

        
        processo_atual = (processo_atual + 1) % n;
    }
}

int main() {
    int n; 
    printf("Digite o número de processos: ");
    scanf("%d", &n);

    Process processes[n];

    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Digite o burst time para o processo P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    int quantum; 
    printf("Digite o valor do quantum: ");
    scanf("%d", &quantum);

    
    roundRobin(processes, n, quantum);

    
    float tempo_medio_espera = calcularTempoMedioEspera(processes, n);
    float tempo_medio_retorno = calcularTempoMedioRetorno(processes, n);

    printf("\nMétricas:\n");
    printf("Tempo Médio de Espera: %.2f\n", tempo_medio_espera);
    printf("Tempo Médio de Retorno: %.2f\n", tempo_medio_retorno);

    return 0;
}
