// ============================================================
// Arquivo: imagem.h
// Descrição: declaração da classe "Imagem",
// estrutura que representa uma imagem 2D baseada em pixels,
// permitindo manipulação e leitura/escrita no formato PPM
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: dezembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#ifndef IMAGEM_H
#define IMAGEM_H

#include <string>
#include "../cor.h"

// define Pixel como Cor
using Pixel = Cor;

class Imagem
{
    // dimensões da imagem
    int altura, largura;

    // matriz dinâmica de pixels (array de ponteiros)
    Pixel **pixels;

    // aloca memória para a matriz de pixels
    void alocarEspaco(int alt, int larg);

    // libera a memória alocada (usado no destrutor e em leituras)
    void limpar();

public:
    // construtor: cria uma imagem com dimensões dadas
    Imagem(int alt = 0, int larg = 0);

    // destrutor: libera memória
    ~Imagem();

    // retorna a largura da imagem
    int obterLargura();

    // retorna a altura da imagem
    int obterAltura();

    // altera a cor de um pixel (x, y)
    // retorna false se a posição for inválida
    bool pintar(int x, int y, Cor cor);

    // retorna a cor do pixel (x, y)
    Cor obterCor(int x, int y);

    // lê uma imagem no formato PPM a partir de arquivo
    bool lerPPM(std::string arquivo);

    // salva a imagem atual no formato PPM
    bool salvarPPM(std::string arquivo);
};

#endif