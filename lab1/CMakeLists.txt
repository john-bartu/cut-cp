
project(PW_Przetwarzanie_Wspolbierzne C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1_zad1
        moj_program.c
        ../pomiar_czasu/pomiar_czasu.c
        ../pomiar_czasu/pomiar_czasu.h
        )