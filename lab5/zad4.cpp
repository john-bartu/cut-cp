#include <cstdio>
#include <omp.h>

#define NO_THREADS 7
#define N 100000000

int main() {
    long i, a;
    double t_start, stop;

    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    stop = omp_get_wtime();
    printf("Static  3:\t\t%lfs\n", stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    stop = omp_get_wtime();
    printf("Static  Default:\t%lfs\n", stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    stop = omp_get_wtime();
    printf("Dynamic 3:\t\t%lfs\n", stop - t_start);


    t_start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        a++;
    }
    stop = omp_get_wtime();
    printf("Dynamic Default:\t%lfs", stop - t_start);
    return 0;
}
