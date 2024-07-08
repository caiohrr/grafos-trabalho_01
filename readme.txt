Trabalho realizado por Caio Henrique Ramos Rufino;

As principais funções no código são:

 - rainhas_bt_recursivo: Implementação da resolução do problema por
backtracking. Ela foi utilizada ao invés da função rainhas_bt devido
aos parametros.

 - conjunto_independente: Função adaptada seguindo o pseudocódigo da
especificação do trabalho.

== Casas proibidas:
As casas proibidas foram representadas por uma matriz de tamanho igual
ao do tabuleiro, mas as casas proibidas foram preenchidas com uma
constante definida como PROIBIDO 2. Na hora de colocar uma rainha, em
uma das duas soluções, bastou checar se o tabuleiro das posições proibidas
estava preenchido naquela posição.

== Solução por backtracking:

Há um bug em que algumas soluções não dão o maior número possível de
rainhas. Não consegui identificar a razão disso.

== Solução por conjunto independente:

Para o grafo que representa o tabuleiro foi utilizada uma matriz de
adjacência. Para encontrar a solução com o maior número de rainhas
possível através desse algoritmo, foi realizado um loop, do maior número
possível de rainhas para o menor. Após diversos testes essa função
funciona corretamente e sempre retorna o resultado esperado. Há entretanto
uma quantidade grande de overhead em relação ao algoritmo de pseudocódigo,
que foi necessário para representação computacional, mais notoriamente,
o tamanho da matriz de adjacência é n^4.

