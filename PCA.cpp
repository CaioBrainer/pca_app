//
// Created by caiogarnier on 28/01/2025.
//

#include "PCA.h"
#include <iostream>

PCA::PCA() {

};

void PCA::centralizaDadosMatriz(const Eigen::MatrixXd &matriz, std::string metodo) {
    if (metodo == "mediaCentro") {
        Eigen::VectorXd medias = matriz.colwise().mean();
        this->matrizCentralizada.resize(matriz.rows(), matriz.cols());

        for (Eigen::Index i = 0; i < matriz.rows(); ++i) {
            for (Eigen::Index j = 0; j < matriz.cols(); ++j) {
                this->matrizCentralizada(i,j) = matriz(i,j) - medias(j);
            }
        };
    }

    if (metodo == "zScore") {
        int rows = matriz.rows();
        int cols = matriz.cols();

        this->matrizCentralizada.resize(matriz.rows(), matriz.cols());

        for (int j = 0; j < cols; ++j) {
            double mean = matriz.col(j).mean();  // Média de cada coluna da matriz
            double stddev = sqrt((matriz.col(j).array() - mean).square().sum() / (rows - 1)); // Desvio padrão

            if (stddev != 0) {
                this->matrizCentralizada.col(j) = (matriz.col(j).array() - mean) / stddev;
            } else {
                this->matrizCentralizada.col(j).setZero(); // Se o desvio padrão for zero, a coluna vira zero
            }
        }
    }
};


void PCA::matrizCov() {
    const int m = this->matrizCentralizada.rows();
    this->matrizCovariancia =  (matrizCentralizada.transpose() * matrizCentralizada) / (m-1);
};

void PCA::autoDecomposicao() {
    this->matrizDecomposta = Eigen::EigenSolver<Eigen::MatrixXd> (this->matrizCovariancia);
};

void PCA::vetoresImportantes() {

    // Vetor de autovalores
    std::vector<std::pair<double, int>> autovaloresIndices;
    for (int i = 0; i < this->matrizDecomposta.eigenvalues().real().size(); ++i) {
        autovaloresIndices.emplace_back(this->matrizDecomposta.eigenvalues().real()(i), i);
    };
    std::ranges::sort(autovaloresIndices, std::ranges::greater()); // Aqui vai ordenar o bicho

    // Matriz de autovetores
    this->autoVetoresOrdenados.resize(this->matrizDecomposta.eigenvectors().rows(), this->matrizDecomposta.eigenvectors().cols() ); //Eigen::MatrixXd matrizOrdenada {autoValVec.eigenvectors().rows(), autoValVec.eigenvectors().cols()};

    for (Eigen::Index j = 0; j < autovaloresIndices.size(); j++) {
        this->autoVetoresOrdenados.col(j) = this->matrizDecomposta.eigenvectors().real().col(autovaloresIndices.at(j).second);
    };

};

void PCA::fitPCA(const Eigen::MatrixXd &matriz, const Eigen::Index &componentes) {
    this->centralizaDadosMatriz(matriz);
    this->matrizCov();
    this->autoDecomposicao();
    this->vetoresImportantes();


    this->matrizReduzida.resize(this->autoVetoresOrdenados.rows(), componentes);

    try {
        if (componentes > this->autoVetoresOrdenados.cols()) {
            throw std::invalid_argument("Valor de k superior ao número de colunas da matriz.");
        }
        Eigen::MatrixXd const kAutovetores = this->autoVetoresOrdenados.leftCols(componentes); // Sugestão mais performática do chatgpt
        this->matrizReduzida = this->matrizCentralizada * kAutovetores;
    }

    catch (const std::invalid_argument &e) {
        std::cerr << "Erro: " << e.what() << "\n";
    }

    catch (const std::exception &e) {
        // Captura outras exceções padrão do C++
        std::cerr << "Erro inesperado: " << e.what() << "\n";
    }

    catch (...) {
        // Captura qualquer outro tipo de exceção
        std::cerr << "Erro desconhecido ocorreu.\n";
    }
}

Eigen::MatrixXd PCA::getMatrizReduzida() {
    return this->matrizReduzida;
};

Eigen::MatrixXd PCA::getAutovetoresOrdenados() {
    return this->autoVetoresOrdenados;
};
