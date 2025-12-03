// includes necessários agora e nas próximas funções
#include <fstream>
#include <string>
#include <iostream>
#include "../paleta/paleta.h"

class Imagem
{
    using Pixel = Cor;
    int altura, largura;
    Pixel **pixels;

    void alocarEspaco(int alt, int larg)
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
        largura = 0;
        altura = 0;
    }

public:
    Imagem(int alt = 0, int larg = 0) :altura(alt), largura(larg), pixels(nullptr)
    {
        if (larg > 0 && alt > 0)
        {
            alocarEspaco(alt, larg);
        }
    }

    ~Imagem()
    {
        limpar();
    }

    int obterLargura()
    {
        return largura;
    }

    int obterAltura()
    {
        return altura;
    }

    Pixel &operator()(int linha, int coluna)
    {
        if ((coluna >= largura || linha >= altura) || (coluna < 0 || linha < 0))
        {
            std::cerr << "Erro! Posição de pixel inválida.\n";
        }
        return pixels[linha][coluna];
    }

    bool pintar(int x, int y, Cor cor)
    {
        if (pixels == nullptr)
        {
            return false;
        }
        if (x < 0 || x >= largura || y < 0 || y >= altura)
        {
            return false;
        }
        pixels[y][x] = cor;
        return true;
    }

    Cor PegarCor(int x, int y)
    {
        Cor preto = {0, 0, 0};
        if (pixels == nullptr)
        {
            return preto;
        }
        if (x < 0 || x >= largura || y < 0 || y >= altura)
        {
            return preto;
        }
        return pixels[y][x];
    }

    bool lerPPM(std::string arquivo)
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

    bool salvarPPM(std::string arquivo)
    {
        std::ofstream file(arquivo);

        if (file.is_open() == false)
        {
            std::cerr << "Erro: nao foi possivel abrir " << arquivo << std::endl;
            return false;
        }

        file << "P3" << std::endl;
        file << largura << " " << altura << std::endl;
        file << "255" << std::endl;

        for (int linha = 0; linha < altura; linha++)
        {
            for (int coluna = 0; coluna < largura; coluna++)
            {
                file << static_cast<int>(pixels[linha][coluna].r) << " "
                     << static_cast<int>(pixels[linha][coluna].g) << " "
                     << static_cast<int>(pixels[linha][coluna].b);
                
                if (coluna == largura - 1)
                    file << std::endl;
                else
                    file << " ";
            }
            file << std::endl;
        }

        file.close();
        return true;
    }
};