#include <iostream>
#include <string>
#include "../terreno/terreno.h"

int main(){

    std::cout << std::endl;
    std::cout << "========================================\n";
    std::cout << "          GERADOR DE MAPAS\n";
    std::cout << "========================================\n\n";

    std::cout << std::endl;
    //paleta
    std::cout << "1. Nome do arquivo com a paleta (ex: arquivo.hex): ";
    std::string arquivoPaleta;
    std::getline(std::cin, arquivoPaleta);
    std::cout << std::endl; 

    //dimensões da matriz
    std::cout << "2. Valor do expoente N para dimensões da matriz (2^N + 1): ";
    int expoente;
    std::cin >> expoente;
    std::cout << std::endl;

    //semente
    std::cout << "3. Semente para geração do terreno: ";
    unsigned int semente;
    std::cin >> semente;
    std::cout << std::endl;

    //altitude minima e maxima
    std::cout << "4. Valores mínimo e máximo para altitudes:" << std::endl;
    int minimo, maximo;
    std::cout << "Altitude mínima: ";
    std::cin >> minimo; 
    std::cout << "Altitude máxima: ";
    std::cin >> maximo;
    std::cout << std::endl;

    //fator de sombreamento
    std::cout << "5. Fator para sombreamento (0.0 a 1.0): ";
    float fator;
    std::cin >> fator;
    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //arquivo para armazenar
    std::cout << "6. Nome do arquivo onde o mapa será armazenado (ex: mapa.ppm): ";
    std::string arquivoSaida;
    std::getline(std::cin, arquivoSaida);
    std::cout << std::endl;

    //inicializando
    Paleta paleta(arquivoPaleta);

    Terreno terreno(expoente, semente, minimo, maximo);
    terreno.gerarMapa();

    terreno.salvarHeightMap("matrizAltitudes.r16");

    Imagem imagem = terreno.carregarTerreno(arquivoPaleta, fator);
    imagem.salvarPPM(arquivoSaida);

    int tamanho = terreno.obterAltura();
    std::cout << "\n"<< std::string(40, '=') << std::endl;
    std::cout << "CONFIGURACAO:\n";
    std::cout << "  Tamanho: " << tamanho << "x" << tamanho << "\n";
    std::cout << "  Semente: " << semente << "\n";
    std::cout << "  Altitude: [" << minimo << ", " << maximo << "]\n";
    std::cout << "  Fator sombra: " << fator << "\n";
    std::cout << std::string(40, '=') << std::endl;
    std::cout << std::endl;

    return 0;
}