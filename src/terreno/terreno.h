#include <cmath>

class Terreno
{
    int expoente;
    int dimensao;
    int semente;
    int **mapa;

    int potencia(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        int resultado = pow(2, n) + 1;
        return resultado;
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

public:
    Terreno(int exp = 0, int seed = 1) : expoente(exp), dimensao(potencia(exp)), semente(seed)
    {
        mapa = new int *[dimensao];
        for (int i = 0; i < dimensao; i++)
        {
            mapa[i] = new int[dimensao];
            for (int j = 0; j < dimensao; j++)
            {
                mapa[i][j] = 0;
            }
        }
    }

    ~Terreno()
    {
        for (int i = 0; i < dimensao; i++)
        {
            delete[] mapa[i];
        }
        delete[] mapa;
    }

    int obterLargura()
    {
        return dimensao;
    }

    int obterProfundidade()
    {
        return dimensao;
    }

    int aleatorio(int minimo, int maximo)
    {
        int valor = gerarNumero();
        return minimo + (valor % (maximo - minimo + 1));
    }
};