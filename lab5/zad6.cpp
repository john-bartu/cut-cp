#include <cstdio>
#include <omp.h>

#define NO_THREADS 6
#define NO_ITERATIONS 10000000

void reduction_test() {
    double t_start, t_stop;
    long sum = 0;
    int n = 1234;
    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS) reduction(+: sum)
    for (int i = 0; i < NO_ITERATIONS; i++) {
        sum += n * n;
    }
    t_stop = omp_get_wtime();
    printf("Reduction: %ld\nTime:\t%lfs\n\n", sum, t_stop - t_start);

}

void atomic_test() {
    double t_start, t_stop;
    long sum = 0;
    int n = 1234;

    sum = 0;
    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (int i = 0; i < NO_ITERATIONS; i++) {
#pragma omp atomic
        sum += n * n;
    }
    t_stop = omp_get_wtime();
    printf("Atomic: %ld\nTime:\t%lfs\n\n", sum, t_stop - t_start);
}

void critical_test() {
    double t_start, t_stop;
    long sum = 0;
    int n = 1234;

    sum = 0;
    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (int i = 0; i < NO_ITERATIONS; i++) {
#pragma omp critical
        sum += n * n;
    }
    t_stop = omp_get_wtime();
    printf("Critical: %ld\nTime:\t%lfs\n\n", sum, t_stop - t_start);

}

void lock_test() {
    double t_start, t_stop;
    long sum = 0;
    int n = 1234;

    omp_lock_t lock;
    omp_init_lock(&lock);
    sum = 0;
    t_start = omp_get_wtime();
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (int i = 0; i < NO_ITERATIONS; i++) {
        omp_set_lock(&lock);
        sum += n * n;
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    t_stop = omp_get_wtime();
    printf("Lock: %ld\nTime:\t%lfs\n", sum, t_stop - t_start);

}

int main() {
    reduction_test();
    atomic_test();
    critical_test();
    lock_test();

    return 0;
}