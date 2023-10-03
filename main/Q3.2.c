#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_LEITORES 5
#define NUM_ESCRITORES 2

sem_t mutex, db, leitores_mutex;
int leitores = 0;

void *leitor(void *arg) {
    while (1) {
        sem_wait(&mutex);
        sem_post(&mutex);

        

        sem_wait(&leitores_mutex);
        leitores--;
        if (leitores == 0) {
            sem_post(&db);
        }
        sem_post(&leitores_mutex);

        
    }
}

void *escritor(void *arg) {
    while (1) {
        sem_wait(&mutex);
        sem_wait(&leitores_mutex);
        
        leitores++;
        if (leitores == 1) {
            sem_wait(&db);
        }
        sem_post(&leitores_mutex);
        sem_post(&mutex);

        

        sem_wait(&leitores_mutex);
        leitores--;
        if (leitores == 0) {
            sem_post(&db);
        }
        sem_post(&leitores_mutex);

        
    }
}

int main() {
    pthread_t leitores_threads[NUM_LEITORES], escritores_threads[NUM_ESCRITORES];

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);
    sem_init(&leitores_mutex, 0, 1);

    for (int i = 0; i < NUM_LEITORES; i++) {
        pthread_create(&leitores_threads[i], NULL, leitor, NULL);
    }

    for (int i = 0; i < NUM_ESCRITORES; i++) {
        pthread_create(&escritores_threads[i], NULL, escritor, NULL);
    }

    for (int i = 0; i < NUM_LEITORES; i++) {
        pthread_join(leitores_threads[i], NULL);
    }

    for (int i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(escritores_threads[i], NULL);
    }

    return 0;
}
