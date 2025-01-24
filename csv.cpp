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
    std::ifstream arquivo(fileName);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << fileName << "\n";
    }


    // std::shared_ptr<int> ptr = std::make_shared<int>(42);

    // auto cabecalho = std::make_shared<std::vector<std::string>>();
    // auto dadosNumericos = std::make_shared<std::vector<std::vector<double>>>();
    // std::vector<std::string> cabecalho;
    // std::vector<std::vector<double>> dadosNumericos;
    dadosTabulares dadosTabulares;
    std::string linha;


    /* O bloco de código abaixo funciona da seguinte forma:
     * O código verifica se há uma linha no arquivo (cabeçalho), e caso afirmativo
     * ele irá criar um objeto stringstream com a linha e instanciar uma string para o dado na coluna.
     * Após isso, o código irá entrar em loop, onde enquanto houver colunas no código,
     * ele irá separar as strings conforme o separador ',', e adicionar cada palavra à variável
     * dado coluna, que será inserida no vetor de strings definido no início da execução da função.
     */

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

    // dadosTabulares dadosTabulares;
    // dadosTabulares.cabecalho = std::move(cabecalho);
    // dadosTabulares.dadosNumericos = std::move(dadosNumericos);
    // dadosTabulares.inserirCabecalho(cabecalho);
    // dadosTabulares.inserirDados(dadosNumericos);


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
