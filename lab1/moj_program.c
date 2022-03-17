//
// Created by jamabaiz on 3/3/2022.
//

#include "../pomiar_czasu/pomiar_czasu.h"
#include <stdio.h>
#include <math.h>

void io_test(int count) {
    for (int i = 0; i < count - 1; i++) {
        printf("H");
    }
    printf("\n");
}

double calc_test(int count) {
    double test1 = 32190325454.0;
    double test2 = 2.0;
    double wynik;
    for (int i = 0; i < count; i++) {
        wynik = test1 - 1.2314 / test2 + 123.2131 - 1231.23 * 12312 - test1 / 2321.32342;
    }
    return wynik;
}

int main() {
    int count = 9999999;

    inicjuj_czas();
    io_test(count);
    printf("Test Function I/O\n");
    drukuj_czas();

    inicjuj_czas();
    calc_test(count);
    printf("Test Function Calculations\n");
    drukuj_czas();
}