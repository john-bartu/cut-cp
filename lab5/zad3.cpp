#include <cstdio>
#include <omp.h>

#define NO_THREADS 4
#define N 15

int main() {
    int i, a;

    a = 7;
    printf("static3  |");
#pragma omp parallel for schedule(static, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        printf(" \t%d ", omp_get_thread_num());
        a++;
    }

    a = 7;
    printf("\nstatic   |");
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        printf(" \t%d ", omp_get_thread_num());
        a++;
    }

    a = 7;
    printf("\ndynamic3 |");
#pragma omp parallel for schedule(dynamic, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        printf(" \t%d ", omp_get_thread_num());
        a++;
    }

    a = 7;
    printf("\ndynamic  |");
#pragma omp parallel for schedule(dynamic) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        printf(" \t%d ", omp_get_thread_num());

        a++;
    }

    return 0;
}
