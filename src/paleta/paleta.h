#ifndef PALETA_H
#define PALETA_H

#include <string>
#include "../cor.h"

class Paleta
{
    int capacidade;
    int tamanho;
    Cor *cores;

    void aumentarCapacidade();

public:
    Paleta(int cap = 1);

    Paleta(std::string arquivo);

    ~Paleta();

    int obterTamanho();

    void adicionarCor(Cor cor);

    Cor obterCor(int n);
};

#endif