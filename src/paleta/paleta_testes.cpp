#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "paleta.h"

TEST_CASE("Testa a criação de uma paleta padrão (sem nenhuma cor)") {
    Paleta paleta;
    CHECK(paleta.obterTamanho() == 0);
}

TEST_CASE("Testa a adição de cores uma paleta vazia") {
    Paleta paleta;
    paleta.adicionarCor(Cor {255, 0, 0});

    CHECK(paleta.obterTamanho() == 1);
    CHECK(paleta.obterCor(0).r == 255);
    CHECK(paleta.obterCor(0).g == 0);
    CHECK(paleta.obterCor(0).b == 0);
}

TEST_CASE("Testa a obtenção de uma cor com índice inválido") {
    Paleta paleta;
    paleta.adicionarCor(Cor {100, 150, 200});

    Cor corInvalida = paleta.obterCor(5); // índice inválido (maior que o tamanho)

    // deve retornar uma cor padrão (preto)
    CHECK(corInvalida.r == 0);
    CHECK(corInvalida.g == 0);
    CHECK(corInvalida.b == 0);
}

TEST_CASE("Testa a criação de uma paleta a partir de um arquivo válido") {
    // o arquivo "cores.hex" foi fornecido junto com o projeto.
    // verifique se ele se encontra na mesma pasta que o executável do teste.
    Paleta paleta("cores.hex");

    // verifica se as cores foram carregadas corretamente
    CHECK(paleta.obterTamanho() == 30);
    CHECK(paleta.obterCor(0).r == 113);
    CHECK(paleta.obterCor(0).g == 171);
    CHECK(paleta.obterCor(0).b == 216);

    CHECK(paleta.obterCor(1).r == 121);
    CHECK(paleta.obterCor(1).g == 178);
    CHECK(paleta.obterCor(1).b == 222);
    
    //... outras cores

    CHECK(paleta.obterCor(29).r == 255);
    CHECK(paleta.obterCor(29).g == 255);
    CHECK(paleta.obterCor(29).b == 255);
}

TEST_CASE("Testa a criação de uma paleta a partir de um arquivo inexistente") {
    Paleta paleta("arquivo_inexistente.txt");

    // a paleta deve estar vazia
    CHECK(paleta.obterTamanho() == 0);
}