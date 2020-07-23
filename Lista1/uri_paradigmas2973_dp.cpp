#include <bits/stdc++.h>

using namespace std;

// Funções de mínimo e máximo
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

// Função para calcular o tempo gasto
int calcTime(int sum, int T) {
    // Tiraremos o teto da divisão da soma pelo número de pipocas máxima
    // para sabermos o tempo gasto para aquele saco
    return (int) ceil((double) sum / T);
}

// Função que realiza a soma de uma parte de um vetor
int arraySum(vector<int>& arr, int begin, int end, int T) {
    int sum = 0;
    for (int i = begin; i < end; i++)
        sum += arr[i];
    
    return calcTime(sum, T);
}

int main(int argc, const char** argv) {
    int N, C, T;
    scanf("%d %d %d", &N, &C, &T);

    // Inicializando os sacos de pipoca
    vector<int> bags(N);
    for (int i = 0; i < N; i++)
        cin >> bags[i];

    // Verificando casos base (apenas 1 saco de pipoca, apenas 1 comedor)
    if (N == 1) {
        cout << calcTime(bags[0], T) << endl;
    }
    else if (C == 1) {
        cout << arraySum(bags, 0, N, T) << endl;
    }
    else {
        // ***** SOLUÇÃO USANDO DP (INVIÁVEL POR SER MUITO GRANDE) ***** //
        // Inicializando a matriz de dp
        int dp[C+1][N+1];
        for (int i = 0; i < C+1; i++)
            for (int j = 0; j < N+1; j++)
                dp[i][j] = 0; // 0 sacos ou 0 competidores são casos inválidos

        // Independente do número de comedores, se tivermos apenas 1 saco será o mesmo tempo
        for (int i = 1; i < C+1; i++)
            dp[i][1] = calcTime(bags[0], T);

        // Independente do número de sacos, se tivermos apenas 1 comedor será a soma dos tempos
        for (int j = 1; j < N+1; j++)
            dp[1][j] = arraySum(bags, 0, j, T);

        // Começaremos o processo de programação dinâmica de (2,2)
        for (int i = 2; i < C+1; i++) {
            for (int j = 2; j < N+1; j++) {
                // O ótimo inicialmente será infinito
                int opt = INT_MAX;

                // p = número de sacos na partição
                for (int p = 1; p <= j; p++) {
                    // A solução ótima será o menor valor entre o valor ótimo atual e o maior
                    // valor entre o valor armazenado para "p" sacos utilizando i-1 comedores
                    // e a soma do tempo gasto para o último comedor comer os sacos restantes.
                    // Tendo assim uma solução "bottom-up"
                    opt = min(opt, max(dp[i-1][p], arraySum(bags, p, j, T)));
                }

                // Armazenando a solução ótima para o caso atual
                dp[i][j] = opt;
            }
        }

        // // DEBUG
        // for (int i = 0; i < C+1; i++) {
        //     for (int j = 0; j < N+1; j++)
        //         printf("%3d ", dp[i][j]);
        //     printf("\n");
        // }

        // Printando a solução ótima
        cout << dp[C][N] << endl;
    }

    return 0;
}