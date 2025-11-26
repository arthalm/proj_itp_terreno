#include <iostream>
#include <cmath>

class Terreno
{
    int expoente;
    int largura;
    int profundidade;
    // evitar valores negativos
    unsigned int semente;
    int **mapa;

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
        semente = (semente * 1103515245 + 12345) % 32768;
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
            mapa[x][y] = limitarValor(novoValor, -variacao*2, variacao*2);
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
            mapa[x][y] = limitarValor(novoValor, -variacao * 2, variacao * 2); // Aproximado
        }
    }

    void diamondSquare( int tamanho, int variacao)
    {
        int metade = tamanho / 2;
        if (metade < 1)
        {
            return;
        }

        for(int y = metade; y < largura; y += tamanho){
            for(int x = metade; x < profundidade; x += tamanho){
                square(x, y, metade, variacao);
            }
        }

        for (int y = 0; y < largura; y += metade)
        {
            for (int x = (y / metade) % 2 == 0 ? metade : 0;
                 x < profundidade;
                 x += tamanho)
            {
                if (x < profundidade && y < largura)
                {
                    diamond(x, y, metade, variacao);
                }
            }
        }

        int novaVariacao = variacao * 0.7;
        if (novaVariacao < 3)
            novaVariacao = 3;
        diamondSquare(metade, novaVariacao);
    }

public:
    Terreno(int exp = 0, int seed = 1)
        : expoente(exp), semente(seed)
    {
        largura = potencia(expoente);
        profundidade = potencia(expoente);

        mapa = new int *[largura];
        for (int i = 0; i < largura; i++)
        {
            mapa[i] = new int[profundidade];
            for (int j = 0; j < profundidade; j++)
            {
                mapa[i][j] = 0;
            }
        }
    }

    ~Terreno()
    {
        for (int i = 0; i < largura; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
    }

    int obterLargura()
    {
        return largura;
    }

    int obterProfundidade()
    {
        return profundidade;
    }

    int &operator()(int lar, int prf)
    {
        if ((lar >= largura || prf >= profundidade) || (lar < 0 || prf < 0))
        {
            std::cerr << "Erro! Posição inválida.\n";
            static int erro = 0;
            return erro;
        }
        return mapa[lar][prf];
    }

    // corrigido para conseguir lidar com numeros negativos
    int aleatorio(int minimo, int maximo)
    {
        int valor = gerarNumero();
        int intervalo = maximo - minimo;

        if (intervalo < 0)
        {
            intervalo = -intervalo;
        }
        intervalo += 1;

        int menor = minimo;
        if (maximo < minimo)
        {
            menor = maximo;
        }
        return menor + (valor % intervalo);
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

        diamondSquare(largura / 2, distInicial);

        for (int i = 0; i < largura; i++)
        {
            for (int j = 0; j < profundidade; j++)
            {
                if (mapa[i][j] < minimo)
                    mapa[i][j] = minimo;
                if (mapa[i][j] > maximo)
                    mapa[i][j] = maximo;
            }
        }
    }
};