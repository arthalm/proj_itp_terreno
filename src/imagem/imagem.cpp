// ============================================================
// Arquivo: imagem.cpp
// Descrição: implementação da classe "Imagem",
// estrutura que representa uma imagem 2D baseada em pixels,
// permitindo manipulação e leitura/escrita no formato PPM
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: dezembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#include "imagem.h"
#include <iostream>
#include <fstream>

// função responsável por alocar memória para a matriz de pixels
// cria uma matriz dinâmica de tamanho altura x largura
// inicializa todos os pixels com a cor preta (0,0,0)
void Imagem::alocarEspaco(int alt, int larg)
{
    // limpa qualquer memória previamente alocada
    limpar();

    altura = alt;
    largura = larg;

    // aloca o array de ponteiros (linhas)
    pixels = new Pixel *[altura];

    for (int i = 0; i < altura; i++)
    {
        // aloca cada linha com "largura" pixels
        pixels[i] = new Pixel[largura];

        // inicializa todos os pixels com preto
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = Pixel{0, 0, 0};
        }
    }
}

// função que libera a memória alocada para a matriz de pixels
void Imagem::limpar()
{
    // se não houver memória alocada, não faz nada
    if (pixels == nullptr) return;

    // libera cada linha da matriz
    for (int i = 0; i < altura; i++)
    {
        delete[] pixels[i];
    }

    // libera o array de ponteiros
    delete[] pixels;

    // evita ponteiro solto
    pixels = nullptr;
    
    // reseta dimensões
    largura = 0;
    altura = 0;
}


// construtor: inicializa a imagem com dimensões dadas
// caso sejam válidas, aloca memória para os pixels
Imagem::Imagem(int alt, int larg) : altura(alt), largura(larg), pixels(nullptr)
{
    if (larg > 0 && alt > 0)
    {
        alocarEspaco(alt, larg);
    }
}

// destrutor: libera a memória alocada
Imagem::~Imagem()
{
    limpar();
}

// retorna a largura da imagem
int Imagem::obterLargura(){return largura;}

// retorna a altura da imagem
int Imagem::obterAltura(){return altura;}

// altera a cor de um pixel na posição (linha, coluna)
// retorna false caso a posição seja inválida ou não haja imagem
bool Imagem::pintar(int linha, int coluna, Cor cor)
{
    // verifica se a matriz foi alocada
    if (pixels == nullptr)return false;

    // verifica se a posição está dentro dos limites
    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
        return false;

    // altera o valor do pixel
    pixels[linha][coluna] = cor;

    return true;
}

// retorna a cor do pixel na posição (linha, coluna)
// caso inválido, retorna preto (0,0,0)
Cor Imagem::obterCor(int linha, int coluna)
{
    Cor preto = {0, 0, 0};

    // retorna a cor do pixel na posição (linha, coluna)
    // caso inválido, retorna preto (0,0,0)
    if (pixels == nullptr)return preto;

    // verifica se a posição é válida
    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
        return preto;

    return pixels[linha][coluna];
}

// lê uma imagem no formato PPM a partir de um arquivo
// armazena os valores RGB na matriz de pixels
bool Imagem::lerPPM(std::string arquivo)
{
    // abre o arquivo para leitura
    std::ifstream file(arquivo);

    // verifica se o arquivo foi aberto corretamente
    if (file.is_open() == false)
    {
        return false;
    }

    std::string formato;
    int largura_arquivo, altura_arquivo;
    int maxIntensidade;

    // lê cabeçalho do arquivo PPM
    file >> formato >> largura_arquivo >> altura_arquivo >> maxIntensidade;

    // atualiza dimensões da imagem
    largura = largura_arquivo;
    altura = altura_arquivo;

    // aloca memória para os pixels
    alocarEspaco(altura, largura);

    // lê os valores RGB de cada pixel
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            int R, G, B;

            // lê os valores de cor
            file >> R >> G >> B;

            // armazena convertendo para unsigned char
            pixels[linha][coluna] = Pixel{
                static_cast<unsigned char>(R),
                static_cast<unsigned char>(G),
                static_cast<unsigned char>(B)};
        }
    }

    return true;
}

// salva a imagem atual em um arquivo no formato PPM
bool Imagem::salvarPPM(std::string arquivo)
{
    // abre o arquivo para escrita
    std::ofstream file(arquivo);

    // verifica se o arquivo foi aberto corretamente
    if (!file.is_open())return false;

    // escreve cabeçalho do PPM
    file << "P3\n";
    file << largura << " " << altura << "\n";
    file << "255\n";

    // escreve os pixels linha por linha
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            // escreve valores RGB
            file << static_cast<int>(pixels[linha][coluna].r) << " "
                 << static_cast<int>(pixels[linha][coluna].g) << " "
                 << static_cast<int>(pixels[linha][coluna].b);

            // evita espaço extra no final da linha
            if (coluna < largura - 1)
                file << " ";
        }
        file << "\n";
    }

    return true;
}