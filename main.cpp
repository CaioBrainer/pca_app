#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "dadosTabulares.h"
#include <limits>
#include <Eigen/Dense>

/*
 *Tô afim de implementar um PCA no C++, então... Vou ir fazendo aos poucos enquanto reviso programação em C++.
 * Inicialmente criei uma estrutura básica e uma classe simples para poder realizar a leitura e escrita de arquivos
 * em CSV. Agora irei revisar os aspectos relacionados à algebra linear e ver as bibliotecas que posso utilizar para não
 * ter que implementar isso do zero (Não tenho tanto tempo assim =D).
 */

/**
 * @brief Função criada para centralizar os dados da matriz em torno das médias em cada coluna.
 * @param matriz A matriz que terá seus dados centralizados.
 */
Eigen::MatrixXd centralizaDadosMatriz(Eigen::MatrixXd &matriz) {

    Eigen::VectorXd medias = matriz.colwise().mean();
    Eigen::MatrixXd C (matriz.rows(), matriz.cols());

    for (Eigen::Index i = 0; i < matriz.rows(); ++i) {
        for (Eigen::Index j = 0; j < matriz.cols(); ++j) {
            C(i,j) = matriz(i,j) - medias(j);
        }
    };
    return C;
};

/**
 * @brief Função criada para calcular a matriz de covariância de uma matriz com dimensões (mxn).
 * @param matrizCentralizada Matriz com os dados centralizados em torno da média.
 * @return Uma matriz de covariância com dimensão (nxn).
 */
Eigen::MatrixXd matrizCov(Eigen::MatrixXd &matrizCentralizada) {

    const int m = matrizCentralizada.rows();
    Eigen::MatrixXd C =  (matrizCentralizada.transpose() * matrizCentralizada) / (m-1);
    return C;
};

/**
 * @brief Realiza o cálculo de autovetores e autovalores de uma matrix de covariância.
 * @param matrizCov Matriz de covariância com dimensões nxn.
 * @return Uma matriz com os autovetores e autovalores, que podem ser acessados com os métodos: .eigenvalues() e
 * .eigenvectors().
 */
Eigen::EigenSolver<Eigen::MatrixXd> autoDecomposicao(const Eigen::MatrixXd &matrizCov) {
    Eigen::EigenSolver<Eigen::MatrixXd> solver(matrizCov);
    return solver;
};

/**
 *
 * @param autoValVec Matriz decomposta em autovetores e autovalores
 * @return Matriz de autovetores ordenada conforme os autovalores mais importantes.
 */
Eigen::MatrixXd vetoresImportantes(const Eigen::EigenSolver<Eigen::MatrixXd> &autoValVec) {


    // Vetor de autovalores
    std::vector<std::pair<double, int>> autovaloresIndices;
    for (int i = 0; i < autoValVec.eigenvalues().real().size(); ++i) {
        autovaloresIndices.emplace_back(autoValVec.eigenvalues().real()(i), i);
    };
    std::ranges::sort(autovaloresIndices, std::ranges::greater()); // Aqui vai ordenar o bicho

    // Matriz de autovetores
    Eigen::MatrixXd matrizOrdenada {autoValVec.eigenvectors().rows(), autoValVec.eigenvectors().cols()};

    // for (Eigen::Index i = 0; i < autoValVec.eigenvectors().rows(); i++) {
    //     for (Eigen::Index j = 0; j < autovaloresIndices.size(); j++) {
    //         matrizOrdenada(i, j) = autoValVec.eigenvectors().real()(i,autovaloresIndices.at(j).second);
    //     };
    // };

    for (Eigen::Index j = 0; j < autovaloresIndices.size(); j++) {
        matrizOrdenada.col(j) = autoValVec.eigenvectors().real().col(autovaloresIndices.at(j).second);
    };

    return matrizOrdenada;
};

// Partes que serão utilizadas para criar a função que ordena os autovalores e autovetores.

// std::vector<std::pair<double, int>> autovaloresIndices;
// for (int i = 0; i < E.eigenvalues().real().size(); ++i) {
//     autovaloresIndices.emplace_back(E.eigenvalues().real()(i), i);
// };
//
// std::ranges::sort(autovaloresIndices, std::ranges::greater());
// for (const auto &[valor, chave]:autovaloresIndices) {
//     std::cout << valor << " - " << chave << "\n";
// };

int main() {

    /*
     * Estrutura básica do aplicativo com algumas funções já criadas. Irei substituir os vetores por matrizes 2D da
     * biblioteca eigen.
     */

    bool running {true};
    int opcao {};
    dadosTabulares dados;

    std::cout << "*******************************************************************" << "\n";
    std::cout << "MINHA APLICACAO DE TESTES" << "\n";
    std::cout << "*******************************************************************" << "\n";
    while (running) {
        std::cout << "Selecione uma das opcoes: " << "\n";
        std::cout << "*******************************************************************" << "\n";
        std::cout << "1 - Ler arquivo CSV" << "\n";
        std::cout << "2 - Ver arquivo CSV" << "\n";
        std::cout << "3 - Realizar PCA" << "\n";
        std::cout << "5 - Sair do aplicativo" << "\n";
        std::cout << "*******************************************************************" << "\n";
        std::cout << "digite a opcao desejada:";
        std::cin >> opcao;
        /* Aprendi que std::cin não lança exceções!
         * temos que usar a função std::cin.fail() para verificar se há problemas!
         */


        // Verificar se a entrada falhou
        if (std::cin.fail()) {
            std::cout << "Entrada invalida!\n";
            std::cin.clear(); // Limpar o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar a entrada inválida do buffer
        } else {
            switch (opcao) {
                case 1: {
                    std::string nome_arquivo {};
                    std::cout << "Digite o nome ou endereço do arquivo: ";
                    std::cin >> nome_arquivo;
                    std::string caminho_arquivo {"../" + nome_arquivo};
                    dados = csv::lerArquivo(caminho_arquivo);
                    break;
                }

                case 2: {
                    csv::visualizarArquivo(dados);
                    break;
                }

                case 3: {
                    Eigen::MatrixXd M = csv::paraMatriz(dados);
                    auto M_centralizada = centralizaDadosMatriz(M);
                    auto M_covariancia = matrizCov(M_centralizada);
                    auto M_decomposicao = autoDecomposicao(M_covariancia);
                    std::cout << M_decomposicao.eigenvectors().real() << std::endl;

                    break;
                }

                case 4: {
                    running = false;
                    break;
                }

                case 5: {
                    running = false;
                    break;
                }


                default: {
                    std::cout << "Opcao invalida" << "\n";
                };
            }
        }
    }
    return 0;
}

// TIP Press Atalho para Debug: Ctrl + F9
// Para adicionar pontos de quebra é usado Ctrl + F8 (na linha)