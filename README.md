# Universidade Federal do Paraná
Alunos: 
Rubens Zandomenighi Laszlo - GRR20206147
Gabriel Razzolini Pires de Paula - GRR20197155
Disciplina: Otimização - CI1238         
Data: 29/05/2023


# Modelagem e Implementação por programação linear de uma solução para o problema de Produção de Produtos Químicos

1. Introdução

Dado o problema de Produção de Produtos Químicos em que uma empresa produz n tipos diferentes de produto. Utilizando proporções de m diferentes compostos.
Cada produto i tem valor de venda (por litro), vi. Cada
composto j usado tem um preço (por litro), pj , e um limite diário de volume (em litros), qj.A quantidade (em litros) de uso de cada composto j na
produção de 1 litro do produto i  ́e dada por cij.
Deseja-se maximizar os lucros da empresa, supondo que toda a produção será vendida.

2. Modelagem

3. Implementação

4. Exemplos
Foram gerados exemplos distintos para teste do programa e análise de diferentes casos para o problema apresentado, tais como abordados a seguir: 

4.1. Exemplo em que todos os produtos dão lucros diferentes (exemplo do enunciado)

|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 1.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.3 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.2 | 0.0  | 3     |
|     | CUSTO  | 1    | 2    | 5   | 10   |       |
|     | LIMITE | 1000 | 2000 | 500 | 2000 |       |

INPUT : 
3 4
10 7 3
1 1000
2 2000
5 500
10 2000
0.2 0.5 1.0 0.1
1.0 0.1 0.3 0.1
0.4 0.2 0.2 0.0

OUTPUT PRODUCAO:

max: 2.8x1 + 3.3x2 + 1.2x3;

0.2x1 + 1.0x2 + 0.4x3 <= 1000;
0.5x1 + 0.1x2 + 0.2x3 <= 2000;
1.0x1 + 0.3x2 + 0.2x3 <= 500;
0.1x1 + 0.1x2 + 0.0x3 <= 2000;

x1 >= 0;
x2 >= 0;
x3 >= 0;

OUTPUT LP_SOLVE: 

Value of objective function: 3755.31914894

Actual values of the variables:
x1                        212.766
x2                        957.447
x3                              0

Portanto, uma solução ótima ... contendo ... podemos perceber que ...


4.2. Caso em que foi criado um produto que utiliza um composto com limite de produção baixo porém é o com maior lucro.

|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 0.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.0 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.0 | 0.0  | 3     |
|     | 4      | 0.0  | 0.0  | 0.8 | 0.0  | 100   |
|     | CUSTO  | 1    | 2    | 5   | 10   |       |
|     | LIMITE | 1000 | 2000 | 10  | 2000 |       |



INPUT : 
4 4
10 7 3 100
1 1000
2 2000
5 10
10 2000
0.2 0.5 0.0 0.1
1.0 0.1 0.0 0.1
0.4 0.2 0.0 0.0
0.0 0.0 0.8 0.0 

OUTPUT:
max: 7.8x1 + 4.8x2 + 2.2x3 + 96.0x4;

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 <= 1000;
0.5x1 + 0.1x2 + 0.2x3 + 0.0x4 <= 2000;
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 <= 10;
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 <= 2000;

x1 >= 0;
x2 >= 0;
x3 >= 0;
x4 >= 0;

OUTPUT LP_SOLVE: 

Value of objective function: 33075.00000000

Actual values of the variables:
x1                        3958.33
x2                        208.333
x3                              0
x4                           12.5

Portanto, uma solução ótima ... contendo ... podemos perceber que ...

4.3. Situação em que houve alta nos preço dos compostos e a produção está dando prejuízo para todos os produtos.

|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 0.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.0 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.0 | 0.0  | 3     |
|     | 4      | 0.0  | 0.0  | 0.8 | 0.0  | 100   |
|     | CUSTO  | 100  | 200  | 500 | 100  |       |
|     | LIMITE | 1000 | 2000 | 10  | 2000 |       |


INPUT:
4 4
10 7 3 100
100 1000
200 2000
500 10
100 2000
0.2 0.5 0.0 0.1
1.0 0.1 0.0 0.1
0.4 0.2 0.0 0.0
0.0 0.0 0.8 0.0 

OUTPUT:
max: -120.0x1 + -123.0x2 + -77.0x3 + -300.0x4;

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 <= 1000;
0.5x1 + 0.1x2 + 0.2x3 + 0.0x4 <= 2000;
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 <= 10;
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 <= 2000;

x1 >= 0;
x2 >= 0;
x3 >= 0;
x4 >= 0;

OUTPUT LP_SOLVE: 
Value of objective function: 0

Actual values of the variables:
x1                              0
x2                              0
x3                              0
x4                              0

Portanto, uma solução ótima ... contendo ... podemos perceber que ...


4.4. Dois produtos com a maior margem de lucro, porém limites de compostos diários distintos.
|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 0.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.0 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.0 | 0.0  | 3     |
|     | 4      | 0.0  | 1.0  | 0.8 | 0.0  | 100   |
|     | 5      | 0.1  | 0.0  | 0.8 | 0.0  | 100   |
|     | CUSTO  | 1    | 1    | 5   |  10  |       |
|     | LIMITE | 1000 | 2000 | 200  | 2000 |       |

INPUT:

5 4
10 7 3 100 100
1 1000
1 2000
5 200
10 2000
0.2 0.5 0.0 0.1
1.0 0.1 0.0 0.1
0.4 0.2 0.0 0.0
0.0 0.1 0.8 0.0 
0.1 0.0 0.8 0.0 

OUTPUT:
max: 8.3x1 + 4.9x2 + 2.4x3 + 95.9x4 + 95.9x5;

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 + 0.1x5 <= 1000;
0.5x1 + 0.1x2 + 0.2x3 + 0.1x4 + 0.0x5 <= 2000;
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 + 0.8x5 <= 200;
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 + 0.0x5 <= 2000;

x1 >= 0;
x2 >= 0;
x3 >= 0;
x4 >= 0;
x5 >= 0;

OUTPUT LP_SOLVE:
Value of objective function: 57765.62500000

Actual values of the variables:
x1                        3963.54
x2                        182.292
x3                              0
x4                              0
x5                            250

Portanto, uma solução ótima ... contendo ... podemos perceber que ...



5. Referências
Understanding and Using Linear Programming. Bernd Gärtner e Jiří Matoušek, 2007.