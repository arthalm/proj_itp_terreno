#include <iostream>
#include <fstream>
#include <string>

struct Cor
{
    unsigned char r, g, b; // unsigned char vao de 0 a 255
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
    // construtor normal
    Paleta(int cap = 1) : capacidade(cap), tamanho(0)
    {
        cores = new Cor[capacidade];
    }

    // construtor do arquivo
    Paleta(std::string arquivo) : capacidade(1), tamanho(0)
    {
        cores = new Cor[capacidade];

        std::ifstream file(arquivo); // recebe um arquivo por referencia e armazena em file

        if (!file.is_open()) {
            std::cerr << "Erro: nao foi possivel abrir " << arquivo << std::endl;
            return;
        }

        std::string linha;
        while (std::getline(file, linha))
        { // pega uma linha do arquivo e armazena em linha
            if (linha.size() != 7 || linha[0] != '#' || linha.empty())
            {
                continue;
            }

            // pega o codigo e separa em pares RR GG BB
            std::string Re = linha.substr(1, 2);
            std::string Gr = linha.substr(3, 2);
            std::string Bl = linha.substr(5, 2);

            // converte a string com hexadecimal em int (stoi), e é recebido pelas variaveis
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
            std::cerr << "Erro: indice " << n << " fora dos limites (0-" << tamanho-1 << ")\n";
            return Cor{0, 0, 0};
        }
        return cores[n];
    }
};