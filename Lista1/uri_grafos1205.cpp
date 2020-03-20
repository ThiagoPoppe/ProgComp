#include <bits/stdc++.h>
#define MAX_CITIES 1000
#define MAX_SNIPERS 2000
#define INF INT_MAX

using namespace std;

// Função para retornar o índice do elemento de menor peso
int min(int dist[MAX_CITIES], bool visited[MAX_CITIES], int N) {
    double min_i = -1, min_dist = INF;

    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[i] <= min_dist) {
            min_i = i;
            min_dist = dist[i];
        }
    }

    return min_i;
}

int main(int argc, const char** argv) {
    int N, M, K, A; // número de cidades, estradas, balas e snipers
    double P; // probabilidade de matar um soldado
    int S, E; // cidade de começo e fim

    int x, y; // variáveis para ler os vértices

    while (scanf("%d %d %d %lf", &N, &M, &K, &P) != EOF) {
        // Criando grafo e vetor de snipers
        vector<int> graph[MAX_CITIES];
        int snipers[MAX_SNIPERS] = {0};

        // Lendo as arestas
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);

            // Assumimos estradas de mão dupla e chance 1.0 de passar por elas (nenhum sniper)
            graph[x-1].push_back(y-1);
            graph[y-1].push_back(x-1);
        }

        // Lendo os snipers
        scanf("%d", &A);
        for (int i = 0; i < A; i++) {
            scanf("%d", &x);
            snipers[x-1]++;
        }

        // Lendo o vértice de entrada e saída
        scanf("%d %d\n", &S, &E); S--; E--;

        // *** ENCONTRANDO O CAMINHO MÍNIMO NO GRAFO ***
        int dist[MAX_CITIES]; // vetor de distâncias (número de snipers visto até então)
        bool visited[MAX_CITIES]; // vetor para sabermos qual cidade visitamos

        // Inicializando os vetores
        for (int i = 0; i < N; i++) { dist[i] = INF; visited[i] = false; }
        dist[S] = snipers[S]; // Iremos inicializar com o número de snipers de S

        // Aplicando dijkstra
        for (int i = 0; i < N; i++) {
            int curr = min(dist, visited, N);
            visited[curr] = true;

            // Atualizando o vetor de distâncias
            for (int v : graph[curr])
                if (!visited[v] && dist[curr] + snipers[v] < dist[v]) 
                    dist[v] = dist[curr] + snipers[v];
        }

        if (dist[E] > K) // não temos balas suficientes
            printf("0.000\n");
        else
            printf("%.3f\n", pow(P, dist[E]));
    }

    return 0;
}