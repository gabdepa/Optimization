# Universidade Federal do Paraná
Alunos: <br> 
Rubens Zandomenighi Laszlo - GRR20206147<br> 
Gabriel Razzolini Pires de Paula - GRR20197155<br> 
Disciplina: Otimização - CI1238      <br>    
Data: 29/05/2023<br> 


# Modelagem e Implementação por programação linear de uma solução para o problema de Produção de Produtos Químicos

## 1. Introdução
Dado o problema de Produção de Produtos Químicos em que uma empresa produz n tipos diferentes de produto. Utilizando proporções de m diferentes compostos.
Cada produto i tem valor de venda (por litro), vi. Cada
composto j usado tem um preço (por litro), pj , e um limite diário de volume (em litros), qj.A quantidade (em litros) de uso de cada composto j na
produção de 1 litro do produto i é dada por cij.<br> 
Deseja-se maximizar os lucros da empresa, supondo que toda a produção será vendida.

## 2. Modelagem
Conforme a introdução do problema, dados que: 
n: Quantidade de produtos, 
m: Quantidade de compostos,
vi: Valor de venda do produto i,
xi: Variável que representa a quantidade para o produto xi,
cij: Custo de cada composto j na produção do produto ,
pj: Preço por litro do composto j, 
qj: Limite diário de volume para o composto j,

Como é desejado a maximização do lucro da empresa, modelamos o problema tal que a função objetiva: z = (∑(vi - cij)) * xi, para todo xi pertencente aos produtos. Já para as restrições, utilizamos as células referentes aos produtos x compostos para restringir a quantidade dos compostos conforme os limites diários, gerando uma restrição para cada composto utilizado, tal que: (cij * xi) ≤ qj para todo j pertencente aos compostos e i pertencente aos produtos.
Assim, geramos ao seguinte modelo: <br> <br> 
Max z = (∑(vi - cij)) * xi  <br> 
Sujeito a:  <br> 
    c[1][1]* (x1) + c[2][1] * (x2+1) + ... + c[n][1] * (Xn) <br> 
    c[1][2]* (x1) + c[2][2] * (x2+1) + ... + c[n][2] * (Xn) <br> 
    ... <br> 
    c[1][m] * (xi) + c[2][m] * (xi+1) + ... + c[n][m]* (Xn) <br> 
xi >= 0, para todo xi ∈ R <br> 

## 3. Implementação
O objetivo deste projeto é a geração uma saída para ser usada pelo resolvedor lp_solve, tal que a entrada segue o formato segue o padrão, a seguir;
O trabalho está dividido em dois arquivos: producao.awk e makefile, e um diretório contento do exemplos que utilizamos para testes e análises das gerações do programa: examples. 
### Entrada: 
* Inicia com dois números inteiros n e m indicando a quantidade de produtos e compostos, respectivamente.
* n números indicando os preços de venda (de 1 litro, vi) de cada produto.
* m linhas, com 2 números em cada, indicando o custo (de 1 litro,pj ) e o limite de produçao (qj ) de cada composto usado como matériaprima. 
* n × m números indicando a quantidade de cada composto usada na produção de 1 litro de cada produto.
### Saída 
Saída seguindo os padrão aceito pelo lp_solve, abordada com mais detalhes nos exemplos na seção 4.
### Algoritmo:
Percorremos as linhas de entrada do arquivo,atribuindo ao vetor V os valores dos produtos, ao vetor C os custos dos produtos, o vetor L os limites dos compostos e as proporções de compostos/produto à matriz P. <br>
Após percorrermos a entrada, geramos a saída conforme impressão "max", somando a variável cost os custos para produção de cada produto (somatório(<P[i][j]>preço_dos_compostos * <C[j]> porcentagem_no_produto)), atribuindo então à variável profit o lucro do produto i: profit = V[i] - cost. Posteriormente impressão da unção de maximização conforme profit[i], i + 1, e finalmente, a impressão das restrições conforme citados na seção de modelagem de cada composto e seu limite diário e as variáveis de não restrição.
  
## 4. Exemplos
Foram gerados exemplos distintos para teste do programa e análise de diferentes casos para o problema apresentado, tais como abordados a seguir: 

### 4.1. Exemplo em que todos os produtos dão lucros diferentes (exemplo do enunciado)

|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 1.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.3 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.2 | 0.0  | 3     |
|     | CUSTO  | 1    | 2    | 5   | 10   |       |
|     | LIMITE | 1000 | 2000 | 500 | 2000 |       |

INPUT : 
3 4 <br> 
10 7 3 <br> 
1 1000 <br> 
2 2000 <br> 
5 500 <br> 
10 2000 <br> 
0.2 0.5 1.0 0.1 <br> 
1.0 0.1 0.3 0.1 <br> 
0.4 0.2 0.2 0.0 <br> 

OUTPUT PRODUCAO:

max: 2.8x1 + 3.3x2 + 1.2x3;

0.2x1 + 1.0x2 + 0.4x3 <= 1000; <br> 
0.5x1 + 0.1x2 + 0.2x3 <= 2000; <br> 
1.0x1 + 0.3x2 + 0.2x3 <= 500; <br> 
0.1x1 + 0.1x2 + 0.0x3 <= 2000; <br> 

x1 >= 0; <br> 
x2 >= 0; <br> 
x3 >= 0; <br> 

OUTPUT LP_SOLVE: <br>  

Value of objective function: 3755.31914894 <br> 

Actual values of the variables:
x1                        212.766 <br> 
x2                        957.447 <br> 
x3                              0 <br> 

Portanto, uma solução ótima tem lucro de R$ 3755.31 com 212,766 litros do produto 1 e 957,44 do produto 2  e 0 litros do produto 3, podemos perceber que a solução gerada é a mesma do enunciado, conforme esperado. 


### 4.2. Caso em que foi criado um produto que utiliza um composto com limite de produção baixo porém é o com maior lucro.

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
10 7 3 100<br> 
1 1000<br>  
2 2000 <br> 
5 10 <br> 
10 2000 <br> 
0.2 0.5 0.0 0.1 <br> 
1.0 0.1 0.0 0.1 <br> 
0.4 0.2 0.0 0.0 <br> 
0.0 0.0 0.8 0.0 <br> 

OUTPUT: <br> 
max: 7.8x1 + 4.8x2 + 2.2x3 + 96.0x4; <br> 

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 <= 1000; <br> 
0.5x1 + 0.1x2 + 0.2x3 + 0.0x4 <= 2000;<br> 
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 <= 10;<br> 
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 <= 2000;<br> 

x1 >= 0;<br> 
x2 >= 0;<br> 
x3 >= 0;<br> 
x4 >= 0;<br> 

OUTPUT LP_SOLVE: <br>  

Value of objective function: 33075.00000000

Actual values of the variables:
x1                        3958.33<br> 
x2                        208.333<br> 
x3                              0<br> 
x4                           12.5<br> 

Portanto, uma solução ótima tem lucro de R$ 33075.00 com 3958,3958.33 litros do produto 1, 208,333 do produto 2, 0 litros do produto 3 e 12,5 litros do produto 4, podemos perceber que a solução gerada como o produto de maior lucro consiste em grande parte de uma matéria prima com baixo limite de produção diária, foi necessário a distribuição entre outros produtos também na produção. 

4.3. Situação em que houve alta nos preços dos compostos e a produção está dando prejuízo para todos os produtos.

|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 0.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.0 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.0 | 0.0  | 3     |
|     | 4      | 0.0  | 0.0  | 0.8 | 0.0  | 100   |
|     | CUSTO  | 100  | 200  | 500 | 100  |       |
|     | LIMITE | 1000 | 2000 | 10  | 2000 |       |


INPUT: <br> 
4 4<br> 
10 7 3 100<br> 
100 1000<br> 
200 2000<br> 
500 10<br> 
100 2000<br> 
0.2 0.5 0.0 0.1<br> 
1.0 0.1 0.0 0.1<br> 
0.4 0.2 0.0 0.0<br> 
0.0 0.0 0.8 0.0 <br> 

OUTPUT: <br> 
max: -120.0x1 + -123.0x2 + -77.0x3 + -300.0x4;

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 <= 1000;<br> 
0.5x1 + 0.1x2 + 0.2x3 + 0.0x4 <= 2000;<br> 
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 <= 10;<br> 
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 <= 2000;<br> 

x1 >= 0;<br> 
x2 >= 0;<br> 
x3 >= 0;<br> 
x4 >= 0;<br> 

OUTPUT LP_SOLVE: <br>  
Value of objective function: 0

Actual values of the variables:
x1                              0
x2                              0
x3                              0
x4                              0

Portanto, uma solução ótima tem lucro de R$ 0.00 com 0 litros do produto 1, 0 do produto 2, 0 litros do produto 3 e 0 litros do produto 4, podemos perceber que a solução gerada como a produção de todos os produtos está gerando prejuízo, a solução ótima para maximizar o lucro é a de não produzir. 


### 4.4. Dois produtos com a maior margem de lucro, porém limites de compostos diários distintos.
|     |        | COM  | POS  | TOS |      |       |
|-----|--------|------|------|-----|------|-------|
|     | N/M    | 1    | 2    | 3   | 4    | VALOR |
| PRO | 1      | 0.2  | 0.5  | 0.0 | 0.1  | 10    |
| DU  | 2      | 1.0  | 0.1  | 0.0 | 0.1  | 7     |
| TOS | 3      | 0.4  | 0.2  | 0.0 | 0.0  | 3     |
|     | 4      | 0.0  | 0.1  | 0.8 | 0.0  | 100   |
|     | 5      | 0.1  | 0.0  | 0.8 | 0.0  | 100   |
|     | CUSTO  | 1    | 1    | 5   |  10  |       |
|     | LIMITE | 1000 | 2000 | 200  | 2000 |      |

INPUT: <br> 

5 4<br> 
10 7 3 100 100<br> 
1 1000<br> 
1 2000<br> 
5 200<br> 
10 2000<br> 
0.2 0.5 0.0 0.1<br> 
1.0 0.1 0.0 0.1<br> 
0.4 0.2 0.0 0.0<br> 
0.0 0.1 0.8 0.0 <br> 
0.1 0.0 0.8 0.0 <br> 

OUTPUT: <br> 
max: 8.3x1 + 4.9x2 + 2.4x3 + 95.9x4 + 95.9x5;

0.2x1 + 1.0x2 + 0.4x3 + 0.0x4 + 0.1x5 <= 1000;<br> 
0.5x1 + 0.1x2 + 0.2x3 + 0.1x4 + 0.0x5 <= 2000;<br> 
0.0x1 + 0.0x2 + 0.0x3 + 0.8x4 + 0.8x5 <= 200;<br> 
0.1x1 + 0.1x2 + 0.0x3 + 0.0x4 + 0.0x5 <= 2000;<br> 

x1 >= 0;<br> 
x2 >= 0;<br> 
x3 >= 0;<br> 
x4 >= 0;<br> 
x5 >= 0;<br> 

OUTPUT LP_SOLVE: <br> 
Value of objective function: 57765.62500000

Actual values of the variables:
x1                        3963.54
x2                        182.292
x3                              0
x4                              0
x5                            250

Portanto, uma solução ótima tem lucro de R$ 57765,62 com 3963,54 litros do produto 1, 182,292 do produto 2, 0 litros do produto 3, 0 litros do produto 4,250 litros do produto 5, podemos perceber que mesmo que os produtos x4 e x5 tem o mesmo lucro de produção foi optado pela produção do produto x5 para maximização também do lucro obtido com os outros produtos. 


5. Referências
Understanding and Using Linear Programming. Bernd Gärtner e Jiří Matoušek, 2007.