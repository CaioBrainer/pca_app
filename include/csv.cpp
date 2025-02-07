//
// Created by caiogarnier on 16/01/2025.
//

#include "csv.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "dadosTabulares.h"
#include <Eigen/Dense>


dadosTabulares csv::lerArquivo(const std::string &fileName) {
    std::string caminho {fileName + ".csv"};

    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo: " << caminho << "\n";
    }

     /* O bloco de código abaixo funciona da seguinte forma:
     * O código verifica se há uma linha no arquivo (cabeçalho), e caso afirmativo
     * ele irá criar um objeto stringstream com a linha e instanciar uma string para o dado na coluna.
     * Após isso, o código irá entrar em loop, onde enquanto houver colunas no código,
     * ele irá separar as strings conforme o separador ',', e adicionar cada palavra à variável
     * dado coluna, que será inserida no vetor de strings definido no início da execução da função.
     */

    dadosTabulares dadosTabulares;
    std::string linha;
    if (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string dadoColuna;

        while (std::getline(ss, dadoColuna, ',')) {
            dadosTabulares.cabecalho.push_back(dadoColuna);
        }
    }

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string dadoColuna;
        std::vector<double> dadosLinha;

        while (std::getline(ss, dadoColuna, ',')) {
            double dadoFloat;
            try {
                dadoFloat = std::stod(dadoColuna);
            } catch (...) {
                dadoFloat = 0.0;
            }
            dadosLinha.push_back(dadoFloat);
        }
        dadosTabulares.dadosNumericos.push_back(dadosLinha);
    }

    return dadosTabulares;


}

void csv::visualizarArquivo(const dadosTabulares &dadosTabulares) {
    for (auto &dado : dadosTabulares.cabecalho) {
        std::cout << dado << " ";
    };
    std::cout << "\n";

    for (const auto &vetor : dadosTabulares.dadosNumericos) {
        for (const auto &dado : vetor) {
            std::cout << dado << " ";
        }
        std::cout << "\n";
    }
}

Eigen::MatrixXd csv::paraMatriz(const dadosTabulares &dadosTabulares) {

    size_t linhas {dadosTabulares.dadosNumericos.size()};
    size_t colunas {dadosTabulares.dadosNumericos.at(0).size()};
    Eigen::MatrixXd matriz (linhas, colunas);

    for (Eigen::Index i = 0; i < linhas; i++) {
        for (Eigen::Index j = 0; j < colunas; j++) {
            matriz(i,j) = dadosTabulares.dadosNumericos.at(i)[j];
        }
    }

    return matriz;
}

void csv::salvarArquivo(const dadosTabulares &dadosTabulares) {
    std::string nomeArquivo;
    std::cout << "Digite o nome do arquivo que deseja salvar: ";
    std::cin >> nomeArquivo;

    std::ofstream arquivoSaida{"../" + nomeArquivo + ".csv"};

    if (arquivoSaida.is_open()) {
        const size_t totalColunas = dadosTabulares.cabecalho.size();
        size_t colunaAtual = 0;

        for (const auto &coluna : dadosTabulares.cabecalho) {
            arquivoSaida << coluna;
            // Aqui que ele coloca a vírgula após cada coluna
            if (++colunaAtual < totalColunas) {
                arquivoSaida << ",";
            }
        }
        std::cout << "\n";


        for (const auto &vetor : dadosTabulares.dadosNumericos) {
            colunaAtual = 0;
            for (const auto &dado : vetor) {
                arquivoSaida << dado;
                if (++colunaAtual < totalColunas) {
                    arquivoSaida << ",";
                }
            }
            arquivoSaida << "\n";
        }

    } else {
        std::cerr << "Erro ao escrever no arquivo: " << nomeArquivo << "\n";
        return;
    }

    arquivoSaida.close();
    std::cout << "Arquivo salvo com sucesso: " << nomeArquivo << ".csv\n";
}

void csv::salvarArquivo(const dadosTabulares &dadosTabulares, const Eigen::MatrixXd &matrizPCA) {
    std::string nomeArquivo;
    std::cout << "Digite o nome do arquivo para salvar o resultado do PCA: ";
    std::cin >> nomeArquivo;

    std::ofstream arquivoSaida{"../" + nomeArquivo + ".csv"};

    try {
        if (arquivoSaida.is_open()) {
            const size_t totalColunas = matrizPCA.cols();
            size_t colunaAtual = 0;

            for (const auto &coluna : dadosTabulares.cabecalho) {
                arquivoSaida << coluna;
                // Aqui que ele coloca a vírgula após cada coluna
                if (++colunaAtual < totalColunas) {
                    arquivoSaida << ",";
                }
            }
            arquivoSaida << "\n"; //Quebra de linha do cabeçalho

            for (Eigen::Index i = 0; i < matrizPCA.rows(); i++) {
                colunaAtual = 0;
                for (Eigen::Index j = 0; j < matrizPCA.cols(); j++) {
                    arquivoSaida << matrizPCA(i, j);
                    // Aqui que ele coloca a vírgula após cada coluna
                    if (++colunaAtual < totalColunas) {
                        arquivoSaida << ",";
                    }
                }
                arquivoSaida << "\n";
            }

        } else {
            std::cerr << "Erro ao salvar arquivo: " << nomeArquivo << "\n";
            return;
        }
    }

    catch (...) {
        std::cerr << "Erro desconhecido ocorreu.\n";
    }

    arquivoSaida.close();
}

void csv::salvarArquivo(const Eigen::MatrixXd &matrizPCA) {
    std::string nomeArquivo;
    std::cout << "Digite o nome do arquivo para salvar o resultado do PCA: ";
    std::cin >> nomeArquivo;

    std::ofstream arquivoSaida{"../" + nomeArquivo + ".csv"};

    try {
        if (arquivoSaida.is_open()) {
            const size_t totalColunas = matrizPCA.cols();
            size_t colunaAtual = 0;

            for (Eigen::Index i = 0; i < totalColunas; i++) {
                std::string coluna = "PC" + std::to_string(i+1);
                arquivoSaida << coluna;
                // Aqui que ele coloca a vírgula após cada coluna
                if (++colunaAtual < totalColunas) {
                    arquivoSaida << ",";
                }
            }
            arquivoSaida << "\n"; //Quebra de linha do cabeçalho

            for (Eigen::Index i = 0; i < matrizPCA.rows(); i++) {
                colunaAtual = 0;
                for (Eigen::Index j = 0; j < matrizPCA.cols(); j++) {
                    arquivoSaida << matrizPCA(i, j);
                    // Aqui que ele coloca a vírgula após cada coluna
                    if (++colunaAtual < totalColunas) {
                        arquivoSaida << ",";
                    }
                }
                arquivoSaida << "\n";
            }

        } else {
            std::cerr << "Erro ao salvar arquivo: " << nomeArquivo << "\n";
            return;
        }
    }

    catch (...) {
        std::cerr << "Erro desconhecido ocorreu.\n";
    }

    arquivoSaida.close();
}


