#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "sequencia.h"

TEST_CASE("Testa a criação de uma sequência de inteiros (sem nenhum elemento)")
{
    Sequencia<int> seq;
    CHECK(seq.obterTamanho() == 0);
}

TEST_CASE("Testa a adição de elementos em uma sequência vazia")
{
    Sequencia<int> seq;
    seq.adicionar(42);

    CHECK(seq.obterTamanho() == 1);
    CHECK(seq[0] == 42);
}

TEST_CASE("Testa a remoção de elementos de uma sequência")
{
    Sequencia<int> seq;
    seq.adicionar(42);
    seq.adicionar(13);
    seq.removerUltimo();

    CHECK(seq.obterTamanho() == 1);
    CHECK(seq[0] == 42);
}

TEST_CASE("Testa o redimensionamento da sequência")
{
    Sequencia<int> seq;
    for (int i = 0; i < 100; i++)
    {
        seq.adicionar(i);
    }

    CHECK(seq.obterTamanho() == 100);
    CHECK(seq[99] == 99);
}

TEST_CASE("Testa a alteração de elementos via operador[]")
{
    Sequencia<int> seq;
    seq.adicionar(10);
    seq.adicionar(20);
    seq[1] = 30;

    CHECK(seq.obterTamanho() == 2);
    CHECK(seq[0] == 10);
    CHECK(seq[1] == 30);
}

TEST_CASE("Testa a criação de uma sequência de strings")
{
    Sequencia<std::string> seq;
    seq.adicionar("hello");
    seq.adicionar("world");

    CHECK(seq.obterTamanho() == 2);
    CHECK(seq[0] == "hello");
    CHECK(seq[1] == "world");
}
