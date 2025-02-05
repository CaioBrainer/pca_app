cmake_minimum_required(VERSION 3.10)
project(svm_test)

set(CMAKE_CXX_STANDARD 20)

# Incluir diretório da LIBSVM
include_directories(/usr/local/include)
# Eigen
include_directories(${CMAKE_SOURCE_DIR}/libs_externas/eigen-3.4.0)

# Criar o executável
add_executable(svm_test main.cpp
        csv.cpp
        csv.h
        SVC.cpp
        SVC.h
        PCA.cpp
        PCA.h
        dadosTabulares.h)

# Linkar com a biblioteca LIBSVM
target_link_libraries(svm_test /usr/local/lib/libsvm.so)