// includes necessários agora e nas próximas funções
#include <fstream>
#include <string>
#include <iostream>
#include "../paleta/paleta.h"

using Pixel = Cor;

class Imagem
{
    int altura, largura;
    Pixel **pixels;

    void alocarEspaco(int alt, int larg)
    {
        pixels = new Pixel *[alt];
        for (int i = 0; i < alt; i++)
        {
            pixels[i] = new Pixel[larg];
        }
    }

    // lerPPM tambem vai usar isso do destrutor
    void limpar()
    {
        if (pixels == nullptr)
            return;
        for (int i = 0; i < altura; i++)
        {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }

public:
    // construtor - CORRIGIDO: parâmetros na ordem correta (altura, largura)
    Imagem(int alt = 0, int larg = 0) : altura(alt), largura(larg)
    {
        alocarEspaco(altura, largura);
        for (int linha = 0; linha < altura; linha++)
        {
            for (int coluna = 0; coluna < largura; coluna++)
            {
                pixels[linha][coluna] = {0, 0, 0};
            }
        }
    }

    ~Imagem()
    {
        limpar();
    }

    int obterLargura()
    {
        return largura; // CORRIGIDO: retorna largura, não altura
    }

    int obterAltura()
    {
        return altura; // CORRIGIDO: retorna altura, não largura
    }

    Pixel &operator()(int linha, int coluna)
    {
        if ((coluna >= largura || linha >= altura) || (coluna < 0 || linha < 0))
        {
            std::cerr << "Erro! Posição de pixel inválida.\n";
        }
        return pixels[linha][coluna]; // CORRIGIDO: [linha][coluna]
    }

    bool lerPPM(std::string arquivo)
    {
        // ler arquivo
        std::ifstream file(arquivo);

        // vê se o arquivo está fechado
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

        // CORRIGIDO: loop com nomes consistentes
        for (int linha = 0; linha < altura; linha++)
        {
            for (int coluna = 0; coluna < largura; coluna++)
            {
                int R, G, B;
                file >> R >> G >> B;
                pixels[linha][coluna] = Pixel{ // CORRIGIDO: [linha][coluna]
                    static_cast<unsigned char>(R),
                    static_cast<unsigned char>(G),
                    static_cast<unsigned char>(B)};
            }
        }

        return true;
    }

    bool salvarPPM(std::string arquivo)
    {
        // criar e ler arquivo
        std::ofstream file(arquivo);

        if (file.is_open() == false)
        {
            return false;
        }

        std::string formato = "P3", maxIntensidade = "255";
        // CORRIGIDO: usar nomes corretos
        int alt = altura, larg = largura;

        file << formato << std::endl;
        file << larg << " " << alt << std::endl; // PPM espera largura primeiro

        file << maxIntensidade << std::endl;

        // CORRIGIDO: loop com nomes consistentes
        for (int linha = 0; linha < altura; linha++)
        {
            for (int coluna = 0; coluna < largura; coluna++)
            {
                int Re, Gr, Bl;
                Re = pixels[linha][coluna].r; // CORRIGIDO: [linha][coluna]
                Gr = pixels[linha][coluna].g;
                Bl = pixels[linha][coluna].b;

                file << Re << " " << Gr << " " << Bl;
                if (coluna < largura - 1) {
                    file << " ";
                }
            }
            file << std::endl;
        }
        return true;
    }
};