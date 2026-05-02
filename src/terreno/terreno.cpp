// ============================================================
// Arquivo: terreno.cpp
// Descrição: implementação da classe "Terreno",
// estrutura que representa um mapa de alturas (heightmap),
// permitindo geração de terreno usando o algoritmo
// diamond-square e conversão para imagem
// Autor 1: Leonardo Alencar de Aquino
// Autor 2: Arthur Victor Vieira Almeida
// Data: dezembro de 2025
// Disciplina: Introdução às Técnicas de Programação
// ============================================================

#include "terreno.h"
#include "../imagem/imagem.h"
#include "../paleta/paleta.h"
#include <iostream>
#include <cmath>
#include <fstream>

// aloca memória para a matriz de alturas (mapa)
// cria uma matriz dinâmica de inteiros de tamanho alt x larg
void Terreno::alocarEspaco(int alt, int larg)
{
    mapa = new int *[alt];
    for (int i = 0; i < alt; i++)
    {
        mapa[i] = new int[larg];
    }
}

// libera a memória alocada para o mapa
void Terreno::limpar()
{
    // verifica se há memória alocada
    if (mapa == nullptr)return;

    // libera cada linha da matriz
    for (int i = 0; i < altura; i++)
    {
        delete[] mapa[i];
    }

    // libera o array de ponteiros
    delete[] mapa;

    // evita ponteiro inválido
    mapa = nullptr;
}


// calcula o tamanho do terreno com base no expoente
// retorna 2^n + 1
int Terreno::potencia(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return std::pow(2, n) + 1;
}

// gerador de números pseudoaleatórios (LCG - Linear Congruential Generator)
// atualiza a semente e retorna um novo valor
int Terreno::gerarNumero()
{
    // A = 1103515245, C = 12345, M = 2^31 - 1
    semente = (semente * 1103515245 + 12345) & 0x7fffffff;
    return semente;
}

// etapa diamond
// calcula o valor de um ponto com base nos vizinhos vertical e horizontal
void Terreno::diamond(int linha, int coluna, int alcance, int variacao)
{
    int cont = 0;
    float media = 0.0;

    // verifica o vizinho acima:
    // só é válido se não ultrapassar o limite superior da matriz
    // (linha - alcance >= 0 garante que não acessamos índice negativo)
    if (linha - alcance >= 0)
    {
        // soma o valor do vizinho à média acumulada
        media += mapa[linha - alcance][coluna];
        // soma 1 à quantidade de vizinhos válidos
        cont++;
    }

    // verifica o vizinho abaixo:
    // (linha + alcance < altura garante que não ultrapasse o limite inferior)
    if (linha + alcance < altura)
    {
        media += mapa[linha + alcance][coluna];
        cont++;
    }

    // verifica o vizinho à esquerda:
    // (coluna - alcance >= 0 evita índice negativo)
    if (coluna - alcance >= 0)
    {
        media += mapa[linha][coluna - alcance];
        cont++;
    }

    // verifica o vizinho à direita:
    // (coluna + alcance < largura evita ultrapassar o limite da matriz)
    if (coluna + alcance < largura)
    {
        media += mapa[linha][coluna + alcance];
        cont++;
    }

    // caso não haja vizinhos válidos
    if (cont == 0)
    {
        mapa[linha][coluna] = aleatorio(-variacao, variacao);
        return;
    }

    // caso existam vizinhos válidos (cont > 0)
    // calcula a média dos valores vizinhos e adiciona um ruído aleatório
    if (cont > 0)
    {
        // calcula a média dos vizinhos considerados
        media /= cont;

        // gera um valor aleatório para criar variação no terreno
        int ruido = aleatorio(-variacao, variacao);

        // soma média + ruído para obter o novo valor
        int novoValor = (int)(media + ruido);

        // atribui o valor calculado ao ponto atual
        mapa[linha][coluna] = novoValor;
    }
}


// etapa square
// calcula o valor de um ponto com base nos vizinhos diagonais
void Terreno::square(int linha, int coluna, int alcance, int variacao)
{
    int cont = 0;
    float media = 0.0;

    // verifica o vizinho superior esquerdo:
    // (linha - alcance >= 0) não ultrapassa o topo
    // (coluna - alcance >= 0) não ultrapassa a esquerda
    if (linha - alcance >= 0 && coluna - alcance >= 0)
    {
        media += mapa[linha - alcance][coluna - alcance];
        cont++;
    }

    // verifica o vizinho superior direito:
    // (linha - alcance >= 0) não ultrapassa o topo
    // (coluna + alcance < largura) não ultrapassa a direita
    if (linha - alcance >= 0 && coluna + alcance < largura)
    {
        media += mapa[linha - alcance][coluna + alcance];
        cont++;
    }

    // verifica o vizinho inferior esquerdo:
    // (linha + alcance < altura) não ultrapassa a base
    // (coluna - alcance >= 0) não ultrapassa a esquerda
    if (linha + alcance < altura && coluna - alcance >= 0)
    {
        media += mapa[linha + alcance][coluna - alcance];
        cont++;
    }

    // verifica o vizinho inferior direito:
    // (linha + alcance < altura) não ultrapassa a base
    // (coluna + alcance < largura) não ultrapassa a direita
    if (linha + alcance < altura && coluna + alcance < largura)
    {
        media += mapa[linha + alcance][coluna + alcance];
        cont++;
    }

    // caso nenhum vizinho válido tenha sido encontrado
    if (cont == 0)
    {
        mapa[linha][coluna] = aleatorio(-variacao, variacao);
        return;
    }

    if (cont > 0)
    {
        // calcula a média dos vizinhos válidos
        media /= cont;

        // adiciona um ruído aleatório para gerar variação no terreno
        int ruido = aleatorio(-variacao, variacao);

        // soma média + ruído
        int novoValor = (int)(media + ruido);

        // atribui o valor final ao ponto atual
        mapa[linha][coluna] = novoValor;
    }
}

// implementação do algoritmo diamond-square
// gera um terreno variando os valores de altura
void Terreno::diamondSquare(int tamanho, int variacao)
{
    // começa com metade do tamanho
    // define a distância entre os pontos que serão calculados
    int metade = tamanho / 2;

    // enquanto ainda houver subdivisões possíveis
    while (metade >= 1)
    {

        // PASSO SQUARE
        // percorre os centros dos quadrados
        // começa em 'metade' para cair exatamente no meio de cada bloco
        for (int linha = metade; linha < tamanho; linha += (metade * 2))
        {
            for (int coluna = metade; coluna < tamanho; coluna += (metade * 2))
            {
                // calcula valor baseado nos 4 cantos (diagonais)
                square(linha, coluna, metade, variacao);
            }
        }

        // PASSO DIAMOND
        // percorre os pontos em forma de losango
        for (int linha = 0; linha < tamanho; linha += metade)
        {
            // alterna o início da coluna a cada linha
            // cria o padrão intercalado pro diamond-square
            for (int coluna = ((linha / metade) % 2 == 0 ? metade : 0); coluna < tamanho; coluna += (metade * 2))
            {
                // calcula valor baseado nos vizinhos (cima, baixo, lados)
                diamond(linha, coluna, metade, variacao);
            }
        }

        // reduz o tamanho do passo pela metade
        metade /= 2;

        // reduz a variação do ruído
        variacao *= 0.6;

        // garante que a variação nunca seja menor que 1
        if (variacao < 1)
        {
            variacao = 1;
        }
    }
}

// construtor: inicializa o terreno com base no expoente e parâmetros
Terreno::Terreno(int exp, int seed, int min, int max)
    : expoente(exp), sementeInicial(seed), semente(seed), altMinimo(min), altMaximo(max)
{
    // calcula dimensões do mapa
    altura = potencia(expoente);
    largura = potencia(expoente);

    // aloca memória
    alocarEspaco(altura, largura);

    // inicializa o mapa com zero
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            mapa[i][j] = 0;
        }
    }
}


Terreno::~Terreno()
{
    limpar();
}

// retorna largura do terreno
int Terreno::obterLargura(){return largura;}

// retorna altura do terreno
int Terreno::obterAltura(){return altura;}

// retorna a semente inicial usada
int Terreno::obterSemente(){return sementeInicial;}

// retorna altitude mínima
int Terreno::obterAltMinimo(){return altMinimo;}

// retorna altitude máxima
int Terreno::obterAltMaximo(){return altMaximo;}


// retorna a altura em uma posição específica
// caso inválido, retorna valor padrão
int Terreno::obterAltura(int lin, int col)
{
    if ((col >= largura || lin >= altura) || (col < 0 || lin < 0))
    {
        std::cerr << "Erro! Posição inválida.\n";
        static int erro = 0;
        return erro;
    }
    return mapa[lin][col];
}


// gera um valor aleatório dentro do intervalo [altMinimo, altMaximo]
int Terreno::aleatorio()
{
    int intervalo = (altMaximo - altMinimo) + 1;
    int valor = gerarNumero();
    return altMinimo + (valor % intervalo);
}

// gera valor aleatório entre minimo e maximo
int Terreno::aleatorio(int minimo, int maximo)
{
    // garante ordem correta
    if (maximo < minimo)
    {
        int temp = minimo;
        minimo = maximo;
        maximo = temp;
    }

    int valor = gerarNumero();

    // normaliza para intervalo [0,1]
    double t = static_cast<double>(valor) / 0x7FFFFFFF;

    int novoValor = minimo + static_cast<int>(t * (maximo - minimo + 1));

    // garante limite superior
    if (novoValor > maximo)
    {
        novoValor = maximo;
    }

    return novoValor;
}

// insere uma altura no mapa
void Terreno::inserirAltura(int lin, int col, int alt)
{
    mapa[lin][col] = alt;
}

// gera o mapa completo usando o diamond-square
void Terreno::gerarMapa()
{
    // inicializa os quatro cantos com valores aleatórios

    // canto superior esquerdo
    mapa[0][0] = aleatorio();

    // canto superior direito
    mapa[0][largura - 1] = aleatorio();

    // canto inferior esquerdo
    mapa[altura - 1][0] = aleatorio();

    // canto inferior direito
    mapa[altura - 1][largura - 1] = aleatorio();

    // define intervalo inicial de variação
    int menor = altMinimo;
    int maior = altMaximo;

    if (altMaximo < altMinimo)
    {
        menor = altMaximo;
        maior = altMinimo;
    }

    int distInicial = (maior - menor) / 2;
    if (distInicial < 1)
    {
        distInicial = 1;
    }

    // executa algoritmo principal
    diamondSquare(largura, distInicial);

    // ajusta valores para permanecerem dentro dos limites
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            if (mapa[linha][coluna] < altMinimo)
                mapa[linha][coluna] = altMinimo;
            if (mapa[linha][coluna] > altMaximo)
                mapa[linha][coluna] = altMaximo;
        }
    }
}

// transforma o terreno em uma imagem colorida usando uma paleta
Imagem Terreno::carregarTerreno(std::string arquivoPALETA, float fator, int dist, int map)
{
    // carrega paleta de cores
    Paleta paleta(arquivoPALETA);

    int numCores = paleta.obterTamanho();

    // cria imagem com mesmo tamanho do terreno
    Imagem img(altura, largura);

    int min = obterAltMinimo();
    int max = obterAltMaximo();

    int sombreados = 0;

    // percorre o mapa e atribui cores
    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            int alturaAtual = mapa[y][x];

            // normaliza altura para intervalo [0,1]
            double t = double(alturaAtual - min) / (max - min);

            // mapeia para índice da paleta
            int indice = static_cast<int>(t * (numCores - 1));

            if (indice < 0) indice = 0;
            if (indice >= numCores) indice = numCores - 1;

            Cor cor = paleta.obterCor(indice);

            // cálculo de sombra baseado no vizinho noroeste
            int limitarAgua = min + (int)((max - min) * 0.28);

            if (y - dist >= 0 && x - dist >= 0 && alturaAtual > limitarAgua)
            {
                int alturaNoroeste = mapa[y - dist][x - dist];
                if (alturaAtual < alturaNoroeste)
                {
                    // escurece a cor (efeito sombra)
                    cor.r = static_cast<unsigned char>(cor.r * fator);
                    cor.g = static_cast<unsigned char>(cor.g * fator);
                    cor.b = static_cast<unsigned char>(cor.b * fator);
                }
            }
            img.pintar(y, x, cor);
        }
    }
    return img;
}

// salva o mapa de alturas em arquivo
bool Terreno::salvarHeightMap(std::string arquivo)
{
    std::ofstream file(arquivo);

    // verifica abertura
    if (file.is_open() == false)
    {
        return false;
    }

    // escreve dimensões
    file << altura << " " << largura << std::endl;

    // escreve semente
    file << sementeInicial << std::endl;

    // escreve intervalo de alturas
    file << altMinimo << " " << altMaximo << std::endl;

    // escreve matriz de alturas
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            file << mapa[linha][coluna];

            if (coluna < largura - 1)
            {
                file << " ";
            }
        }

        file << std::endl;
    }

    return true;
}

// lê um mapa de alturas de arquivo
bool Terreno::lerHeightMap(std::string arquivo)
{
    std::ifstream file(arquivo);

    // verifica abertura
    if (file.is_open() == false)
    {
        return false;
    }

    // lê dimensões
    file >> altura >> largura;

    // lê semente
    file >> sementeInicial;
    semente = sementeInicial;

    // lê intervalo de alturas
    file >> altMinimo >> altMaximo;

    // aloca memória
    alocarEspaco(altura, largura);

    // lê valores do mapa
    for (int linha = 0; linha < altura; linha++)
    {
        for (int coluna = 0; coluna < largura; coluna++)
        {
            int altitude;
            file >> altitude;
            mapa[linha][coluna] = altitude;
        }
    }

    return true;
}