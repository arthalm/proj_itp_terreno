# Etapa 1 - Criação de uma paleta de cores

### Pré-requisitos
Para a realização desta etapa, você deve estar a par dos seguintes conceitos:
- Classes
- Separação de definições (.h) e implementações (.cpp)
- Leitura de dados de arquivos
- Compilação de vários arquivos em um único executável

### Objetivo
O objetivo desse sub-projeto é definir uma classe capaz de representar uma paleta de cores no formato RGB. Essa paleta será usada para indicar as cores a serem usadas em cada faixa de altitude de um terreno. Por exemplo, a figura abaixo utiliza um conjunto limitado de cores (uma paleta de cores), cada uma representando uma faixa de altitude (as tonalidades de azul são as profundidades na água e as tonalidades verde e marrom na terra).

![Parte de um terreno](./terreno_parcial.png)

### Descrição
Defina novos tipos de dados necessários para representar um conjunto de cores no formato RGB. Para isso, defina inicialmente um tipo para representar uma única cor. Ele deve ser composto de 3 atributos, cujos valores estarão limitados entre 0 e 255:
- R: indicando o componente vermelho do formato RGB;
- G: indicando o componente verde do formato RGB;
- B: indicando o componente azul do formato RGB.

Além deste tipo, é necessário também especificar um tipo para representar um conjunto de cores, de forma que cada cor esteja associada a um índice. Por exemplo, haverá a cor de índice 0, a de índice 1, 2... e assim por diante.

Esse novo tipo deverá ser capaz de responder às seguintes operações:
- **Criar uma paleta vazia**: este será o construtor padrão da classe, inicializando o conjunto com 0 cores.
- **Criar uma paleta a partir de um arquivo**: este será um construtor que recebe o nome de um arquivo como parâmetro e inicializa o conjunto de cores com o conteúdo do arquivo, que deve ter uma linha por cor, no formato hexadecimal. Por exemplo:
```
#d8f2fe
#acd0a5
#93bf8b
#a7c58e
#bdcc96
#d1d7ab
```
- **Adicionar uma cor à paleta**: esta operação deve acrescentar uma cor às já existes na paleta. A cor será incluída no último índice do conjunto.
- **Consultar o número de cores da paleta**: deve retornar a quantidade de cores da paleta.
- **Consultar a cor associada a um determinado índice**: Deve retornar a cor associada a um determinado índice.

### Testes
Para verificar se a paleta de cores está funcionando corretamente, os testes definidos no arquivo `paleta_testes.cpp` devem passar.

