#include <iostream>
#include <Eigen/Dense>
#include "svm.h"
#include "SVC.h"
#include "csv.h"
#include "dadosTabulares.h"
#include "PCA.h"

int main() {
    // Instanciando meus objetos
    csv leitorCSV;
    PCA pca;
    SVC modeloSVC;

    dadosTabulares dados = leitorCSV.lerArquivo("../dados/ca_amphiboles");
    Eigen::MatrixXd dadosMatriz = leitorCSV.paraMatriz(dados);
    Eigen::MatrixXd atributosMatriz = dadosMatriz.leftCols(dadosMatriz.cols()-1);



    Eigen::VectorXd rotulosVetor = dadosMatriz.rightCols(1);

    std::cout << "Iniciando PCA" << std::endl;
    pca.fitPCA(atributosMatriz, 2);
    std::cout << "Iniciando teste do SVM com Eigen..." << std::endl;
    modeloSVC.treinoSVC(pca.getMatrizReduzida(), rotulosVetor);
    std::cout << "Treino realizado com sucesso!" << std::endl;
    return 0;
}
