struct Pixel
{
    unsigned char r, g, b; // unsigned char vao de 0 a 255
};

class Imagem
{
    int largura, altura;
    Pixel **pixels;

public:
    Imagem(int lar = 0, int alt = 0) : largura(lar), altura(alt)
    {
        pixels = new Pixel *[largura];
        for (int i = 0; i < largura; i++)
        {
            pixels[i] = new Pixel[altura];
        }
    }

    ~Imagem()
    {
        for (int i = 0; i < largura; i++)
        {
            delete[] pixels[i];
        }
        delete[] pixels;
    }

    int obterLargura()
    {
        return largura;
    }

    int obterAltura()
    {
        return altura;
    }

    Pixel &operator()(int lar, int alt)
    {
        if ((lar > largura || alt > altura) || (lar < 0 || alt < 0))
        {
            std::cerr << "Erro! Posição de pixel inválida.\n";
        }
        return pixels[lar][alt];
    }
};