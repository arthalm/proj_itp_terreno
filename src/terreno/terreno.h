#include <cmath>

class Terreno {
    int expoente;
    int dimensao;
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

public:

    Terreno(int exp = 0): expoente(exp), dimensao(potencia(exp))
    {
        mapa = new int*[dimensao];
        for (int i = 0; i < dimensao; i++)
        {
            mapa[i] = new int [dimensao];
            for (int j = 0; j < dimensao; j++)
            {
                mapa[i][j] = 0;
            }
        }
    }

    ~Terreno ()
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

};