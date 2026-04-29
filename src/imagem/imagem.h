#ifndef PALETA_H
#define PALETA_H

// includes necessários agora e nas próximas funções
#include <string>
#include "../cor.h"

using Pixel = Cor;

class Imagem
{
    int altura, largura;
    Pixel **pixels;

    void alocarEspaco(int alt, int larg);

    // lerPPM tambem vai usar isso do destrutor
    void limpar();

public:
    Imagem(int alt = 0, int larg = 0);

    ~Imagem();

    int obterLargura();

    int obterAltura();

    bool pintar(int x, int y, Cor cor);

    Cor obterCor(int x, int y);

    bool lerPPM(std::string arquivo);

    bool salvarPPM(std::string arquivo);
};

#endif