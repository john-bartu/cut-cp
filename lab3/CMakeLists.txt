
project(PW_LAB_3)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(lab3_zad1 zad1.c)

set(CMAKE_CXX_FLAGS -pthread)


add_executable(lab3_zad2 zad2.cpp)

target_link_libraries( lab3_zad1 pthread )
target_link_libraries( lab3_zad2 pthread )