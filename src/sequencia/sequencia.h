#include <iostream>

template <typename S>
class Sequencia
{
    int capacidade;
    int tamanho;
    S *dados;

    // função que dobra a capacidade de alocação da memória e deleta a sequência antiga
    void aumentarCapacidade()
    {
        capacidade *= 2;
        S *novo = new S[capacidade];
        for (int i = 0; i < tamanho; i++)
        {
            novo[i] = dados[i];
        }
        delete[] dados;
        dados = novo;
    }

public:
    // método que inicializa uma sequência de capacidade 2 e tamanho 0;
    Sequencia(int cap = 2) : capacidade(cap), tamanho(0)
    {
        dados = new S[capacidade];
    }

    // método que deleta a sequência de dados
    ~Sequencia()
    {
        delete[] dados;
    }

    // método que retorna o tamanho/quantidade de dados que estão na sequência atualmente
    int obterTamanho()
    {
        return tamanho;
    }

    // método que adiciona mais valores para a sequência, com um verificador de tamanho em relação a capacidade da sequência
    void adicionar(S valor)
    {
        if (tamanho >= capacidade)
        {
            aumentarCapacidade();
        }
        dados[tamanho] = valor;
        tamanho++;
    }

    // método de consulta/alteração de valor dado um índice da sequência, com verificador de existência do índice
    S &operator[](int indice)
    {
        if (indice < 0 || indice >= tamanho)
        {
            std::cerr << "Erro: índice inválido!" << std::endl;
        }
        return dados[indice];
    }

    // método de remoção do último valor da sequência, com verficador de existência de sequência
    void removerUltimo()
    {
        if (tamanho <= 0)
        {
            std::cerr << "Erro: remoção de sequência vazia!" << std::endl;
        }
        tamanho--;
    }
};