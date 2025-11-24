// includes necessários agora e nas próximas funções
#include <fstream>
#include <string>
#include <iostream>
#include "../paleta/paleta.h"

using Pixel = Cor;

class Imagem
{
    int largura, altura;
    Pixel **pixels;

    void aumentarLargura()
    {
        int novaLargura = largura + 1;
        Pixel **novaLinha = new Pixel *[novaLargura]; // novo array de ponteiros com largura maior

        // copiando dados
        for (int i = 0; i < largura; i++)
        {
            novaLinha[i] = pixels[i];
        }

        // adiconando preto na nova coluna
        novaLinha[largura] = new Pixel[altura];
        for (int j = 0; j < altura; j++)
        {
            novaLinha[largura][j] = {0, 0, 0};
        }

        //remove array de ponteiros antiga, mas as colunas se mantém
        delete[] pixels;
        pixels = novaLinha;
        largura = novaLargura;
    }

    void aumentarAltura()
    {
        int novaAltura = altura + 1;

        // para cada coluna
        for (int i = 0; i < largura; i++)
        {
            Pixel *novaColuna = new Pixel[novaAltura];

            // copiando dados
            for (int j = 0; j < altura; j++)
            {
                novaColuna[j] = pixels[i][j];
            }

            // adicionar preto na nova linha
            for (int j = altura; j < novaAltura; j++)
            {
                novaColuna[j] = {0, 0, 0};
            }

            //((pixels[i] é a coluna antiga))
            delete[] pixels[i];
            pixels[i] = novaColuna;
        }
        altura = novaAltura;
    }

    //lerPPM tambem vai usar isso do destrutor
    void limpar()
    {
        for (int i = 0; i < largura; i++)
        {
            delete[] pixels[i];
        }
        delete[] pixels;
    }

public:
    // construtor
    Imagem(int lar = 0, int alt = 0) : largura(lar), altura(alt)
    {
        pixels = new Pixel *[largura];
        for (int i = 0; i < largura; i++)
        {
            pixels[i] = new Pixel[altura];
            // para iniciar com a cor preta
            for (int j = 0; j < altura; j++)
            {
                pixels[i][j] = {0, 0, 0};
            }
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

    Pixel &operator()(int lar, int alt)
    {
        if ((lar >= largura || alt >= altura) || (lar < 0 || alt < 0))
        {
            std::cerr << "Erro! Posição de pixel inválida.\n";
        }
        return pixels[lar][alt];
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
        int larg, alt, maxIntensidade;

        file >> formato >> larg >> alt >> maxIntensidade;

        //o que tem no PPM vai substituir a imagem atual
        //precisa limpar a imagem antiga agr
        //ja que o destrutor só limparia no final do codigo
        limpar();
        largura = 0;
        altura = 0;
        pixels = nullptr;

        for (int i = 0; i < larg; i++)
        {
            aumentarLargura();
        }
        for (int i = 0; i < alt; i++)
        {
            aumentarAltura();
        }

        for (int y = 0; y < alt; y++)
        {
            for (int x = 0; x < larg; x++)
            {
                int R, G, B;
                file >> R >> G >> B;
                pixels[x][y] = Pixel{
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
        int larg = largura, alt = altura;

        file << formato << std::endl;
        file << std::to_string(larg) << " " << std::to_string(alt) << std::endl;

        //não precisa aumentar tamanho nessa parte

        file << maxIntensidade << std::endl;

        for (int y = 0; y < larg; y++)
        {
            for (int x = 0; x < alt; x++)
            {
                int Re, Gr, Bl;
                Re = pixels[x][y].r;
                Gr = pixels[x][y].g;
                Bl = pixels[x][y].b;

                file << std::to_string(Re) << " " << std::to_string(Gr) << " " << std::to_string(Bl) << std::endl;
            }
        }
        return true;
    }
};