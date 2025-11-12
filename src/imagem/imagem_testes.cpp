#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "imagem.h"

TEST_CASE("Testa a criação de uma imagem com largura e altura específicas") {
    Imagem img(100, 50);
    CHECK(img.obterLargura() == 100);
    CHECK(img.obterAltura() == 50);
}

TEST_CASE("Testa a modificação e acesso aos pixels da imagem") {
    Imagem img(10, 10);
    Pixel vermelho = {255, 0, 0};
    img(5, 5) = vermelho;

    const Pixel& pixel = img(5, 5);
    CHECK(pixel.r == 255);
    CHECK(pixel.g == 0);
    CHECK(pixel.b == 0);
}

TEST_CASE("Testa a leitura de uma imagem em formato PPM") {
    Imagem img;
    bool sucesso = img.lerPPM("imagem.ppm");
    CHECK(sucesso);
    CHECK(img.obterLargura() == 3);
    CHECK(img.obterAltura() == 2);

    const Pixel& p1 = img(0, 0);
    CHECK(p1.r == 255);
    CHECK(p1.g == 0);
    CHECK(p1.b == 0);

    const Pixel& p2 = img(1, 0); // (x,y) = (1,0)
    CHECK(p2.r == 0);
    CHECK(p2.g == 255);
    CHECK(p2.b == 0);

    const Pixel& p3 = img(0, 1); // (x,y) = (0,1)
    CHECK(p3.r == 255);
    CHECK(p3.g == 255);
    CHECK(p3.b == 0);

    const Pixel& p4 = img(1, 1);
    CHECK(p4.r == 255);
    CHECK(p4.g == 255);
    CHECK(p4.b == 255);
}

TEST_CASE("Testa a salvamento da imagem em formato PPM") {
    Imagem img(2, 2);
    img(0, 0) = {255, 0, 0};   // vermelho
    img(1, 0) = {0, 255, 0};   // verde
    img(0, 1) = {0, 0, 255};   // azul
    img(1, 1) = {255, 255, 0}; // amarelo

    bool sucesso = img.salvarPPM("teste.ppm");
    CHECK(sucesso);

    // Verifica se o arquivo foi criado corretamente
    std::ifstream arquivo("teste.ppm");
    CHECK(arquivo.is_open());

    std::string conteudo;
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "P3");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "2 2");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "255");

    std::getline(arquivo, conteudo);
    CHECK(conteudo == "255 0 0");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 255 0");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "0 0 255");
    std::getline(arquivo, conteudo);
    CHECK(conteudo == "255 255 0");

    arquivo.close();
}