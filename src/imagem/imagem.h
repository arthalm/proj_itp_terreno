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
        largura += 1;
        Pixel **novoL = new Pixel *[largura]; //novo array de ponteiros com largura maior

        for (int i = 0; i < largura - 1; i++) // -1 pq a ultima é o tamanho novo
        {
            novoL[i] = pixels[i];
        }

        //na parte aumentada, cria uma coluna onde todos os elementos são preto
        novoL[largura - 1] = new Pixel[altura];
        for (int j = 0; j < altura; j++){
            novoL[largura - 1][j] = {0, 0, 0};
        }

        delete[] pixels;
        pixels = novoL;
        
    }

    void aumentarAltura(){
        altura += 1;
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