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

    //paleta
    std::cout << "A. Esocolha o tipo de paleta:" << std::endl;
    std::cout << "1 - Paleta com 30 cores" << std::endl;
    std::cout << "2 - Paleta com 60 cores" << std::endl;
    std::string arquivoPaleta;
    int opcaoPaleta;
    std::cin >> opcaoPaleta;
    std::cout << std::endl; 
    if (opcaoPaleta < 1 || opcaoPaleta > 2)
    {
        std::cout << "Opção inválida. Usando valor padrão (30 cores)" << std::endl;
        opcaoPaleta = 1;
    }
    if (opcaoPaleta == 1){arquivoPaleta = "cores.hex";}
    else {arquivoPaleta = "cores_60.hex";}

    double map;
    if (opcaoPaleta == 1) map = 0.3;
    else map = 0.26;

    //dimensões da matriz
    std::cout << "B. Escolha o tamanho do mapa:" << std::endl;
    std::cout << "1 - Mapa pequeno (17x17)" << std::endl;
    std::cout << "2 - Mapa médio (65x65)" << std::endl;
    std::cout << "3 - Mapa grande (257x257)" << std::endl;
    std::cout << "4 - Mapa gigante (1025x1025)" << std::endl;
    int opcaoTamanho;
    int expoente;
    std::cin >> opcaoTamanho;
    std::cout << std::endl;
    if (opcaoTamanho < 1 || opcaoTamanho > 4)
    {
        std::cout << "Opção inválida. Usando valor padrão (mapa grande)" << std::endl;
        opcaoTamanho = 3;
    }
    if (opcaoTamanho == 1) expoente = 4;
    else if (opcaoTamanho == 2) expoente = 6;
    else if (opcaoTamanho == 3) expoente = 8;
    else expoente = 10;

    int dist;
    if (expoente < 10) dist = 2;
    else dist = 3;

    //semente
    std::cout << "C. Semente para geração do terreno: ";
    unsigned int semente;
    std::cin >> semente;
    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //arquivo para armazenar
    std::cout << "D. Nome do arquivo onde o mapa será armazenado (ex: mapa): ";
    std::string arquivoSaida;
    std::string nomeArquivo;
    std::getline(std::cin, nomeArquivo);
    arquivoSaida = nomeArquivo + ".ppm";
    std::cout << std::endl;

    Terreno terreno(expoente, semente, 0, 600);
    terreno.gerarMapa();

    terreno.salvarHeightMap("matrizAltitudes.r16");

    Imagem imagem = terreno.carregarTerreno(arquivoPaleta, 0.7, dist, map);
    imagem.salvarPPM(arquivoSaida);

    int tamanho = terreno.obterAltura();
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