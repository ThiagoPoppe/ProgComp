#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

bool inBounds(int i, int j, int N, int M) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

void count(vector<vector<int>>& board, int i, int j, int score, int &ans) {
    int N = board.size(), M = board[0].size();

    // Andando para a esquerda superior
    if (inBounds(i-2, j-2, N, M) && board[i-1][j-1] == 2 && board[i-2][j-2] == 0) {
        board[i][j] = 0;
        board[i-1][j-1] = 0;
        board[i-2][j-2] = 1;
        count(board, i-2, j-2, score+1, ans);
        board[i][j] = 1;
        board[i-1][j-1] = 2;
        board[i-2][j-2] = 0;
    }

    // Andando para a direita superior
    if (inBounds(i-2, j+2, N, M) && board[i-1][j+1] == 2 && board[i-2][j+2] == 0) {
        board[i][j] = 0;
        board[i-1][j+1] = 0;
        board[i-2][j+2] = 1;
        count(board, i-2, j+2, score+1, ans);
        board[i][j] = 1;
        board[i-1][j+1] = 2;
        board[i-2][j+2] = 0;
    }

    // Andando para a esquerda inferior
    if (inBounds(i+2, j-2, N, M) && board[i+1][j-1] == 2 && board[i+2][j-2] == 0) {
        board[i][j] = 0;
        board[i+1][j-1] = 0;
        board[i+2][j-2] = 1;
        count(board, i+2, j-2, score+1, ans);
        board[i][j] = 1;
        board[i+1][j-1] = 2;
        board[i+2][j-2] = 0;
    }

    // Andando para a direita inferior
    if (inBounds(i+2, j+2, N, M) && board[i+1][j+1] == 2 && board[i+2][j+2] == 0) {
        board[i][j] = 0;
        board[i+1][j+1] = 0;
        board[i+2][j+2] = 1;
        count(board, i+2, j+2, score+1, ans);
        board[i][j] = 1;
        board[i+1][j+1] = 2;
        board[i+2][j+2] = 0;
    }

    if (score > ans)
        ans = score;

    return;
}

int main(int argc, const char** argv) {
    int nRows, nCols;
    cin >> nRows >> nCols;

    while (nRows != 0 && nCols != 0) {
        vector<vector<int>> board(nRows, vector<int>(nCols));
        int n = (int) ceil((double) (nRows*nCols) / 2);
        int row = nRows - 1, col = 0;

        // Montando a matriz
        for (int i = 0; i < n; i++) {
            int state;
            cin >> state;
        
            board[row][col] = state;
            
            // Atualizando linha e coluna
            if (nCols % 2 == 0) { // Número par de colunas
                if (col == nCols - 2)      { row--; col = 1; }
                else if (col == nCols - 1) { row--; col = 0; }
                else                       { col += 2;       }
            }
            else { // Número ímpar de colunas
                if (col == nCols - 1)      { row--; col = 1; }
                else if (col == nCols - 2) { row--; col = 0; }
                else                       { col += 2;       }
            }
        }
            
        int ans = 0;
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                if (board[i][j] == 1)
                    count(board, i, j, 0, ans);

        cout << ans << endl;
        cin >> nRows >> nCols;
    }

    return 0;
}