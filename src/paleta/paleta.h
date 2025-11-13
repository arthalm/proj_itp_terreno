#include <iostream>
#include <fstream>
#include <string>

struct Cor
{
    unsigned char r, g, b;
};

class Paleta
{
    int capacidade;
    int tamanho;
    Cor *cores;

    void aumentarCapacidade()
    {
        capacidade *= 2;
        Cor *novo = new Cor[capacidade];
        for (int i = 0; i < tamanho; i++)
        {
            novo[i] = cores[i];
        }
        delete[] cores;
        cores = novo;
    }

public:
    Paleta(int cap = 2) : capacidade(cap), tamanho(0)
    {
        cores = new Cor[capacidade];
    }

    Paleta(std::string arquivo) : capacidade(2), tamanho(0)
    {
        cores = new Cor[capacidade];
        std::ifstream file(arquivo);
        std::string linha;
        while (std::getline(file, linha))
        {
            if (linha.empty())
            {
                continue;
            }
            if (linha[0] == '#')
            {
                linha.erase(0, 1);
            }
            std::string Ri = linha.substr(0, 2);
            std::string Gi = linha.substr(2, 2);
            std::string Bi = linha.substr(4, 2);

            unsigned char R = std::stoi(Ri, 0, 16);
            unsigned char G = std::stoi(Gi, 0, 16);
            unsigned char B = std::stoi(Bi, 0, 16);

            if (tamanho >= capacidade)
            {
                aumentarCapacidade();
            }

            cores[tamanho] = Cor{R, G, B};
            tamanho++;
        }
    }

    ~Paleta()
    {
        delete[] cores;
    }

    int obterTamanho()
    {
        return tamanho;
    }

    void adicionarCor(Cor cor)
    {
        if (tamanho >= capacidade)
        {
            aumentarCapacidade();
        }
        cores[tamanho] = cor;
        tamanho++;
    }

    Cor obterCor(int n)
    {
        if (n >= tamanho || n < 0)
        {
            Cor corInvalida{0, 0, 0};
            return corInvalida;
        }
        return cores[n];
    }
};