#include <bits/stdc++.h>
#define QUANT 100
#define W 50

// Função auxiliar para determinar o maior inteiro
int max(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, const char** argv) {
    int n, m;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int memo[QUANT + 1][W + 1] = {{0}};
        int pac[2][QUANT + 1];

        // Lendo a quantidade de brinquedos [0] e peso de cada pacote [1]
        scanf("%d", &m);
        for (int j = 1; j <= m; j++)
            scanf("%d %d", &pac[0][j], &pac[1][j]);
    
        // Ideia: resolver o problema da mochila 0-1 usando programação dinâmica
        // Usar estratégia bottom-up. Ou seja, a mochila possui pesos de 0 até W
        // Caso inserimos um elemento, verificamos o max(val + memo[x-1][y - peso], memo[x-1][y])
        // OBS.: É mais fácil começarmos de 1 e não 0, pois não teremos problemas com memo[x-1]...
        for (int x = 1; x <= m; x++)
            for (int y = 1; y <= W; y++) {
                // Conseguimos inserir um elemento
                if (pac[1][x] <= y)
                    memo[x][y] = max(pac[0][x] + memo[x-1][y - pac[1][x]], memo[x-1][y]);
                
                // Não conseguimos inserir um elemento
                else
                    memo[x][y] = memo[x-1][y];
            }

        // "Backtracking" para sabermos quais pacotes escolhemos
        int weight = 0;
        int numPac = 0;
        int x = m, y = W;

        while (memo[x][y] != 0) {
            // O valor da célula atual "veio de cima", ou seja, não escolhemos o x-ésimo item
            if (memo[x-1][y] == memo[x][y]) 
                x--;

            // Senão, escolhemos o item e precisamos atualizar os valores
            else {
                numPac++;
                weight += pac[1][x];
                y -= pac[1][x];
                x--;
            }
        }

        printf("%d brinquedos\n", memo[m][W]);
        printf("Peso: %d kg\n", weight);
        printf("sobra(m) %d pacote(s)\n\n", m - numPac);
    }

    return 0;
}