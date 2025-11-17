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
        capacidade += 1;
        Cor *novo = new Cor[capacidade];
        for (int i = 0; i < tamanho; i++)
        {
            novo[i] = cores[i];
        }
        delete[] cores;
        cores = novo;
    }

public:
    Paleta(int cap = 1) : capacidade(cap), tamanho(0)
    {
        cores = new Cor[capacidade];
    }

    Paleta(std::string arquivo) : capacidade(1), tamanho(0)
    {
        cores = new Cor[capacidade];
        std::ifstream file(arquivo);
        std::string linha;
        while (std::getline(file, linha))
        {
            if (linha.size() != 7 || linha[0] != '#' || linha.empty())
            {
                continue;
            }

            std::string Re = linha.substr(1, 2);
            std::string Gr = linha.substr(3, 2);
            std::string Bl = linha.substr(5, 2);

            unsigned char R = std::stoi(Re, 0, 16);
            unsigned char G = std::stoi(Gr, 0, 16);
            unsigned char B = std::stoi(Bl, 0, 16);

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