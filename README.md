# EcoChallenge

## Sobre o Projeto

O **EcoChallenge** é um sistema de monitoramento de hábitos sustentáveis desenvolvido em linguagem C. O programa permite que os usuários registrem ações ecológicas, consultem o histórico de atividades realizadas e comparem suas pontuações com as de outros participantes por meio de um ranking.

---

## Funcionalidades

### Menu Principal  
![Menu Principal](assets-EcoChallenge/menu-EcoChallenge.jpeg)  
Tela inicial do programa, onde o usuário pode escolher entre registrar uma ação, visualizar atividades, acessar o ranking ou encerrar o sistema.

### Registro de Nome  
![Entrada de Nome](assets-EcoChallenge/entradaDoNome-EcoChallenge.jpeg)  
Tela onde o usuário insere seu nome para identificação e acompanhamento das ações realizadas.

### Ações Sustentáveis Disponíveis  
![Registro de Ações](assets-EcoChallenge/atividades-EcoChallenge.jpeg)  
Tela para registro de ações ecológicas. Cada opção representa uma prática sustentável, com pontuações diferentes:

1. Separar lixo (10 pontos)  
2. Economia de água (15 pontos)  
3. Economia de energia (15 pontos)  
4. Compostagem (15 pontos)  
5. Reciclagem de materiais (20 pontos)  
6. Organização de trocas (brechó) (25 pontos)  
7. Meios de transportes não poluentes (30 pontos)  
8. Reaproveitamento de água da chuva (30 pontos)  
9. Plantar árvores (50 pontos)

### Visualização de Histórico de Ações  
![Histórico de Ações](assets-EcoChallenge/vizualizadorDeAcoes-EcoChallenge.jpeg)  
Permite consultar o histórico de ações sustentáveis registradas por qualquer participante cadastrado.

### Ranking de Pontuação  
![Ranking](assets-EcoChallenge/ranking-EcoChallenge.jpeg)  
Exibe o ranking com a pontuação acumulada de todos os usuários, promovendo a competitividade e incentivando boas práticas ecológicas.

---

## Estrutura do Sistema

- O sistema suporta até **100 usuários** simultâneos.  
- Cada usuário pode registrar até **15 ações** sustentáveis.  
- As informações são armazenadas **temporariamente** durante a execução do programa.

---

## Como Compilar e Executar

1. Certifique-se de ter um compilador C instalado (como o GCC).
2. Compile o programa com o comando:
   ```bash
   gcc main.c -o ecochallenge

## Autores
- Lorenzo Farias, Bernardo Soares Nunes e Pedro Cabral Buchaim
