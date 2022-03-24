#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int global_variable = 0;
pthread_mutex_t mutex;

void printError(int errNum) {
    fprintf(stderr, "Error = %d (%s)\n", errNum, strerror(errNum));
}

void *increment(void *arg) {
    int r, i, tmp;
    for (i = 0; i < 100000; i++) {

        if ((r = pthread_mutex_lock(&mutex)) != 0) {
            printError(r);
            exit(1);
        }
        tmp = global_variable;
        tmp++;
        printf("%d\n", tmp);
        global_variable = tmp;

        if ((r = pthread_mutex_unlock(&mutex)) != 0) {
            printError(r);
            exit(1);
        }
    }

    return 0;
}


void *decrement(void *arg) {
    int r, i, tmp;
    for (i = 0; i < 100000; i++) {

        if ((r = pthread_mutex_lock(&mutex)) != 0) {
            printError(r);
            exit(1);
        }

        tmp = global_variable;
        tmp--;
        printf("%d\n", tmp);
        global_variable = tmp;

        if ((r = pthread_mutex_unlock(&mutex)) != 0) {
            printError(r);
            exit(1);
        }
    }

    return 0;
}

int main() {
    int r;
    pthread_t tid1, tid2;

    if ((r = pthread_mutex_init(&mutex, NULL)) != 0) {
        printError(r);
        return 1;
    }

    pthread_create(&tid1, NULL, increment, NULL);
    pthread_create(&tid2, NULL, decrement, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);

    sleep(1);
    printf("\nglobal variable: %d\n", global_variable);

    return 0;
}