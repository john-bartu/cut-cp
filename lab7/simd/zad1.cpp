#include <omp.h>
#include <random>
#include <iostream>
#include "../csv.h"

std::random_device rd{};
std::mt19937 gen{rd()};

static double random_number(double min = -99, double max = 99) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(gen);
}

void randomize_vector(double *vec, long int size) {
    for (long int i = 0; i < size; i++) {
        vec[i] = random_number();
    }
}

double multiplicate(double *v1, double *v2, long int size) {
    double product = 0;
    for (long int i = 0; i < size; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}

double multiplication_reduction(double *v1, double *v2, long int size) {
    double product = 0;
#pragma omp parallel for schedule(static) num_threads(6) reduction(+: product)
    for (long int i = 0; i < size; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}

double multiplicate_simd(double *v1, double *v2, long int size) {
    double product = 0;
#pragma omp simd
    for (long int i = 0; i < size; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}


int main() {
    long int N = 1000000000;
    double *vector1, *vector2;
    double start;

    vector1 = (double *) malloc(sizeof(double) * N);
    vector2 = (double *) malloc(sizeof(double) * N);

    std::cout << "Vectors Generating" << std::endl;
    randomize_vector(vector1, N);
    randomize_vector(vector2, N);
    std::cout << "Vectors Generated" << std::endl;

    CSVFile csvFile("vector.csv");
    csvFile << "SIZE" << "NONE" << "SIMD" << "REDUCTION" << nextl;

    for (long int n = 10; n <= N; n *= 10) {
        csvFile << n;

        start = omp_get_wtime();
        multiplicate(vector1, vector2, n);
        csvFile << omp_get_wtime() - start;

        start = omp_get_wtime();
        multiplicate_simd(vector1, vector2, n);
        csvFile << omp_get_wtime() - start;

        start = omp_get_wtime();
        multiplication_reduction(vector1, vector2, n);
        csvFile << omp_get_wtime() - start << nextl;

        std::cout << "SIZE: " << n << std::endl;
    }
}