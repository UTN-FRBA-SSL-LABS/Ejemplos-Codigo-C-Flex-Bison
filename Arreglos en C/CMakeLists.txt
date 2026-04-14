cmake_minimum_required(VERSION 3.28)
project(Arreglos_2025 C)

set(CMAKE_C_STANDARD 11)

add_executable(Arreglos_2025
        main.c
        1.recorrer.c
        2.por_parametro.c
        3.retornar.c
        "Ejemplos Arreglos/Coordenadas.c"
        "Ejemplos Arreglos/por_parametro_2.c"
        "Ejemplos Arreglos/por_parametro_bidimensional.c"
        "Ejemplos Arreglos/Puntajes.c"
        "Ejemplos Arreglos/TamanioDelArreglo.c"
)
