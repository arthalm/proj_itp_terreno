#include <iostream>
#include <cmath>
#include <fstream>
#include "../imagem/imagem.h"

class Terreno
{
    int expoente, altura, largura, **mapa;
    // evitar valores negativos
    unsigned int sementeInicial;
    unsigned int semente;
    int altMinimo, altMaximo;

    void alocarEspaco(int alt, int larg)
    {
        mapa = new int *[alt];
        for (int i = 0; i < alt; i++)
        {
            mapa[i] = new int[larg];
        }
    }

    void limpar()
    {
        if (mapa == nullptr)
            return;
        for (int i = 0; i < altura; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
        mapa = nullptr;
    }

    int potencia(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        return std::pow(2, n) + 1;
    }

    // metodo LCG
    int gerarNumero()
    {
        // A = 1103515245
        // C = 12345
        // M = 0x7fffffff
        semente = (semente * 1103515245 + 12345) & 0x7fffffff;
        return semente;
    }

    void diamond(int linha, int coluna, int alcance, int variacao)
    {
        int cont = 0;
        float media = 0.0;

        if (linha - alcance >= 0)
        {
            media += mapa[linha - alcance][coluna];
            cont++;
        }

        if (linha + alcance < altura)
        {
            media += mapa[linha + alcance][coluna];
            cont++;
        }

        if (coluna - alcance >= 0)
        {
            media += mapa[linha][coluna - alcance];
            cont++;
        }

        if (coluna + alcance < largura)
        {
            media += mapa[linha][coluna + alcance];
            cont++;
        }

        if (cont == 0)
        {
            mapa[linha][coluna] = aleatorio(-variacao, variacao);
            return;
        }

        if (cont > 0)
        {
            media /= cont;
            int ruido = aleatorio(-variacao, variacao);
            int novoValor = (int)(media + ruido);
            mapa[linha][coluna] = novoValor;
        }
    }

    void square(int linha, int coluna, int alcance, int variacao)
    {
        int cont = 0;
        float media = 0.0;

        if (linha - alcance >= 0 && coluna - alcance >= 0)
        {
            media += mapa[linha - alcance][coluna - alcance];
            cont++;
        }

        if (linha - alcance >= 0 && coluna + alcance < largura)
        {
            media += mapa[linha - alcance][coluna + alcance];
            cont++;
        }

        if (linha + alcance < altura && coluna - alcance >= 0)
        {
            media += mapa[linha + alcance][coluna - alcance];
            cont++;
        }

        if (linha + alcance < altura && coluna + alcance < largura)
        {
            media += mapa[linha + alcance][coluna + alcance];
            cont++;
        }

        if (cont == 0)
        {
            mapa[linha][coluna] = aleatorio(-variacao, variacao);
            return;
        }

        if (cont > 0)
        {
            media /= cont;
            int ruido = aleatorio(-variacao, variacao);
            int novoValor = (int)(media + ruido);
            mapa[linha][coluna] = novoValor;
        }
    }

    void diamondSquare(int tamanho, int variacao)
    {
        int metade = tamanho / 2;

        while (metade >= 1)
        {

            for (int linha = metade; linha < tamanho; linha += (metade * 2))
            {
                for (int coluna = metade; coluna < tamanho; coluna += (metade * 2))
                {
                    square(linha, coluna, metade, variacao);
                }
            }

            for (int linha = 0; linha < tamanho; linha += metade)
            {
                for (int coluna = ((linha / metade) % 2 == 0 ? metade : 0); coluna < tamanho; coluna += (metade * 2))
                {
                    diamond(linha, coluna, metade, variacao);
                }
            }

            metade /= 2;

            variacao *= 0.6;
            if (variacao < 1)
            {
                variacao = 1;
            }
        }
    }

    void suavizarMapa(int repeticoes)
    {
        for (int r = 0; r < repeticoes; r++)
        {
            // ALOCAÇÃO MANUAL do mapa temporário
            int **tempMapa = new int *[altura];
            for (int i = 0; i < altura; i++)
            {
                tempMapa[i] = new int[largura];
            }

            // 1. CÓPIA DAS BORDAS (mantém a borda original)
            // e aloca a matriz temporária
            for (int y = 0; y < altura; y++)
            {
                for (int x = 0; x < largura; x++)
                {
                    // Copia o valor atual para o tempMapa
                    tempMapa[y][x] = mapa[y][x];
                }
            }

            // 2. Processamento e Média (ATUALIZA APENAS O INTERIOR)
            for (int y = 1; y < altura - 1; y++)
            {
                for (int x = 1; x < largura - 1; x++)
                {
                    // Filtro de Média 3x3 (Box Blur)
                    int soma = 0;

                    for (int dy = -1; dy <= 1; dy++)
                    {
                        for (int dx = -1; dx <= 1; dx++)
                        {
                            soma += tempMapa[y + dy][x + dx]; // Usa tempMapa[y][x] (valor original)
                        }
                    }
                    // Atualiza o valor diretamente no mapa original
                    mapa[y][x] = soma / 9; // Sempre divide por 9 (3x3)
                }
            }

            // LIBERAÇÃO MANUAL do mapa temporário
            for (int i = 0; i < altura; i++)
            {
                delete[] tempMapa[i];
            }
            delete[] tempMapa;
        }
    }

public:
    Terreno(int exp = 0, int seed = 1, int min = 0, int max = 100)
        : expoente(exp), sementeInicial(seed), semente(seed), altMinimo(min), altMaximo(max)
    {
        altura = potencia(expoente);
        largura = potencia(expoente);

        alocarEspaco(altura, largura);
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                mapa[i][j] = 0;
            }
        }
    }

    ~Terreno()
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

    int obterSemente()
    {
        return sementeInicial;
    }

    int obterAltMinimo()
    {
        return altMinimo;
    }

    int obterAltMaximo()
    {
        return altMaximo;
    }

    int &operator()(int lin, int col)
    {
        if ((col >= largura || lin >= altura) || (col < 0 || lin < 0))
        {
            std::cerr << "Erro! Posição inválida.\n";
            static int erro = 0;
            return erro;
        }
        return mapa[lin][col];
    }

    int aleatorio()
    {
        int intervalo = (altMaximo - altMinimo) + 1;
        int valor = gerarNumero();
        return altMinimo + (valor % intervalo);
    }

    int aleatorio(int minimo, int maximo)
    {
        if (maximo < minimo)
        {
            int temp = minimo;
            minimo = maximo;
            maximo = temp;
        }

        int valor = gerarNumero();
        double t = static_cast<double>(valor) / 0x7FFFFFFF;
        int novoValor = minimo + static_cast<int>(t * (maximo - minimo + 1));

        if (novoValor > maximo)
        {
            novoValor = maximo;
        }

        return novoValor;
    }

    void gerarMapa()
    {
        // canto superior esquerdo
        mapa[0][0] = aleatorio();
        // canto superior direito
        mapa[0][largura - 1] = aleatorio();
        // canto inferior esquerdo
        mapa[altura - 1][0] = aleatorio();
        // canto inferior direito
        mapa[altura - 1][largura - 1] = aleatorio();

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

        diamondSquare(largura, distInicial);
        suavizarMapa(2);

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

    bool salvarHeightMap(std::string arquivo)
    {
        // criar e ler arquivo
        std::ofstream file(arquivo);

        if (file.is_open() == false)
        {
            return false;
        }

        int alt = altura, larg = largura;
        file << alt << " " << larg << std::endl;

        int seed = sementeInicial;
        file << seed << std::endl;

        int min = altMinimo, max = altMaximo;
        file << min << " " << max << std::endl;

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

    bool lerHeightMap(std::string arquivo)
    {
        // ler arquivo
        std::ifstream file(arquivo);

        // vê se o arquivo está fechado
        if (file.is_open() == false)
        {
            return false;
        }

        file >> altura >> largura;

        file >> sementeInicial;
        semente = sementeInicial;

        file >> altMinimo >> altMaximo;

        alocarEspaco(altura, largura);

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

    Imagem carregarTerreno(std::string arquivoPALETA, float fator)
    {
        Paleta paleta(arquivoPALETA);
        int numCores = paleta.obterTamanho();
        Imagem img(altura, largura);

        int min = obterAltMinimo();
        int max = obterAltMaximo();

        int sombreados = 0;

        for (int y = 0; y < altura; y++)
        {
            for (int x = 0; x < largura; x++)
            {
                int alturaAtual = mapa[y][x];

                // Mapear para cor
                double t = double(alturaAtual - min) / (max - min);
                int indice = static_cast<int>(t * (numCores - 1));
                if (indice < 0)
                    indice = 0;
                if (indice >= numCores)
                    indice = numCores - 1;

                Cor cor = paleta.obterCor(indice);

                if (x > 0 && y > 0)
                {
                    int alturaNoroeste = mapa[y - 1][x - 1];

                    // aplicar sombra
                    if (alturaAtual < alturaNoroeste)
                    {
                        cor.r = static_cast<unsigned char>(cor.r * fator);
                        cor.g = static_cast<unsigned char>(cor.g * fator);
                        cor.b = static_cast<unsigned char>(cor.b * fator);
                        sombreados++;
                    }
                }

                img.pintar(y, x, cor);
            }
        }
        return img;
    }
};