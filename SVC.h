//
// Created by caiobrainer on 01/02/25.
//

#ifndef SVC_H
#define SVC_H


#include <Eigen/Dense>

class SVC {
public:
    void treino(const Eigen::MatrixXd &matrizDados, const Eigen::VectorXd &vetorRotulos,
        const double &valorRegularizacao, double taxaAprendizado=0.01);
    std::vector<int> previsao(const Eigen::MatrixXd &matrizDados);
    void getPesos();
    void getVies();
private:
    Eigen::VectorXd pesos {0};
    Eigen::VectorXd regularizacao {};
    double vies {0};
    int iteracoes {};
};



#endif //SVC_H
