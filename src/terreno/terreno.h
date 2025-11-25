#include <cmath>

class Terreno {
    int expoente;
    int largura;
    int profundidade;
    //evitar valores negativos
    unsigned int semente;
    int **mapa;

    int potencia(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        return pow (2, n) + 1;
    }

        //metodo LCG
    int gerarNumero()
    {
        //A = 1103515245
        //C = 12345
        //M = 32768 (potencia de 2 (2¹⁵))
        semente = (semente * 1103515245 + 12345) % 32768;
        return semente;
    }

public:
    Terreno(int exp = 0, int seed = 1)
        : expoente(exp),
          largura(potencia(exp)),
          profundidade(potencia(exp)),
          semente(seed)
    {
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

    ~Terreno ()
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
            std::cerr << "Erro! Posição de pixel inválida.\n";
            static int erro = 0;
            return erro;
        }
        return mapa[lar][prf];
    }

    int aleatorio (int minimo, int maximo)
    {
        int valor = gerarNumero();
        return minimo + (valor % (maximo - minimo + 1));
    }


};