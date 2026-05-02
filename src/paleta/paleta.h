// ============================================================
// Arquivo: paleta.h
// Descrição: declaração da classe "Paleta",
// estrutura que armazena um conjunto de cores,
// permitindo inserção dinâmica e acesso aos elementos
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: novembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#ifndef PALETA_H
#define PALETA_H

#include <string>
#include "../cor.h"

class Paleta
{
    // capacidade máxima atual do array de cores
    int capacidade;

    // quantidade atual de cores armazenadas
    int tamanho;

    // ponteiro para o array dinâmico de cores
    Cor *cores;

    // função que aumenta a capacidade do array
    void aumentarCapacidade();

public:

    // construtor: inicializa a paleta com capacidade = 1
    Paleta(int cap = 1);

    // construtor: inicializa a paleta a partir de um arquivo
    Paleta(std::string arquivo);

    // destrutor: libera a memória alocada
    ~Paleta();

    // retorna a quantidade de cores armazenadas
    int obterTamanho();

    // adiciona uma nova cor à paleta
    void adicionarCor(Cor cor);

    // retorna a cor armazenada na posição n
    Cor obterCor(int n);
};

#endif