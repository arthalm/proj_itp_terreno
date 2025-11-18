//includes necessários agora e nas próximas funções
#include <fstream>
#include <string>
#include <iostream>

struct Pixel
{
    unsigned char r, g, b;
};

class Imagem
{
    int largura, altura;
    Pixel **pixels;


    void aumentarLargura(){
        int novaLargura = largura + 1;
        Pixel **novaLinha = new Pixel *[novaLargura]; //novo array de ponteiros com largura maior

        //copiando dados
        for (int i = 0; i < largura; i++)
        {
            novaLinha[i] = pixels[i];
        }

        //adiconando preto na nova coluna
        novaLinha[largura] = new Pixel[altura];
        for (int j = 0; j < altura; j++)
        {
            novaLinha[largura][j] = {0, 0, 0};
        }

        delete[] pixels;
        pixels = novaLinha;
        largura = novaLargura;
        
    }


    void aumentarAltura(){
        int novaAltura = altura + 1;

        //para cada coluna
        for (int i = 0; i < largura; i++)
        {
            Pixel *novaColuna = new Pixel[novaAltura];

            //copiando dados
            for (int j = 0; j < altura; j++)
            {
                novaColuna[j] = pixels[i][j];
            }

            //adicionar preto na nova linha
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

public:

    //construtor normal
    Imagem(int lar = 1, int alt = 1) : largura(lar), altura(alt)
    {
        pixels = new Pixel *[largura];
        for (int i = 0; i < largura; i++)
        {
            pixels[i] = new Pixel[altura];
            //para iniciar com a cor preta
            for (int j = 0; j < altura; j++)
            {
                pixels[i][j] = {0, 0, 0};
            }
        }
    }
/*
    //construtor do arquivo
    Imagem(std::string arquivo) : largura(1), altura(1)
    {
        pixels = new Pixel *[largura];
        for (int i = 0; i < largura; i++)
        {
            pixels[i] = new Pixel[altura];
            for (int j = 0; j < altura; j++)
            {
                pixels[i][j] = {0, 0, 0};
            }
        }

        std::ifstream file(arquivo);

    }
*/
    ~Imagem()
    {
        for (int i = 0; i < largura; i++)
        {
            delete[] pixels[i];
        }
        delete[] pixels;
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
        if ((lar > largura || alt > altura) || (lar < 0 || alt < 0))
        {
            std::cerr << "Erro! Posição de pixel inválida.\n";
        }
        return pixels[lar][alt];
    }

};