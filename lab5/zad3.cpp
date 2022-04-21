#include <cstdio>
#include <omp.h>

#define NO_THREADS 7
#define N 15

int main() {
    int i, a;
    int test_static_portion_3[N],
            test_static_portion_default[N],
            test_dynamic_portion_3[N],
            test_dynamic_portion_default[N];

    a = 7;
#pragma omp parallel for schedule(static, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        test_static_portion_3[i] = omp_get_thread_num();
        a++;
    }

    a = 7;
#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        test_static_portion_default[i] = omp_get_thread_num();
        a++;
    }

    a = 7;
#pragma omp parallel for schedule(dynamic, 3) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        test_dynamic_portion_3[i] = omp_get_thread_num();
        a++;
    }

    a = 7;
#pragma omp parallel for schedule(dynamic) num_threads(NO_THREADS)
    for (i = 0; i < N; i++) {
        test_dynamic_portion_default[i] = omp_get_thread_num();
        a++;
    }

    printf(" s 3  \t  s  \t d 3 \t  d  \n");
    printf(" ---  \t --- \t --- \t --- \n");

    for (i = 0; i < N; i++) {
        printf("  %d  \t  %d  \t  %d  \t  %d  \n",
               test_static_portion_3[i],
               test_static_portion_default[i],
               test_dynamic_portion_3[i],
               test_dynamic_portion_default[i]
        );
    }

    return 0;
}
