cmake_minimum_required(VERSION 3.10)
project(svm_test)

set(CMAKE_CXX_STANDARD 23)

# Incluir diretório da LIBSVM
include_directories(/usr/local/include)
# Eigen
include_directories(${CMAKE_SOURCE_DIR}/libs_externas/eigen-3.4.0)
include_directories(${CMAKE_SOURCE_DIR}/include)
# Criar o executável
add_executable(svm_test src/main.cpp
        include/csv.cpp
        include/csv.h
        include/SVC.cpp
        include/SVC.h
        include/PCA.cpp
        include/PCA.h
        include/dadosTabulares.h)

# Linkar com a biblioteca LIBSVM
target_link_libraries(svm_test /usr/local/lib/libsvm.so)