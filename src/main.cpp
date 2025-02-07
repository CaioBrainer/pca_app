#include "PCA.h"
#include "SVC.h"
#include "csv.h"
#include "dadosTabulares.h"
#include <Eigen/Dense>
#include <iostream>
#include <memory>

void printMenu() {
    std::cout << R"(
  __  __                       _____  _____
 |  \/  |                /\   |  __ \|  __ \
 | \  / | ___ _   _     /  \  | |__) | |__) |
 | |\/| |/ _ \ | | |   / /\ \ |  ___/|  ___/
 | |  | |  __/ |_| |  / ____ \| |    | |
 |_|  |_|\___|\__,_| /_/    \_\_|    |_|
)" << "\n";
};

void lerInteiro(std::shared_ptr<int> opcao) {
    while (true) {
        std::cout << "Selecione uma opção: ";
        std::cin >> *opcao;

        if (std::cin.fail()) {  // Se a entrada for inválida (ex: letra, símbolo, etc.)
            std::cin.clear();   // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta entrada inválida
            std::cout << "Entrada inválida! Por favor, digite um número inteiro.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Evita sobras no buffer
            break;  // Sai do loop apenas se a entrada for válida
        }
    }
};

int main() {
    // Instanciando meus objetos
    std::shared_ptr<PCA> modeloPCA = std::make_shared<PCA>();
    std::shared_ptr<SVC> modeloSVC = std::make_shared<SVC>();
    std::shared_ptr<csv> leitorCSV = std::make_shared<csv>();
    std::shared_ptr<Eigen::MatrixXd> matrizDados = std::make_shared<Eigen::MatrixXd>();
    std::shared_ptr<int> opcao = std::make_shared<int>();

    Eigen::VectorXd pesos;
    double vies;
    bool rodando {true};
    //std::make_shared<int> opcao (nullptr);
    //csv *leitorCSV = nullptr;
    //PCA *modeloPCA = nullptr;
    // SVC *modeloSVC = nullptr;

    printMenu();
    while (rodando) {
        std::cout << "--------------------------------" << "\n";
        std::cout << "1) Carregar dados: " << "\n";
        std::cout << "2) Realizar PCA: " << "\n";
        std::cout << "3) Realizar SVC: " << "\n";
        std::cout << "4) Avaliar SVC: " << "\n";
        std::cout << "5) Fechar aplicativo " << "\n";
        std::cout << "--------------------------------" << "\n";


        lerInteiro(opcao);

        switch (*opcao) {
            case 1: {
                std::string nomeArquivo;
                std::cout << "Digite o nome do arquivo csv que deseja carregar (SEM .CSV)" << "\n";
                std::cin >> nomeArquivo;
                auto dados = leitorCSV->lerArquivo("../data/" + nomeArquivo);
                *matrizDados = leitorCSV->paraMatriz(dados);
                break;
            }
            case 2: {
                std::cout << "Iniciando PCA" << std::endl;
                std::cout << "Selecione o número de componentes principais: " << std::endl;

                int componentes{};
                std::cin >> componentes;

                //Preparação de ados pro modelo
                auto numColunas = matrizDados->cols();
                auto atributosMatriz= matrizDados->leftCols(numColunas - 1);
                // Treinamento do modelo
                modeloPCA->fitPCA(atributosMatriz, componentes);

                break;
            }
            case 3: {
                Eigen::VectorXd rotulos = (matrizDados->rightCols(1));
                modeloSVC->treinoSVC(modeloPCA->getMatrizReduzida(), rotulos);
                break;
            }
            case 4: {
                rodando = false;
                break;
            }
            default: {
                std::cout << "Opção inválida." << "\n";
                std::cout << "Escolha uma das opções abaixo: " << "\n";
            }
        }
    };

    // dadosTabulares dados = leitorCSV->lerArquivo("../data/ca_amphiboles");
    // Eigen::MatrixXd dadosMatriz = leitorCSV->paraMatriz(dados);
    //
    // // Preparando os data para treinamento:
    // Eigen::MatrixXd atributosMatriz = dadosMatriz.leftCols(dadosMatriz.cols()-1);
    // Eigen::VectorXd rotulosVetor = dadosMatriz.rightCols(1);
    //
    // std::cout << "Iniciando PCA" << std::endl;
    // modeloPCA->fitPCA(atributosMatriz, 2);
    // std::cout << "Iniciando teste do SVM com Eigen..." << std::endl;
    // modeloSVC->treinoSVC(modeloPCA->getMatrizReduzida(), rotulosVetor);
    // std::cout << "Treino realizado com sucesso!" << std::endl;
    // return 0;

     return 0;
}
