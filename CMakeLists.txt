cmake_minimum_required(VERSION 3.30)
project(pca_app)

set(CMAKE_CXX_STANDARD 20)

# Para incluir bibliotecas externas "header only"
# O endereço tinha que para nesse diretório aí ao invés de ir pro "/eigen" (nome de outra pasta lá pode dentro)
include_directories(${CMAKE_SOURCE_DIR}/libs_externas/eigen-3.4.0)

add_executable(pca_app main.cpp csv.cpp csv.h dadosTabulares.h)
