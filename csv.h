//
// Created by caiogarnier on 16/01/2025.
//

#ifndef LEITORCSV_H
#define LEITORCSV_H

#include <string>
#include <Eigen/Dense>

#include "dadosTabulares.h"

// incluir cabeçalho do struct que vou criar e trocar o tipo do método estático

class csv {
  public:
    // Métodos estáticos pertencem à classe, e não às instâncias definidas por ela
    static dadosTabulares lerArquivo(const std::string &fileName);
    static void visualizarArquivo(const dadosTabulares &dadosTabulares);
    static Eigen::MatrixXd paraMatriz(const dadosTabulares &dadosTabulares);
    //std::vector<std::vector<float>> escreverArquivo(); ~para implementar posteriormente
  // private:
  //   std::vector<std::string> cabecalho;
  //   std::vector<std::vector<float>> dadosNumericos;
};



#endif //LEITORCSV_H
