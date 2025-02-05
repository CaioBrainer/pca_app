//
// Created by caiobrainer on 04/02/25.
//

#include "SVC.h"
#include "svm.h"
#include "Eigen/Dense"
#include <iostream>

void SVC::treinoSVC(const Eigen::MatrixXd &matrizAtributos, Eigen::VectorXd &vetorRotulos) {

    int numAmostras = matrizAtributos.rows();
    int numAtributos = matrizAtributos.cols();

    // Criando estruturas do LIBSVM
    struct svm_problem prob;
    struct svm_parameter param;
    struct svm_model* model;
    struct svm_node* x_space = new svm_node[numAmostras * (numAtributos + 1)];

    prob.l = numAmostras;
    prob.y = vetorRotulos.data(); // Usando os dados do Eigen
    prob.x = new svm_node*[numAmostras];

    // Convertendo os dados do Eigen para o formato LIBSVM
    for (int i = 0; i < numAmostras; i++) {
        prob.x[i] = &x_space[i * (numAtributos + 1)];
        for (int j = 0; j < numAtributos; j++) {
            x_space[i * (numAtributos + 1) + j].index = j + 1;
            x_space[i * (numAtributos + 1) + j].value = matrizAtributos(i, j);
        }
        x_space[i * (numAtributos + 1) + numAtributos].index = -1; // Fim da amostra
    }

    // Configurando os parâmetros do SVM
    param.svm_type = C_SVC;
    param.kernel_type = LINEAR;
    param.C = 1.0;
    param.gamma = 0; // Ignorado para kernel linear
    param.cache_size = 10; // Corrigindo erro de cache_size <= 0
    param.eps = 1e-3;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;

    // Verificar se os parâmetros são válidos
    const char *error_msg = svm_check_parameter(&prob, &param);
    if (error_msg) {
        std::cerr << "Erro nos parâmetros: " << error_msg << std::endl;
        return;
    }

    // Treinar o modelo
    this->model = svm_train(&prob, &param);
    // Pesose viés
    double *alpha = this->model->sv_coef[0];
    svm_node **SVs = this->model->SV;

    // Pesos
    this->pesos.resize(numAtributos);
    this->pesos.setZero(); // Inicializa w com zeros
    // Realizando o cálculo dos pesos:
    for (int i = 0; i < this->model->l; i++) { // model->l é o número de SVs
        double coeff = alpha[i]; // Coeficiente do vetor de suporte
        int j = 0;
        while (SVs[i][j].index != -1) { // Percorre os atributos do SV
            this->pesos(SVs[i][j].index - 1) += coeff * SVs[i][j].value;
            j++;
        }
    }

    // Viés
    this->bias = -(this->model->rho[0]);


    std::cout << "Modelo treinado com sucesso!" << std::endl;
    std::cout << "Pesos w:\n" << this->pesos.transpose() << std::endl;
    std::cout << "Bias b: " << bias << std::endl;

    // Limpar memória
    svm_free_and_destroy_model(&model);
    delete[] x_space;
    delete[] prob.x;
}