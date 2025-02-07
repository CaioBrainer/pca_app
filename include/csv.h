//
// Created by caiogarnier on 16/01/2025.
//

#ifndef LEITORCSV_H
#define LEITORCSV_H

#include <string>
#include <Eigen/Dense>
#include "dadosTabulares.h"

class csv {
  public:
    // Métodos estáticos pertencem à classe, e não às instâncias definidas por ela
    static dadosTabulares lerArquivo(const std::string &fileName);
    static void visualizarArquivo(const dadosTabulares &dadosTabulares);
    static Eigen::MatrixXd paraMatriz(const dadosTabulares &dadosTabulares);
    static void salvarArquivo(const dadosTabulares &dadosTabulares);
    static void salvarArquivo(const Eigen::MatrixXd &matrizPCA);
    static void salvarArquivo(const dadosTabulares &dadosTabulares, const Eigen::MatrixXd &matrizPCA);
};



#endif //LEITORCSV_H
