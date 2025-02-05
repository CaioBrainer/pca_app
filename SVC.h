//
// Created by caiobrainer on 04/02/25.
//

#ifndef SVC_H
#define SVC_H

#include <svm.h>
#include <Eigen/Dense>

class SVC {
public:
    void treinoSVC(const Eigen::MatrixXd &matrizAtributos, Eigen::VectorXd &vetorRotulos);
private:
    svm_model *model {};
    Eigen::VectorXd pesos{};
    double bias{};
};



#endif //SVC_H
