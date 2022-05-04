#include <list>
#include <cstdio>
#include <iostream>
#include <random>

class Matrix {
public:
    double **data;
    int N;
    int M;

    Matrix(int n, int m, double value = 0);

    void Randomize() const;

    virtual ~Matrix();
};

static double random_number(double min = -99, double max = 99) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(gen);
}