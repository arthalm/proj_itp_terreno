#ifndef TERRENO_H
#define TERRENO_H

#include "../imagem/imagem.h"
#include <string>

class Terreno
{
    int expoente, altura, largura, **mapa;
    unsigned int sementeInicial;
    unsigned int semente;
    int altMinimo, altMaximo;

    void alocarEspaco(int alt, int larg);

    void limpar();

    int potencia(int n);

    // metodo LCG
    int gerarNumero();

    void diamond(int linha, int coluna, int alcance, int variacao);

    void square(int linha, int coluna, int alcance, int variacao);

    void diamondSquare(int tamanho, int variacao);

public:

    Terreno(int exp = 0, int seed = 1, int min = 0, int max = 100);

    ~Terreno();

    int obterLargura();
    int obterAltura();

    int obterSemente();

    int obterAltMinimo();

    int obterAltMaximo();

    int obterAltura(int lin, int col);

    void inserirAltura(int lin, int col, int alt);

    int aleatorio();

    int aleatorio(int minimo, int maximo);

    void gerarMapa();

    Imagem carregarTerreno(std::string arquivoPALETA, float fator, int dist, int map);

    bool salvarHeightMap(std::string arquivo);

    bool lerHeightMap(std::string arquivo);
};

#endif