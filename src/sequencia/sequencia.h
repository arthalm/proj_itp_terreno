#include <iostream>

template <typename S> // Para usar tipos diferentes de dados
class Sequencia
{
    int capacidade;
    int quantidade;
    S *dados;

    // criar funçao que aumenta tamanho
    void aumentarCapacidade()
    {
        capacidade *= 2;
        S *novo = new S[capacidade];
        for (int i = 0; i < quantidade; i++)
        {
            novo[i] = dados[i];
        }
        delete[] dados;
        dados = novo;
    }

public:
    // inicialização
    Sequencia(int cap = 2) : capacidade(cap), quantidade(0)
    {
        dados = new S[capacidade];
    }

    // destrutor
    ~Sequencia()
    {
        delete[] dados;
    }

    int obterTamanho()
    {
        return quantidade;
    }

    void adicionar(S n)
    {
        if (quantidade >= capacidade)
        {
            // chamar a funçao que aumenta tamanho
            aumentarCapacidade();
        }
        dados[quantidade] = n;
        quantidade++;
    }

    // método de consulta/alteração de valor dado um índice da sequência, com verificador de existência do índice
    S &operator[](int indice)
    {
        if (indice < 0 || indice >= quantidade)
        {
            std::cerr << "Erro: índice inválido!" << std::endl;
        }
        return dados[indice];
    }

    // método de remoção do último valor da sequência, com verficador de existência de sequência
    void removerUltimo()
    {
        if (quantidade <= 0)
        {
            std::cerr << "Erro: remoção de sequência vazia!" << std::endl;
        }
        quantidade--;
    }
};