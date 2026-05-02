#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "imagem.h"

TEST_CASE("Testa a criação de uma imagem com largura e altura específicas") {
    Imagem img(50, 100);
    CHECK(img.obterLargura() == 100);
    CHECK(img.obterAltura() == 50);
}

TEST_CASE("Testa a modificação e acesso aos pixels da imagem")
{
    Imagem img(10, 10);
    Pixel vermelho = {255, 0, 0};
    img.pintar(5, 5, vermelho);

    const Pixel& pixel = img.obterCor(5, 5);
    CHECK(pixel.r == 255);
    CHECK(pixel.g == 0);
    CHECK(pixel.b == 0);
}

TEST_CASE("Testa a leitura de uma imagem em formato PPM") {
    Imagem img;
    bool sucesso = img.lerPPM("teste_ler.ppm");
    CHECK(sucesso);
    CHECK(img.obterLargura() == 3);
    CHECK(img.obterAltura() == 2);

    const Pixel& p1 = img.obterCor(0, 0);
    CHECK(p1.r == 255);
    CHECK(p1.g == 0);
    CHECK(p1.b == 0);

    const Pixel& p2 = img.obterCor(0, 1);
    CHECK(p2.r == 0);
    CHECK(p2.g == 255);
    CHECK(p2.b == 0);

    const Pixel& p3 = img.obterCor(1, 0);
    CHECK(p3.r == 255);
    CHECK(p3.g == 255);
    CHECK(p3.b == 0);

    const Pixel& p4 = img.obterCor(1, 1);
    CHECK(p4.r == 255);
    CHECK(p4.g == 255);
    CHECK(p4.b == 255);
}

TEST_CASE("Testa o salvamento da imagem em formato PPM") {
    Imagem img(2, 2);
    img.pintar(0, 0, {255, 0, 0});  // vermelho
    img.pintar(0, 1, {0, 255, 0});   // verde

    img.pintar(1, 0, {0, 0, 255});   // azul
    img.pintar(1, 1, {255, 255, 0}); // amarelo

    bool sucesso = img.salvarPPM("teste_salvar.ppm");
    CHECK(sucesso);

    // Verifica se o arquivo foi criado corretamente
    std::ifstream arquivo("teste_salvar.ppm");
    CHECK(arquivo.is_open());

    std::string conteudo;
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "P3");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "2 2");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "255");

    std::getline(arquivo, conteudo);
    CHECK(conteudo == "255 0 0 0 255 0");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 0 255 255 255 0");

    arquivo.close();
}