#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"

TEST_CASE("Testa a criação de um terreno de uma única célula") {
  Terreno terreno(0); // 2^0 + 1 = 1
  CHECK(terreno.obterLargura() == 1);
  CHECK(terreno.obterProfundidade() == 1);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  Terreno terreno(2);
  CHECK(terreno.obterLargura() == 5);
  CHECK(terreno.obterProfundidade() == 5);
}

TEST_CASE("Testa a modificação e acesso as altitudes da matriz") {
    Terreno terreno(1, 1);

    terreno(1,1) = 42;
    CHECK(terreno(1,1) == 42);
}

TEST_CASE("Testa a geração de números aleatorios dentro do intervalo")
{
    Terreno t(2, 25);

    for (int i = 0; i < 20; i++)
    {
        int v = t.aleatorio(5, 10);
        CHECK(v >= 5);
        CHECK(v <= 10);
    }
}
// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".