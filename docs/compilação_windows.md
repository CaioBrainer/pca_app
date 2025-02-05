# Baixar o código-fonte da LIBSVM


```
git clone https://github.com/cjlin1/libsvm.git
cd libsvm
```

# Criar o CMakeLists.txt para LIBSVM
- Criar dentro da pasta do libsvm

```
cmake_minimum_required(VERSION 3.10)
project(libsvm)

# Define a versão do C++ compilação
set(CMAKE_CXX_STANDARD 20)

# Definir compilação para Windows
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Criar biblioteca estática (libsvm.a)
add_library(svm STATIC svm.cpp)

# Especificar diretório de saída
set_target_properties(svm PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Incluir diretórios
target_include_directories(svm PUBLIC ${CMAKE_SOURCE_DIR})
```

# Compilar LIBSVM para Windows

```
mkdir build
cd build
cmake ..
make
```

- Se der certo
```
cp build/lib/libsvm.a ~/mingw_libs/
cp svm.h ~/mingw_libs/
```

# Modificar o CMakeLists.txt

```
cmake_minimum_required(VERSION 3.10)
project(svm_test)

set(CMAKE_CXX_STANDARD 20)

# Definir compilação para Windows
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Adicionar flags para compilação estática
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Incluir diretório da LIBSVM e Eigen
#include_directories(/usr/local/include)
include_directories(${CMAKE_SOURCE_DIR}/libs_externas/eigen-3.4.0)
include_directories(${CMAKE_SOURCE_DIR}/libsvm_win)

# Criar o executável
add_executable(svm_test main.cpp
        csv.cpp
        csv.h
        SVC.cpp
        SVC.h
        PCA.cpp
        PCA.h
        dadosTabulares.h)

# Linkar com a biblioteca LIBSVM compilada
target_link_libraries(svm_test ${CMAKE_SOURCE_DIR}/libsvm_win/libsvm.a)
```

- Agora só compilar:
```
mkdir build
cd build
cmake ..
make
``




