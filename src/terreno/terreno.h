#include <iostream>
#include <cmath>

class Terreno
{
    int expoente, profundidade, largura, **mapa;
    // evitar valores negativos
    unsigned int semente;

    void alocarEspaco(int prf, int larg)
    {
        mapa = new int *[prf];
        for (int i = 0; i < prf; i++)
        {
            mapa[i] = new int[larg];
        }
    }

    void limpar()
    {
        if (mapa == nullptr)
            return;
        for (int i = 0; i < profundidade; i++)
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
        // M = 32768 (potencia de 2 (2¹⁵))
        semente = (semente * 1103515245 + 12345) & 0x7fffffff;
        return semente;
    }

    void diamond(int x, int y, int alcance, int variacao)
    {
        int cont = 0;
        float media = 0.0;

        if (x - alcance >= 0)
        {
            media += mapa[x - alcance][y];
            cont++;
        }

        if (x + alcance < profundidade)
        {
            media += mapa[x + alcance][y];
            cont++;
        }

        if (y - alcance >= 0)
        {
            media += mapa[x][y - alcance];
            cont++;
        }

        if (y + alcance < largura)
        {
            media += mapa[x][y + alcance];
            cont++;
        }

        if (cont == 0)
        {
            mapa[x][y] = aleatorio(-variacao, variacao);
            return;
        }

        if (cont > 0)
        {
            media /= cont;
            int ruido = aleatorio(-variacao, variacao);
            int novoValor = (int)(media + ruido);
            mapa[x][y] = novoValor;
        }
    }

    void square(int x, int y, int alcance, int variacao)
    {
        int cont = 0;
        float media = 0.0;

        if (x - alcance >= 0 && y - alcance >= 0)
        {
            media += mapa[x - alcance][y - alcance];
            cont++;
        }

        if (x - alcance >= 0 && y + alcance < largura)
        {
            media += mapa[x - alcance][y + alcance];
            cont++;
        }

        if (x + alcance < profundidade && y - alcance >= 0)
        {
            media += mapa[x + alcance][y - alcance];
            cont++;
        }

        if (x + alcance < profundidade && y + alcance < largura)
        {
            media += mapa[x + alcance][y + alcance];
            cont++;
        }

        if (cont == 0)
        {
            mapa[x][y] = aleatorio(-variacao, variacao);
            return;
        }

        if (cont > 0)
        {
            media /= cont;
            int ruido = aleatorio(-variacao, variacao);
            int novoValor = (int)(media + ruido);
            mapa[x][y] = novoValor;
        }
    }

    void diamondSquare(int tamanho, int variacao)
    {
        int metade = tamanho / 2;

        while (metade >= 1)
        {

            for (int x = metade; x < tamanho; x += (metade * 2))
            {
                for (int y = metade; y < tamanho; y += (metade * 2))
                {
                    square(x, y, metade, variacao);
                }
            }

            for (int x = 0; x < tamanho; x += metade)
            {
                for (int y = ((x / metade) % 2 == 0 ? metade : 0); y < tamanho; y += (metade * 2))
                {
                    diamond(x, y, metade, variacao);
                }
            }

            metade /= 2;

            variacao *= 0.5;
            if (variacao < 1)
            {
                variacao = 1;
            }
        }
    }

public:
    Terreno(int exp = 0, int seed = 1)
        : expoente(exp), semente(seed)
    {
        profundidade = potencia(expoente);
        largura = potencia(expoente);

        alocarEspaco(profundidade, largura);
        for (int i = 0; i < profundidade; i++)
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

    int obterProfundidade()
    {
        return profundidade;
    }

    int obterSemente()
    {
        return semente;
    }

    int &operator()(int prf, int larg)
    {
        if ((larg >= largura || prf >= profundidade) || (larg < 0 || prf < 0))
        {
            std::cerr << "Erro! Posição inválida.\n";
            static int erro = 0;
            return erro;
        }
        return mapa[prf][larg];
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
        int intervalo = (maximo - minimo) + 1; // sem o 1 nunca geraria o valor maximo
        return minimo + (valor % intervalo);
    }

    int limitarValor(int valor, int minimo, int maximo)
    {
        if (valor < minimo)
        {
            return minimo;
        }
        if (valor > maximo)
        {
            return maximo;
        }
        return valor;
    }

    void gerarMapa(int minimo, int maximo)
    {
        // canto superior esquerdo
        mapa[0][0] = aleatorio(minimo, maximo);
        // canto superior direito
        mapa[0][largura - 1] = aleatorio(minimo, maximo);
        // canto inferior esquerdo
        mapa[profundidade - 1][0] = aleatorio(minimo, maximo);
        // canto inferior direito
        mapa[profundidade - 1][largura - 1] = aleatorio(minimo, maximo);
        // centro da matriz
        mapa[profundidade / 2][largura / 2] = aleatorio(minimo, maximo);

        int h = (largura - 1) / 2;

        // meios dos lados
        mapa[h][0] = aleatorio(minimo, maximo);
        mapa[0][h] = aleatorio(minimo, maximo);
        mapa[h][largura - 1] = aleatorio(minimo, maximo);
        mapa[largura - 1][h] = aleatorio(minimo, maximo);

        int menor = minimo;
        int maior = maximo;
        if (maximo < minimo)
        {
            menor = maximo;
            maior = minimo;
        }

        int distInicial = (maior - menor) / 2;
        if (distInicial < 1)
        {
            distInicial = 1;
        }

        diamondSquare(largura, distInicial);

        for (int x = 0; x < profundidade; x++)
        {
            for (int y = 0; y < largura; y++)
            {
                if (mapa[x][y] < minimo)
                    mapa[x][y] = minimo;
                if (mapa[x][y] > maximo)
                    mapa[x][y] = maximo;
            }
        }
    }

    bool salvarHeightMap(std::string arquivo, int min, int max)
    {
        // criar e ler arquivo
        std::ofstream file(arquivo);

        if (file.is_open() == false)
        {
            return false;
        }

        int prf = profundidade, larg = largura;

        file << prf << " " << larg << std::endl;

        int seed = semente;
        file << seed << std::endl;

        file << min << " " << max << std::endl;

        for (int x = 0; x < profundidade; x++)
        {
            for (int y = 0; y < largura; y++)
            {
                file << mapa[x][y];
                if (y < largura - 1)
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

        file >> profundidade >> largura;

        file >> semente;

        int min, max;
        file >> min >> max;

        alocarEspaco(profundidade, largura);

        for (int x = 0; x < profundidade; x++)
        {
            for (int y = 0; y < largura; y++)
            {
                int altitude;
                file >> altitude;
                mapa[x][y] = altitude;
            }
        }
        return true;
    }
};