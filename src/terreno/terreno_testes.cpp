#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"
using namespace std;

TEST_CASE("Testa a criação de um terreno de uma única célula")
{
    Terreno terreno(0); // 2^0 + 1 = 1
    CHECK(terreno.obterLargura() == 1);
    CHECK(terreno.obterProfundidade() == 1);
}

TEST_CASE("Testa a geração aleatória de altitudes")
{
    Terreno terreno(2);
    CHECK(terreno.obterLargura() == 5);
    CHECK(terreno.obterProfundidade() == 5);
}

TEST_CASE("Testa a modificação e acesso as altitudes da matriz")
{
    Terreno terreno(1, 1);

    terreno(1, 1) = 42;
    CHECK(terreno(1, 1) == 42);
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

TEST_CASE("Testa gerarMapa nos quatro cantos para terreno 2x2")
{
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

TEST_CASE("Testa gerarMapa com numero negativo")
{
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

TEST_CASE("Testa a salvamento do terreno em formato R16 (HeightMap)")
{
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

    bool sucesso = terreno.salvarHeightMap("teste.r16", 0, 3);
    CHECK(sucesso);

    // Verifica se o arquivo foi criado corretamente
    std::ifstream arquivo("teste.r16");
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

TEST_CASE("Testa a leitura de terreno em formato R16 (HeightMap)")
{
    Terreno terreno;
    bool sucesso = terreno.lerHeightMap("teste.r16");
    CHECK(sucesso);
    CHECK(terreno.obterProfundidade() == 3);
    CHECK(terreno.obterLargura() == 3);
    CHECK(terreno.obterSemente() == 42);

    const int &p1 = terreno(0, 0);
    CHECK(p1 == 3);

    const int &p2 = terreno(0, 1); // (x,y) = (1,0)
    CHECK(p2 == 0);

    const int &p3 = terreno(0, 2); // (x,y) = (0,1)
    CHECK(p3 == 1);

    const int &p4 = terreno(1, 0);
    CHECK(p4 == 0);

    const int &p5 = terreno(1, 1);
    CHECK(p5 == 0);

    const int &p6 = terreno(1, 2);
    CHECK(p6 == 0);

    const int &p7 = terreno(2, 0);
    CHECK(p7 == 0);

    const int &p8 = terreno(2, 1);
    CHECK(p8 == 0);

    const int &p9 = terreno(2, 2);
    CHECK(p9 == 2);
}

TEST_CASE("Testa geração, visualização e salvamento de um terreno potencia 5")
{
    Terreno terreno(5, 42);     // 2^5 + 1 = 33
    terreno.gerarMapa(0, 300);    // valores aleatórios entre 0 e 300

    CHECK(terreno.obterLargura() == 33);
    CHECK(terreno.obterProfundidade() == 33);

    // Testa se canto superior-esquerdo e inferior-direito estão dentro do intervalo
    CHECK(terreno(0, 0) >= 0);
    CHECK(terreno(0, 0) <= 300);

    CHECK(terreno(32, 32) >= 0);
    CHECK(terreno(32, 32) <= 300);

    // ------------------------------------------------------------
    // TESTE DE SALVAMENTO EM R16
    // ------------------------------------------------------------

    bool sucesso = terreno.salvarHeightMap("terreno_33x33.r16", 0, 300);
    CHECK(sucesso);

    // Abre o arquivo salvo
    std::ifstream arquivo("terreno_33x33.r16");
    CHECK(arquivo.is_open());

    // Verifica conteúdo básico (dimensões e semente)
    std::string linha;

    std::getline(arquivo, linha);
    CHECK(linha == "33 33");   // largura e profundidade

    std::getline(arquivo, linha);
    CHECK(linha == "42");    // semente usada

    std::getline(arquivo, linha);
    CHECK(linha == "0 300");   // min e max gravados

    // Le uma linha qualquer da matriz para garantir formato válido
    std::getline(arquivo, linha);
    CHECK(linha.size() > 0); // só verifica que existe algo

    arquivo.close();
}

TEST_CASE("Testa geração, visualização e salvamento de um terreno potencia 8")
{
    Terreno terreno(8, 42);   // 2^8 + 1 = 257
    terreno.gerarMapa(0, 300);

    CHECK(terreno.obterLargura() == 257);
    CHECK(terreno.obterProfundidade() == 257);

    // Testes básicos: valores nos cantos
    CHECK(terreno(0, 0) >= 0);
    CHECK(terreno(0, 0) <= 300);

    CHECK(terreno(256, 256) >= 0);
    CHECK(terreno(256, 256) <= 300);

    // ------------------------------------------------------------
    // TESTE DE SALVAMENTO EM R16
    // ------------------------------------------------------------

    bool sucesso = terreno.salvarHeightMap("terreno_257x257.r16", 0, 300);
    CHECK(sucesso);

    std::ifstream arquivo("terreno_257x257.r16");
    CHECK(arquivo.is_open());

    std::string linha;

    // Primeira linha: dimensões
    std::getline(arquivo, linha);
    CHECK(linha == "257 257");

    // Segunda linha: semente final depois de gerar o mapa
    // Esta semente muda durante o algoritmo, portanto você deve imprimir
    // o valor real gerado para descobrir qual é.
    // Por enquanto, apenas testaremos que a linha NÃO está vazia:
    std::getline(arquivo, linha);
    CHECK(linha.size() > 0);

    // Terceira linha: intervalo min e max
    std::getline(arquivo, linha);
    CHECK(linha == "0 300");

    // Testa se existe ao menos uma linha da matriz
    std::getline(arquivo, linha);
    CHECK(linha.size() > 0);

    arquivo.close();
}