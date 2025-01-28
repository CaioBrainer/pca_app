//
// Created by caiogarnier on 28/01/2025.
//

#ifndef PCA_H
#define PCA_H

#include <Eigen/Dense>



class PCA {
public:
    PCA();
    void centralizaDadosMatriz(const Eigen::MatrixXd &matriz);
    void matrizCov();
    void autoDecomposicao();
    void vetoresImportantes();
    void fitPCA(const Eigen::MatrixXd &matriz,const Eigen::Index &componentes);
    Eigen::MatrixXd getMatrizReduzida();
    Eigen::MatrixXd getAutovetoresOrdenados();
private:
    Eigen::MatrixXd matrizCentralizada {};
    Eigen::MatrixXd matrizCovariancia {};
    Eigen::EigenSolver<Eigen::MatrixXd> matrizDecomposta{};
    Eigen::MatrixXd autoVetoresOrdenados {};
    Eigen::MatrixXd matrizReduzida {};
};


#endif //PCA_H
