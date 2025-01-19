//
// Created by caiogarnier on 17/01/2025.
//

#ifndef DADOSTABULARES_H
#define DADOSTABULARES_H

#include <string>
#include <vector>


// Estrutura criada para armazenar os arquivos lidos com a classe cvs

struct dadosTabulares {
    std::vector<std::string> cabecalho;
    std::vector<std::vector<double>> dadosNumericos;

    // Método para preencher o cabeçalho
    void inserirCabecalho(const std::vector<std::string> &cabecalhoArquivo) {
        for (const auto &coluna: cabecalhoArquivo) {
            this->cabecalho.push_back(coluna); // Mudar para std::move posteriormente
        }

    }

    // Método para preencher os dados numéricos
    void inserirDados(const std::vector<std::vector<double>>& vetorVetores) {
        for (const auto &vetor: vetorVetores) {
            this->dadosNumericos.push_back(vetor); /* Mudar para std::move posteriormente,
                                                da forma que está os dados estão sendo copiados*/
        }
    }
};


#endif //DADOSTABULARES_H
