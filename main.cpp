#include <iostream>
#include <string>
#include "csv.h"
#include "dadosTabulares.h"
#include <limits>
#include <Eigen/Dense>
#include "PCA.h"

int main() {

    // Variáveis globais que preciso
    bool running {true};
    int opcao {};
    Eigen::Index componentes;
    dadosTabulares dados;
    PCA meuPCA;
    Eigen::MatrixXd matriz;

    std::cout << "*******************************************************************" << "\n";
    std::cout << "MINHA APLICACAO DE TESTES" << "\n";
    std::cout << "*******************************************************************" << "\n";
    while (running) {
        std::cout << "Selecione uma das opcoes: " << "\n";
        std::cout << "*******************************************************************" << "\n";
        std::cout << "1 - Ler arquivo CSV" << "\n";
        std::cout << "2 - Ver arquivo CSV" << "\n";
        std::cout << "3 - Realizar PCA" << "\n";
        std::cout << "4 - Salvar dados brutos em .CSV" << "\n";
        std::cout << "5 - Salvar autovetores em .CSV" << "\n";
        std::cout << "6 - Salvar resultado do PCA em .CSV" << "\n";
        std::cout << "7 - Sair do aplicativo" << "\n";
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
                    matriz = csv::paraMatriz(dados);
                    std::cout << "Quantos componentes? ";
                    std::cin >> componentes;
                    meuPCA.fitPCA(matriz, componentes);
                    break;
                }

                case 4: {
                    break;
                }

                case 5: {
                    csv::salvarArquivo(dados, meuPCA.getAutovetoresOrdenados());
                    break;
                }

                case 6: {
                    csv::salvarArquivo(meuPCA.getMatrizReduzida());
                    break;
                }

                case 7: {
                    running = false;
                    break;
                }

                default: {
                    std::cout << "Opcao invalida" << "\n";
                    break;
                };
            }
        }
    }
    return 0;
}