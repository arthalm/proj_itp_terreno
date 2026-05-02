// ============================================================
// Arquivo: main.cpp
// Descrição: programa principal do gerador de mapas de terreno,
// responsável por coletar as configurações do usuário e gerar, 
// colorir e exportar o mapa
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: dezembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include "../paleta/paleta.h"
#include "../imagem/imagem.h"
#include "../terreno/terreno.h"

int main(){

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "          GERADOR DE MAPAS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // BLOCO A: escolha da paleta de cores
    std::cout << "A. Esocolha o tipo de paleta:" << std::endl;
    std::cout << "1 - Paleta com 30 cores" << std::endl;
    std::cout << "2 - Paleta com 60 cores" << std::endl;

    std::string arquivoPaleta;
    int opcaoPaleta;
    std::cin >> opcaoPaleta;
    std::cout << std::endl;

    // valida a opção; caso inválida, usa 30 cores como padrão
    if (opcaoPaleta < 1 || opcaoPaleta > 2)
    {
        std::cout << "Opção inválida. Usando valor padrão (30 cores)" << std::endl;
        opcaoPaleta = 1;
    }

    // define o arquivo de paleta correspondente à opção escolhida
    if (opcaoPaleta == 1){arquivoPaleta = "cores.hex";}
    else {arquivoPaleta = "cores_60.hex";}

    // define o limite de água de acordo com o número de cores da paleta
    // paletas maiores exigem um limite menor para manter a proporção visual
    double map;
    if (opcaoPaleta == 1) map = 0.3;
    else map = 0.26;

    // BLOCO B: escolha do tamanho do mapa
    // o tamanho é definido por um expoente n, onde o mapa tem dimensão 2^n + 1
    std::cout << "B. Escolha o tamanho do mapa:" << std::endl;
    std::cout << "1 - Mapa pequeno (17x17)" << std::endl;
    std::cout << "2 - Mapa médio (65x65)" << std::endl;
    std::cout << "3 - Mapa grande (257x257)" << std::endl;
    std::cout << "4 - Mapa gigante (1025x1025)" << std::endl;

    int opcaoTamanho;
    int expoente;
    std::cin >> opcaoTamanho;
    std::cout << std::endl;

    // valida a opção; caso inválida, usa mapa grande como padrão
    if (opcaoTamanho < 1 || opcaoTamanho > 4)
    {
        std::cout << "Opção inválida. Usando valor padrão (mapa grande)" << std::endl;
        opcaoTamanho = 3;
    }

    // mapeia a opção para o expoente correspondente
    if (opcaoTamanho == 1) expoente = 4;
    else if (opcaoTamanho == 2) expoente = 6;
    else if (opcaoTamanho == 3) expoente = 8;
    else expoente = 10;

    // define a distância usada no cálculo de sombra
    // mapas maiores usam distância maior para suavizar o efeito
    int dist;
    if (expoente < 10) dist = 2;
    else dist = 3;

    // BLOCO C: semente para geração do terreno
    // sementes iguais sempre produzem o mesmo mapa
    std::cout << "C. Semente para geração do terreno: ";
    unsigned int semente;
    std::cin >> semente;
    std::cout << std::endl;

    // descarta o '\n' residual do buffer antes de ler a próxima linha
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // BLOCO D: nome do arquivo de saída
    std::cout << "D. Nome do arquivo onde o mapa será armazenado (ex: mapa): ";
    std::string arquivoSaida;
    std::string nomeArquivo;
    std::getline(std::cin, nomeArquivo);

    // concatena a extensão .ppm ao nome fornecido
    arquivoSaida = nomeArquivo + ".ppm";
    std::cout << std::endl;

    // cria o terreno com expoente, semente e intervalo de altitude [0, 600]
    Terreno terreno(expoente, semente, 0, 600);

    // executa o algoritmo diamond-square para preencher o mapa de alturas
    terreno.gerarMapa();

    // salva a matriz de alturas em arquivo para uso externo
    terreno.salvarHeightMap("matrizAltitudes.r16");

    // converte o mapa de alturas em imagem colorida aplicando paleta e sombra
    Imagem imagem = terreno.carregarTerreno(arquivoPaleta, 0.7, dist, map);

    // salva a imagem gerada no arquivo de saída no formato PPM
    imagem.salvarPPM(arquivoSaida);

    // obtém o tamanho do terreno para exibição no resumo
    int tamanho = terreno.obterAltura();

    // exibe resumo das configurações utilizadas na geração
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "CONFIGURACAO:" << std::endl;
    std::cout << "  Tamanho: " << tamanho << "x" << tamanho << std::endl;
    std::cout << "  Semente: " << semente << std::endl;
    std::cout << "  Altitude: [" << 0 << ", " << 600 << "]" << std::endl;
    std::cout << "  Fator sombra: " << 0.7 << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    return 0;
}