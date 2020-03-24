#include <bits/stdc++.h>
#define MAX 20
#define BLACK -1
#define EMPTY 0
#define PLAYER 1
#define ENEMY 2

using namespace std;

/*
    - Ideia:
        1) Para cada casa com peças do jogador, verificar a redondeza
        2) Se tivermos peça do inimigo E casa vazia, verificamos recursivamente
*/

int max(int a, int b) { return a > b ? a : b; }

bool hasVisited(vector<pair<int, int>>& v, int i, int j) { return find(v.begin(), v.end(), make_pair(i, j)) != v.end(); }

int max_play(int board[MAX][MAX], vector<pair<int,int>>& visited, int i, int j, int N, int M) {
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    visited.push_back({i, j});

    // Andando para canto superior esquerdo
    if (i - 1 >= 0 && j - 1 >= 0)
        if (board[i-1][j-1] == ENEMY && board[i-2][j-2] == EMPTY && !hasVisited(visited, i-2, j-2))
            v1 = 1 + max_play(board, visited, i-2, j-2, N, M);
    
    // Andando para canto superior direito
    if (i - 1 >= 0 && j + 1 < M)
        if (board[i-1][j+1] == ENEMY && board[i-2][j+2] == EMPTY && !hasVisited(visited, i-2, j+2))
            v2 = 1 + max_play(board, visited, i-2, j+2, N, M);

    // Andando para canto inferior esquerdo
    if (i + 1 < N && j - 1 >= 0)
        if (board[i+1][j-1] == ENEMY && board[i+2][j-2] == EMPTY && !hasVisited(visited, i+2, j-2))
            v3 = 1 + max_play(board, visited, i+2, j-2, N, M);

    // Andando para canto inferior direito
    if (i + 1 < N && j + 1 < M)
        if (board[i+1][j+1] == ENEMY && board[i+2][j+2] == EMPTY && !hasVisited(visited, i+2, j+2))
            v4 = 1 + max_play(board, visited, i+2, j+2, N, M);

    return max(max(v1, v2), max(v3, v4));
}

int main(int argc, const char** argv) {
    int N, M;
    int board[MAX][MAX];

    scanf("%d %d", &N, &M);
    while (N != 0 && M != 0) {
        vector<pair<int, int>> indices; // vetor de indíces das peças do jogador

        // Inicializando o tabuleiro
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                board[i][j] = BLACK;

        // Preenchendo o tabuleiro com os estados
        bool alternate = true; // Variável para alteramos a coloração das casas
        for (int i = N - 1; i >= 0; i--) {
            int start = alternate ? 0 : 1; alternate = !alternate;
            for (int j = start; j < M; j += 2) {
                scanf("%d", &board[i][j]);
                if (board[i][j] == PLAYER)
                    indices.push_back({i, j});
            }
        }

        // printf("(");
        // for (auto p : indices)
        //     printf("{%d, %d},", p.first, p.second);
        // printf(")\n");

        if (indices.size() != 0) {
            int result = 0;
            for (auto p : indices) {
                vector<pair<int, int>> visited;
                result = max(max_play(board, visited, p.first, p.second, N, M), result);
            }

            printf("%d\n", result);
        }
        else {
            printf("0\n");
        }

        // // DEBUG
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < M; j++)
        //         printf("%d ", board[i][j]);

        //     printf("\n");
        // }
        // printf("\n");

        scanf("%d %d", &N, &M);
    }

    return 0;
}