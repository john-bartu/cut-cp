
project(PW_LAB_7)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

add_executable(lab7_zad1 zad1.cpp)
#add_executable(lab7_zad2 zad2.cpp)
#add_executable(lab7_zad3 zad3.cpp)
#add_executable(lab7_zad4 zad4.cpp)
#add_executable(lab7_zad5 zad5.cpp)
#add_executable(lab7_zad6 zad6.cpp)