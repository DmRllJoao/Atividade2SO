#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

pthread_mutex_t garfos[NUM_FILOSOFOS];
sem_t lugares_na_mesa;

void *filosofo(void *arg) {
    int id = *((int *)arg);
    int garfo_esquerdo = id;
    int garfo_direito = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        
        printf("Filósofo %d está pensando.\n", id);
        sleep(rand() % 3);

        
        sem_wait(&lugares_na_mesa);
        pthread_mutex_lock(&garfos[garfo_esquerdo]);
        pthread_mutex_lock(&garfos[garfo_direito]);

        
        printf("Filósofo %d está comendo.\n", id);
        sleep(rand() % 3);

        
        pthread_mutex_unlock(&garfos[garfo_esquerdo]);
        pthread_mutex_unlock(&garfos[garfo_direito]);
        sem_post(&lugares_na_mesa);
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    sem_init(&lugares_na_mesa, 0, NUM_FILOSOFOS);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}
