template <typename T> //Para usar tipos diferentes de dados
class Sequencia{
    int capacidade;
    int quantidade;
    T *dados;

public:
    //inicialização
    Sequencia (int cap = 2):capacidade(cap), quantidade(0){
        dados = new T[capacidade];
     }

    //destrutor
     ~Sequencia(){
        delete[] dados
     }

     int obterTamanho(){
        return quantidade;
     }
};