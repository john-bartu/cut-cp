#include <stdio.h>
#include <omp.h>

#define NO_THREADS 7


int main() {
    int i, a = 7;

    printf("\tPrivate:\n");
#pragma omp parallel for private(a) num_threads(NO_THREADS)
    for (i = 0; i < 10; i++) {
        printf("Thread %d a=%d\n", omp_get_thread_num(), a);
        a++;
    }

    printf("\n\tFirst Private:\n");
#pragma omp parallel for firstprivate(a) num_threads(NO_THREADS)
    for (i = 0; i < 10; i++) {
        printf("Thread %d a=%d\n", omp_get_thread_num(), a);
        a++;
    }

    printf("\n\tShared:\n");
#pragma omp parallel for shared(a) num_threads(NO_THREADS)
    for (i = 0; i < 10; i++) {
        printf("Thread %d a=%d\n", omp_get_thread_num(), a);
        a++;
    }

    return 0;
}
