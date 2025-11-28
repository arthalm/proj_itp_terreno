#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"
using namespace std;

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

TEST_CASE("Testa gerarMapa nos quatro cantos para terreno 2x2") {
    Terreno terreno(1, 42); // 2^1 + 1 = 3
    
    terreno.gerarMapa(0, 100);
    
    // Verifica se os quatro cantos foram inicializados
    CHECK(terreno(0, 0) >= 0);
    CHECK(terreno(0, 0) <= 100);
    
    CHECK(terreno(0, 2) >= 0);
    CHECK(terreno(0, 2) <= 100);
    
    CHECK(terreno(2, 0) >= 0);
    CHECK(terreno(2, 0) <= 100);
    
    CHECK(terreno(2, 2) >= 0);
    CHECK(terreno(2, 2) <= 100);
}

TEST_CASE("Testa gerarMapa com numero negativo") {
    Terreno terreno(1, 123);
    
    terreno.gerarMapa(-10, 10);
    
    // Verifica se os valores estão no intervalo -10 a 10
    CHECK(terreno(0, 0) >= -10);
    CHECK(terreno(0, 0) <= 10);
    
    CHECK(terreno(0, 2) >= -10);
    CHECK(terreno(0, 2) <= 10);
    
    CHECK(terreno(2, 0) >= -10);
    CHECK(terreno(2, 0) <= 10);
    
    CHECK(terreno(2, 2) >= -10);
    CHECK(terreno(2, 2) <= 10);
}

TEST_CASE("Testa visualização do terreno")
{
    Terreno terreno(1, 42); // mude onde está o 2 para ter diferentes tamanhos de matriz
    terreno.gerarMapa(0, 3); //alt minima e maxima

    SUBCASE("Terreno 5x5")
    {
        std::cout << "\nTerreno 5x5 gerado:\n";
        for (int i = 0; i < terreno.obterProfundidade(); i++)
        {
            for (int j = 0; j < terreno.obterLargura(); j++)
            {
                std::cout << terreno(i, j) << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // Verifica se os cantos foram realmente inicializados primeiro (teste qualquer)
    CHECK(terreno(0, 0) != 0);
    CHECK(terreno(0, 4) != 0);
    CHECK(terreno(4, 0) != 0);
    CHECK(terreno(4, 4) != 0);
}

TEST_CASE("Testa a salvamento da imagem em formato PPM") {
    Terreno terreno(1, 42);
    terreno(0, 0) = 3;
    terreno(0, 1) = 0;
    terreno(0, 2) = 1;
    terreno(1, 0) = 0;
    terreno(1, 1) = 0;
    terreno(1, 2) = 0;
    terreno(2, 0) = 0;
    terreno(2, 1) = 0;
    terreno(2, 2) = 2;

    bool sucesso = terreno.salvarPPM("teste.ppm", 0, 3);
    CHECK(sucesso);

    // Verifica se o arquivo foi criado corretamente
    std::ifstream arquivo("teste.ppm");
    CHECK(arquivo.is_open());

    std::string conteudo;
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "3 3");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "42");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 3");

    std::getline(arquivo, conteudo);
    CHECK(conteudo == "3 0 1");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 0 0");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 0 2");

    arquivo.close();
}

TEST_CASE("Testa a leitura de terreno em formato PPM") {
    Terreno terreno;
    bool sucesso = terreno.lerPPM("terreno.ppm");
    CHECK(sucesso);
    CHECK(terreno.obterProfundidade() == 3);
    CHECK(terreno.obterLargura() == 3);
    CHECK(terreno.obterSemente() == 42);

    const int& p1 = terreno(0, 0);
    CHECK(p1 == 3);

    const int& p2 = terreno(0, 1); // (x,y) = (1,0)
    CHECK(p2 == 0);

    const int& p3 = terreno(0, 2); // (x,y) = (0,1)
    CHECK(p3 == 1);

    const int& p4 = terreno(1, 0);
    CHECK(p4 == 0);

    const int& p5 = terreno(1, 1);
    CHECK(p5 == 0);

    const int& p6 = terreno(1, 2);
    CHECK(p6 == 0);

    const int& p7 = terreno(2, 0);
    CHECK(p7 == 0);

    const int& p8 = terreno(2, 1);
    CHECK(p8 == 0);

    const int& p9 = terreno(2, 2);
    CHECK(p9 == 2);

}

// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".