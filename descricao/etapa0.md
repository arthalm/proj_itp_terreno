# Etapa 0 - Criação de um tipo de dado de sequência genérica

### Pré-requisitos
Para a realização desta etapa, você deve estar a par dos seguintes conceitos:
- Classes
- Alocação dinâmica

### Objetivo
Definir um tipo de dado que funcione de forma equivalente ao tipo `vector<>` da biblioteca padrão do C++. Ele pode ser usado como base para criar a paleta de cores e a matriz de pixels de uma imagem.

### Descrição
Defina um tipo de dado capaz de guardar uma sequência de dados. Essa sequência tem:
1. Um atributo indicando sua capacidade, ou seja quantos elementos ela é capaz de armazenar;
2. Um atributo indicando a quantidade de dados que estão armazenados;
3. Um atributo com a sequência de dados armazenados.

Quando uma sequência é criada, ela deve ser inicializada com uma capacidade padrão (você define), mas se novos dados forem inseridos, ela deve ser capaz de se adaptar, alocando mais espaço para guardar novos dados. Ela deve ser também genérica a ponto de poder guardar diferentes tipo de dados (inteiros, strings etc.).

De maneira geral, ela deve funcionar de forma semelhante ao tipo `vector<>` da biblioteca padrão do C++. Assim, podemos:
- **Criar uma sequência padrão**. Será uma sequência com uma capacidade de armazenamento predeterminada, mas sem nenhum dado inserido.
- **Criar uma sequência com uma capacidade informada** (passada por parâmetro). A capacidade é alocada com o tamanho passado, mas sem nenhum dado inserido.
- **Consultar a quantidade de dados armazenados na sequência**. Deve retornar quantos dados a sequência está atualmente armazenando.
- **Inserir um novo dado no final da sequência de dados existente**. Insere um novo dados, mas se a capacidade de armazenamento já tiver sido alcançada, mais espaço deverá ser alocado de forma que mais dados possam ser inseridos. Uma possível estratégia para saber quanto espaço alocar é dobrar sua capacidade atual.
- **Remover um dado do final da sequência de dados existente**. Simplesmente reduz a quantidade de dados armazenado.
- **Consultar o valor de um dado em função de sua posição na sequência (índice).**
- **Alterar o valor do dado que se encontra em uma dada posição da sequência.**

**IMPORTANTE**: Vale salientar que como essa classe lida com alocação dinâmica. Você deverá atentar para liberar a memória quando uma instância da classe (objeto) for descartado (quando seu destrutor for chamado).

### Testes
Para verificar se a paleta de cores está funcionando corretamente, os testes definidos no arquivo `sequencia_testes.cpp` devem passar.
