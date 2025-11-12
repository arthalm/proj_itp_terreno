# Geração aleatória de terrenos

**Projeto da disciplina ITP**


## Introdução
Digamos que você deseja fazer um jogo de mundo aberto... só que muito melhor que o GTA 😉. Nesse jogo, os cenários não são fixos, predefinidos. Eles vão sendo criados à medida que o jogador se desloca por eles. Como fazer isso?!

O presente projeto vai te ajudar/conduzir no desenvolvimento de um aplicativo de linha de comando capaz de gerar terrenos de forma procedural, o que implica em poder usá-lo para criar partes do terreno do teu jogo. O projeto vai te guiar também na geração de imagens para você poder visualizar o terreno, como a imagem a seguir.

![Exemplo de terreno](./exemplo_terreno.png)

*Exemplo de imagem criada a partir de um mapa de altitudes (terreno).*

## Organização do projeto
Como todo problema, este projeto pode ser dividido em sub-projetos (ou sub-problemas). Dividir um problema em problemas menores é essencial para a execução de qualquer projeto. Depois de dividido, podemos separar sua execução em etapas.

O primeiro passo para organizar nosso desenvolvimento é identificar elementos que possam ser separados em "módulos". Um módulo é algo que podemos implementar e testar independente dos demais. Depois que cada módulo estiver desenvolvido (e testado), podemos então juntá-los em um único aplicativo.

O presente projeto será estruturado nos seguintes módulos:
- **Paleta**: responsável por representar um conjunto de cores a serem usadas em uma imagem. Veja na imagem acima que cada altitude do terreno tem uma cor associada. As partes mais baixas têm uma tonalidade marrom, que vai embranquecendo cada vez que fica mais alto. As partes mais baixas são identificadas como água (mar, lago etc.), também com diferentes tonalidades. Por isso, podemos definir um módulo próprio para a paleta de cores e definir operações como ler as cores de um arquivo de paleta ou consultar uma cor a ser usada.
- **Imagem**: responsável por representar uma imagem (no nosso caso, através de uma matriz de pixels RGB) e realizar operações como salvar em um determinado formato.
- **Terreno**: responsável por representar um terreno (no nosso caso, será através de um mapa de altitudes) e realizar operações tais como gerar aleatoriamente o terreno, criar uma imagem a partir dele etc.

A seguir vamos descrever como cada um desses módulos podem ser desenvolvidos e testados por etapas. Por fim, teremos a última etapa, que será de juntar todas os módulos em um único aplicativo. Cada etapa será um projeto separado (sub-projeto). Assim, sua equipe deve apresentar os sub-projetos separadamente e, por fim, na etapa 4, apresentar o resultado final.

- **[Etapa 1 - Criação de uma paleta de cores](./etapa1.md)**
- **[Etapa 2 - Criação de imagens no formato PPM](./etapa2.md)**
- **[Etapa 3 - Geração de um mapa de altitudes](./etapa3.md)**
- **[Etapa 4 - Criação de imagens a partir de um mapa de altitudes](./etapa4.md)**
