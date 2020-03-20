#include <bits/stdc++.h>
#define INF INT_MAX

using namespace std;

int min(int dist[], int visited[], int n) {
    int min_i, min_dist = INF;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min_dist) {
            min_i = i;
            min_dist = dist[i];
        }
    }

    return min_i;
}

int main(int argc, const char** argv) {
    int N, M, S;
    int u, v, w;

    scanf("%d %d", &N, &M);
    vector<pair<int, int>> graph[N]; // first -> conexão, second -> peso

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &u, &v, &w);

        graph[u-1].push_back({v-1, w});
        graph[v-1].push_back({u-1, w});
    }

    scanf("%d", &S); S--;

    // Realizando o caminhamento mínimo no grafo
    int dist[N], visited[N]; // vetor de distâncias (ping máximo) e se visitamos uma ilha
    for (int i = 0; i < N; i++) { dist[i] = INF; visited[i] = 0; }
    dist[S] = 0;

    // Aplicando o algoritmo de Dijkstra
    for (int i = 0; i < N - 1; i++) {
        int curr = min(dist, visited, N);
        visited[curr] = 1;

        for (auto p : graph[curr])
            if (!visited[p.first] && dist[curr] + p.second < dist[p.first])
                dist[p.first] = dist[curr] + p.second;
    }

    // // Encontrando o menor e maior valores no vetor de distâncias
    int max_ping = 0, min_ping = INF;
    for (int i = 0; i < N; i++) {
        if (dist[i] > max_ping)
            max_ping = dist[i];

        if (i != S && dist[i] < min_ping)
            min_ping = dist[i];
    }

    printf("%d\n", max_ping - min_ping);

    return 0;
}