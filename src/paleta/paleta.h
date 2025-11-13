struct Cor {
    unsigned char r, g, b; //unsigned char vao de 0 a 255
};

class Paleta{
    int capacidade;
    int tamanho;
    Cor *cores;

    void aumentarCapaciadade(){
        capacidade *= 2;
        Cor *novo = new Cor[capacidade];
        for (int i = 0; i < tamanho; i++){
            novo[i] = cores[i];
        }
        delete[] cores;
        cores = novo;
    }

public:
    Paleta(int cap = 2): capacidade(cap), tamanho(0){
        cores = new Cor[capacidade];
    }

    ~Paleta(){
        delete[] cores;
    }

    int obterTamanho(){
        return tamanho;
    }

    Cor obterCor (int n){
        return cores[n];
    }

    void adicionarCor(Cor cor){
        if (tamanho >= capacidade){
            aumentarCapaciadade();
        }
        cores[tamanho] = cor;
        tamanho++;
    }

};