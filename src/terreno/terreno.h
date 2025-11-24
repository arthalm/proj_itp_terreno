class Terreno {
    int profundidade, largura;
    int **mapa;

public:

    Terreno(int col = 2, int lin = 2): profundidade(col) , largura(lin)
    {
        mapa = new int*[profundidade];
        for (int i = 0; i < profundidade; i++)
        {
            mapa[i] = new int [largura];
            for (int j = 0; j < largura; j++)
            {
                mapa[i][j] = 0;
            }
        }
    }

    ~Terreno ()
    {
        for (int i = 0; i < profundidade; i++)
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

};