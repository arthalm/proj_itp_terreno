// ============================================================
// Arquivo: sequencia.h
// Descrição: declaração e implementação da classe "Sequencia",
// estrutura que armazena elementos de qualquer tipo,
// permitindo alocação dinâmica com aumento automático de capacidade
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: novembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#include <iostream>

// template permite que a classe funcione com qualquer tipo de dado
template <typename S>


class Sequencia
{
    // capacidade máxima atual do array
    int capacidade;

    // quantidade de elementos armazenados
    int quantidade;

    // ponteiro para o array dinâmico de elementos
    S *dados;

    // função responsável por aumentar a capacidade do array
    // dobra o tamanho atual e copia os elementos antigos
    void aumentarCapacidade()
    {
        // dobra a capacidade
        capacidade *= 2;

        // cria um novo array com a nova capacidade
        S *novo = new S[capacidade];

        //copia os elementos antigos para o novo array
        for (int i = 0; i < quantidade; i++)
        {
            novo[i] = dados[i];
        }

        // libera a memória antiga
        delete[] dados;

        // atualiza o ponteiro para o novo array
        dados = novo;
    }

public:

    // construtor: inicializa a sequência com capacidade = 2
    // aloca dinamicamente o array de elementos
    Sequencia(int cap = 2) : capacidade(cap), quantidade(0)
    {
        dados = new S[capacidade];
    }

    // destrutor: libera a memória alocada para o array
    ~Sequencia()
    {
        delete[] dados;
    }

    // retorna a quantidade atual de elementos
    int obterTamanho(){return quantidade;}

    // adiciona um novo elemento ao final da sequência
    // caso a capacidade seja atingida, dobra o tamanho do array
    void adicionar(S n)
    {
        if (tamanho >= capacidade)
        {
            // aumenta a capacidade do array
            aumentarCapacidade();
        }

        // insere o novo elemento na próxima posição
        dados[quantidade] = n;

        // soma 1 à quantidade de elementos
        quantidade++;
    }

    // operador de acesso
    // permite acessar ou modificar elementos pelo índice
    S &operator[](int indice)
    {
        // verifica se o índice é válido
        if (indice < 0 || indice >= quantidade)
        {
            std::cerr << "Erro: índice inválido!" << std::endl;
        }
        return dados[indice];
    }

    // remove o último elemento da sequência
    void removerUltimo()
    {
        // verifica se a sequência está vazia
        if (quantidade <= 0)
        {
            std::cerr << "Erro: remoção de sequência vazia!" << std::endl;
        }

        // reduz a quantidade de elementos
        quantidade--;
    }
};