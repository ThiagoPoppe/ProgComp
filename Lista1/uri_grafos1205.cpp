#include <bits/stdc++.h>
#define MAX_CITIES 1000
#define MAX_SNIPERS 2000

int main(int argc, const char** argv) {
    int N, M, K, A; // número de cidades, estradas, balas e inimigos
    int S, E; // de onde devemos começar e terminar
    double P; // probabilidade de matar um inimigo

    while (scanf("%d %d %d %lf", &N, &M, &K, &P) != EOF) {
        std::vector<int> v[MAX_CITIES];
        int snipers[MAX_SNIPERS] = {0};

        // Lendo as estradas
        for (int i = 0; i < M; i++) {
            int x, y; scanf("%d %d", &x, &y);

            v[x-1].push_back(y-1);
            v[y-1].push_back(x-1);
        }

        // Lendo os snipers inimigos
        scanf("%d", &A);
        for (int i = 0; i < A; i++) {
            int x; scanf("%d", &x);
            snipers[x-1]++;
        }

        // Lendo de onde devemos começar e parar
        scanf("%d %d", &S, &E); S--; E--;
    }

    return 0;
}

