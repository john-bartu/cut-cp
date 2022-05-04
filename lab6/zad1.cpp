#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"

#include <iostream>
#include <omp.h>
#include "matrix.h"
#include "csv.h"

#define THREADS 12

// multiply_XXX
// r - used reduction
// n - no reduction

Matrix multiply_rrr(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
    for (int y = 0; y < A.N; y++) {
#pragma omp parallel for schedule(static) num_threads(THREADS)
        for (int x = 0; x < B.M; x++) {
            sum = 0;
#pragma omp parallel for schedule(static) num_threads(THREADS)
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_rrn(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
    for (int y = 0; y < A.N; y++) {
#pragma omp parallel for schedule(static) num_threads(THREADS)
        for (int x = 0; x < B.M; x++) {
            sum = 0;
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_rnr(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
    for (int y = 0; y < A.N; y++) {
        for (int x = 0; x < B.M; x++) {
            sum = 0;
#pragma omp parallel for schedule(static) num_threads(THREADS)
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_nrr(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
    for (int y = 0; y < A.N; y++) {
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
        for (int x = 0; x < B.M; x++) {
            sum = 0;
#pragma omp parallel for schedule(static) num_threads(THREADS)
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_rnn(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
    for (int y = 0; y < A.N; y++) {
        for (int x = 0; x < B.M; x++) {
            sum = 0;
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_nrn(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
    for (int y = 0; y < A.N; y++) {
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum)
        for (int x = 0; x < B.M; x++) {
            sum = 0;
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_nnr(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
    for (int y = 0; y < A.N; y++) {
        for (int x = 0; x < B.M; x++) {
            sum = 0;
#pragma omp parallel for schedule(static) num_threads(THREADS) reduction(+: sum) 
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}


Matrix multiply_nnn(const Matrix &A, const Matrix &B) {
    double sum;
    if (A.M != B.N) {
        throw std::invalid_argument("Size is not equal");
    }

    Matrix C(A.N, B.M);
    for (int y = 0; y < A.N; y++) {
        for (int x = 0; x < B.M; x++) {
            sum = 0;
            for (int i = 0; i < A.M; i++) {
                sum += A.data[y][i] * B.data[i][x];
            }
            C.data[y][x] = sum;
        }
    }
    return C;
}

static double get_and_reset_time(double *start_time) {
    double val = omp_get_wtime() - *start_time;
    *start_time = omp_get_wtime();
    return val;

}

int main() {
    double time;

    CSVFile csv("MatrixTiming.csv");
    csv << "dimmension" << "rrr" << "rrn" << "rnr" << "nrr" << "rnn" << "rnr" << "nnr" << "nnn" << nextl;

    for (int dim = 500; dim <= 2000; dim += 1500) {
        csv << dim;
        std::cout << dim << std::endl;
        Matrix A(dim, dim);
        Matrix B(dim, dim);

        A.Randomize();
        B.Randomize();

        get_and_reset_time(&time);

        multiply_rrr(A, B);
        csv << get_and_reset_time(&time);

        multiply_rrn(A, B);
        csv << get_and_reset_time(&time);

        multiply_rnr(A, B);
        csv << get_and_reset_time(&time);

        multiply_nrr(A, B);
        csv << get_and_reset_time(&time);

        multiply_rnn(A, B);
        csv << get_and_reset_time(&time);

        multiply_nrn(A, B);
        csv << get_and_reset_time(&time);

        multiply_nnr(A, B);
        csv << get_and_reset_time(&time);

        multiply_nnn(A, B);
        csv << get_and_reset_time(&time);

        csv << nextl;
    }

    csv.flush();
    return 0;
}