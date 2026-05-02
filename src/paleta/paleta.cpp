// ============================================================
// Arquivo: paleta.cpp
// Descrição: implementação da classe "Paleta",
// estrutura que armazena um conjunto de cores,
// permitindo inserção dinâmica e acesso aos elementos
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: novembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#include "paleta.h"
#include <iostream>
#include <fstream>
#include <string>

// função que dobra a capacidade do array de cores
// cria um novo array maior e copia os elementos antigos
void Paleta::aumentarCapacidade()
{
    capacidade *= 2;
    Cor *novo = new Cor[capacidade];

    // copia as cores antigas para o novo array
    for (int i = 0; i < tamanho; i++)
    {
        novo[i] = cores[i];
    }

    // libera memória antiga
    delete[] cores;

    // atualiza o ponteiro
    cores = novo;
}


// construtor padrão
// inicializa a paleta com capacidade inicial e tamanho 0
Paleta::Paleta(int cap) : capacidade(cap), tamanho(0)
{
    cores = new Cor[capacidade];
}

// construtor que lê cores de um arquivo
// espera linhas no formato hexadecimal (#RRGGBB)
Paleta::Paleta(std::string arquivo) : capacidade(1), tamanho(0)
{
    cores = new Cor[capacidade];

    // abre o arquivo
    std::ifstream file(arquivo);

    // verifica se abriu corretamente
    if (!file.is_open())
    {
        std::cerr << "Erro: nao foi possivel abrir " << arquivo << std::endl;
        return;
    }

    std::string linha;

    // lê o arquivo linha por linha
    while (std::getline(file, linha))
    {
        // valida formato (#RRGGBB)
        if (linha.size() != 7 || linha[0] != '#' || linha.empty())
        {
            continue;
        }

        // separa o hexadecimal em pares RR GG BB
        std::string Re = linha.substr(1, 2);
        std::string Gr = linha.substr(3, 2);
        std::string Bl = linha.substr(5, 2);

        // converte hexadecimal para inteiro
        unsigned char R = std::stoi(Re, 0, 16);
        unsigned char G = std::stoi(Gr, 0, 16);
        unsigned char B = std::stoi(Bl, 0, 16);

        // aumenta capacidade se necessário
        if (tamanho >= capacidade)
        {
            aumentarCapacidade();
        }

        // adiciona a cor na paleta
        cores[tamanho] = Cor{R, G, B};
        tamanho++;
    }
}

// destrutor: libera memória alocada
Paleta::~Paleta()
{
    delete[] cores;
}

// retorna a quantidade de cores armazenadas
int Paleta::obterTamanho(){return tamanho;}

// adiciona uma nova cor à paleta
void Paleta::adicionarCor(Cor cor)
{
    if (tamanho >= capacidade)
    {
        aumentarCapacidade();
    }
    cores[tamanho] = cor;
    tamanho++;
}

// retorna a cor na posição n
// caso o índice seja inválido, retorna preto (0,0,0)
Cor Paleta::obterCor(int n)
{
    if (n >= tamanho || n < 0)
    {
        std::cerr << "Erro: indice " << n << " fora dos limites (0-" << tamanho - 1 << ")\n";
        return Cor{0, 0, 0};
    }
    return cores[n];
}