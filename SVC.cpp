//
// Created by caiobrainer on 01/02/25.
//

#include "SVC.h"

#include <Eigen/Dense>
#include <iostream>

void SVC::treino(const Eigen::MatrixXd &matrizDados, const Eigen::VectorXd &vetorRotulos,
    const double &valorRegularizacao, double taxaAprendizado) {

    int linhas = matrizDados.rows();
    int colunas = matrizDados.cols();

    this->pesos = Eigen::VectorXd::Zero(colunas);
    this->iteracoes = 1000;
    this->vies = 0;

    for (int i = 0; i < iteracoes; i++) {
        for (int j = 0; j < linhas; j++) {
            double condicao = vetorRotulos(i) * matrizDados.row(i) * this->pesos + vies;
            if (condicao >= 1) {
                this->pesos = this->pesos - (taxaAprendizado * 2 * this->pesos); // poderia ser -= também
            } else {
                this->pesos = taxaAprendizado * (2 * this->pesos - valorRegularizacao * vetorRotulos(i) * matrizDados.row(i).transpose());
                this->vies =taxaAprendizado * (-valorRegularizacao * vetorRotulos(i));
            }
        }
    }
};

std::vector<int> SVC::previsao(const Eigen::MatrixXd &matrizDados) {
    std::vector<int> resultados;

    for (Eigen::Index i = 0 ; i < matrizDados.rows(); i++) {
        Eigen::VectorXd vetorDados = matrizDados.row(i);
        double previsao = this->pesos.dot(vetorDados) + this->vies;

        if (previsao >= 0) {
            resultados.push_back(1);
        } else {
            resultados.push_back(-1);
        }
    }
    return resultados;
};

void SVC::getPesos() {
    for (Eigen::Index i = 0; i < this->pesos.size(); i++) {
        std::cout << "w" << i << ": " << this->pesos(i)<< "\n";
    }
};

void SVC::getVies() {
    std::cout << "vies: " << this->vies << "\n";
};


