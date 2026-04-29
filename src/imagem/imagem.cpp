#include "imagem.h"
#include <iostream>
#include <fstream>

void Imagem::alocarEspaco(int alt, int larg)
{
    limpar();
    altura = alt;
    largura = larg;

    pixels = new Pixel *[altura];
    for (int i = 0; i < altura; i++)
    {
        pixels[i] = new Pixel[largura];
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = Pixel{0, 0, 0};
        }
    }
}

// lerPPM tambem vai usar isso do destrutor
void Imagem::limpar()
{
    if (pixels == nullptr)
        return;
    for (int i = 0; i < altura; i++)
    {
        delete[] pixels[i];
    }
    delete[] pixels;
    pixels = nullptr;
    largura = 0;
    altura = 0;
}

Imagem::Imagem(int alt, int larg) : altura(alt), largura(larg), pixels(nullptr)
{
    if (larg > 0 && alt > 0)
    {
        alocarEspaco(alt, larg);
    }
}

Imagem::~Imagem()
{
    limpar();
}

int Imagem::obterLargura()
{
    return largura;
}

int Imagem::obterAltura()
{
    return altura;
}
/*
Pixel &operator()(int linha, int coluna)
{
    if ((coluna >= largura || linha >= altura) || (coluna < 0 || linha < 0))
    {
        std::cerr << "Erro! Posição de pixel inválida.\n";
    }
    return pixels[linha][coluna];
}
*/

bool Imagem::pintar(int linha, int coluna, Cor cor)
{
    if (pixels == nullptr)
        return false;

    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
        return false;

    pixels[linha][coluna] = cor;
    return true;
}

Cor Imagem::obterCor(int linha, int coluna)
{
    Cor preto = {0, 0, 0};

    if (pixels == nullptr)
        return preto;

    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
        return preto;

    return pixels[linha][coluna];
}

bool Imagem::lerPPM(std::string arquivo)
{
    std::ifstream file(arquivo);

    if (file.is_open() == false)
    {
        return false;
    }

    std::string formato;
    int largura_arquivo, altura_arquivo;
    int maxIntensidade;

    file >> formato >> largura_arquivo >> altura_arquivo >> maxIntensidade;

    largura = largura_arquivo;
    altura = altura_arquivo;

    alocarEspaco(altura, largura);

    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            int R, G, B;
            file >> R >> G >> B;
            pixels[linha][coluna] = Pixel{
                static_cast<unsigned char>(R),
                static_cast<unsigned char>(G),
                static_cast<unsigned char>(B)};
        }
    }

    return true;
}

bool Imagem::salvarPPM(std::string arquivo)
{
    std::ofstream file(arquivo);

    if (!file.is_open())
        return false;

    file << "P3\n";
    file << largura << " " << altura << "\n";
    file << "255\n";

    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            file << static_cast<int>(pixels[linha][coluna].r) << " "
                 << static_cast<int>(pixels[linha][coluna].g) << " "
                 << static_cast<int>(pixels[linha][coluna].b);

            if (coluna < largura - 1)
                file << " ";
        }
        file << "\n";
    }

    return true;
}