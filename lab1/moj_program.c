//
// Created by jamabaiz on 3/3/2022.
//

#include "../pomiar_czasu/pomiar_czasu.h"
#include <stdio.h>

static int count = 9999999;

void test1() {
    printf("Test1\n");
    inicjuj_czas();

    for (int i = 0; i < count-1; i++) {
        printf("H");
    }

    printf("\ne");

    drukuj_czas();
}

void test2() {
    printf("Test2\n");
    inicjuj_czas();
    double test1 = 32190325454.0;
    double test2 = 2.0;
    int wynik;

    for (int i = 0; i < count; i++) {
        wynik = test1 /test2;
    }

    drukuj_czas();
}

int main(int argc, char *argv[]) {
    test1();
    test2();
}