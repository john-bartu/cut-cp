#include <cstdio>

#define NO_THREADS 8


int main() {
    long sum = 0;
    int n = 10;

#pragma omp parallel for schedule(static) num_threads(NO_THREADS)
    for (int i = 0; i < 500; i++) {
        sum += n * n;
    }

    printf("Sum: %ld\n", sum);
    return 0;
}
