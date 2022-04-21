#include <cstdio>
#include <omp.h>

#define NO_THREADS 12
#define N 100000000

int main() {
    long i, a;
    double t_start, t_stop;

    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    t_stop = omp_get_wtime();
    printf("Static  3:\t\t%lfs\n", t_stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    t_stop = omp_get_wtime();
    printf("Static  Default:\t%lfs\n", t_stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    t_stop = omp_get_wtime();
    printf("Dynamic 3:\t\t%lfs\n", t_stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    t_stop = omp_get_wtime();
    printf("Dynamic Default:\t%lfs", t_stop - t_start);
    return 0;
}
