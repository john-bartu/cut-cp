#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <omp.h>
#include <iostream>
#include "../csv.h"

long int fibonacci_none(long int n) {
    long int result, n_1, n_2;
    if (n < 2) {
        result = n;
    } else {
        n_1 = fibonacci_none(n - 1);
        n_2 = fibonacci_none(n - 2);
        result = n_1 + n_2;
    }
    return result;
}


long int fibonacci_task(long int n) {
    long int result, n_1, n_2;
    if (n < 2) {
        result = n;
    } else {
#pragma omp task shared(n_1)
        n_1 = fibonacci_task(n - 1);

#pragma omp task shared(n_2)
        n_2 = fibonacci_task(n - 2);

#pragma omp taskwait
        result = n_1 + n_2;
    }
    return result;
}

long int fibonacci_task_statement(long int n) {
    long int result, n_1, n_2;
    if (n < 2) {
        result = n;
    } else {
        if (n > 31) {
#pragma omp task shared(n_1)
            n_1 = fibonacci_task_statement(n - 1);

#pragma omp task shared(n_2)
            n_2 = fibonacci_task_statement(n - 2);

#pragma omp taskwait
            result = n_1 + n_2;
        } else {
            n_1 = fibonacci_task_statement(n - 1);
            n_2 = fibonacci_task_statement(n - 2);
            result = n_1 + n_2;
        }
    }
    return result;
}

int main() {
    double start;
    int COUNT = 40;

    CSVFile csvFile("fibonacci.csv");
    csvFile << "N" << "NONE" << "TASK" << "STATEMENT" << nextl;

    for (int n = 1; n <= COUNT; n++) {
        std::cout << "SIZE: " << n << std::endl;
        csvFile << n;

        start = omp_get_wtime();
        fibonacci_none(n);
        csvFile << omp_get_wtime() - start;

        start = omp_get_wtime();
        fibonacci_task(n);
        csvFile << omp_get_wtime() - start;

        start = omp_get_wtime();
        fibonacci_task_statement(n);
        csvFile << omp_get_wtime() - start << nextl;
    }
}

#pragma clang diagnostic pop