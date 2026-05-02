// ============================================================
// Arquivo: terreno.h
// Descrição: declaração da classe "Terreno",
// estrutura que representa um mapa de alturas (heightmap),
// permitindo geração de terreno usando o algoritmo
// diamond-square e conversão para imagem
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: dezembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#ifndef TERRENO_H
#define TERRENO_H

#include "../imagem/imagem.h"
#include <string>

class Terreno
{
    // expoente usado para calcular dimensões (2^n + 1)
    int expoente;

    // dimensões do mapa
    int altura, largura;

    // matriz dinâmica que armazena as alturas do terreno
    int **mapa;

    // semente inicial (permite reproduzir o mesmo terreno)
    unsigned int sementeInicial;

    // semente atual usada pelo gerador pseudoaleatório
    unsigned int semente;

    // limites de altura do terreno
    int altMinimo, altMaximo;

    // aloca memória para o mapa de alturas
    void alocarEspaco(int alt, int larg);

    // libera memória do mapa
    void limpar();

    // calcula 2^n + 1
    int potencia(int n);

    // gerador de números pseudoaleatórios (LCG)
    int gerarNumero();

    // etapa diamond
    // vertical e horizontal
    void diamond(int linha, int coluna, int alcance, int variacao);

    // etapa square
    void square(int linha, int coluna, int alcance, int variacao);

    // algoritmo principal de geração de terreno
    void diamondSquare(int tamanho, int variacao);

public:

    // construtor: inicializa o terreno com parâmetros dados
    Terreno(int exp = 0, int seed = 1, int min = 0, int max = 100);

    // destrutor: libera memória
    ~Terreno();

    // retorna largura do terreno
    int obterLargura();

    // retorna altura do terreno
    int obterAltura();

    // retorna a semente inicial
    int obterSemente();

    // retorna altura mínima
    int obterAltMinimo();

    // retorna altura máxima
    int obterAltMaximo();

    // retorna a altura em uma posição específica
    int obterAltura(int lin, int col);

    // insere uma altura no mapa
    void inserirAltura(int lin, int col, int alt);

    // gera valor aleatório dentro do intervalo global [altMinimo, altMaximo]
    int aleatorio();

    // gera valor aleatório dentro de um intervalo específico
    int aleatorio(int minimo, int maximo);

    // gera o mapa completo usando diamond-square
    void gerarMapa();

    // converte o terreno em imagem usando uma paleta de cores
    Imagem carregarTerreno(std::string arquivoPALETA, float fator, int dist, int map);

    // salva o mapa de alturas em arquivo
    bool salvarHeightMap(std::string arquivo);

    // lê um mapa de alturas de arquivo
    bool lerHeightMap(std::string arquivo);
};

#endif