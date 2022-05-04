#include "matrix.h"

Matrix::Matrix(int n, int m, double value) : N(n), M(m) {
    data = (double **) malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        data[i] = (double *) malloc(M * sizeof(double));
        for (int j = 0; j < M; j++) {
            data[i][j] = value;
        }
    }
}

void Matrix::Randomize() const {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            data[i][j] = random_number();
        }
    }
}


Matrix::~Matrix() {
    for (int i = 0; i < N; i++) {
        delete[] data[i];
    }
    delete[] data;
}