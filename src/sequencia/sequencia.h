template <typename T> //Para usar tipos diferentes de dados
class Sequencia{
    int capacidade;
    int quantidade;
    T *dados;

    //criar funçao que aumenta tamanho
    void aumentarCapacidade()
    {
        capacidade *= 2;
        T *novo = new T[capacidade];
        for (int i = 0; i < tamanho; i++)
        {
            novo[i] = dados[i];
        }
        delete[] dados;
        dados = novo;
    }

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

     void adicionarElemento(T n){
        if (quantidade >= capacidade){
            //chamar a funçao que aumenta tamanho
        }
        dados[quantidade] = n;
        quantidade++;
     }
};