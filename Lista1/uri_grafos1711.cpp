#include <bits/stdc++.h>
#define my_pair pair<int,int> // first -> peso, second -> vértice
#define my_graph vector<vector<my_pair>>
#define min_heap priority_queue<my_pair, vector<my_pair>, greater<my_pair>>
using namespace std;

// Função que calcula as distâncias dos caminhos mínimos via Dijkstra
// v := vértice inicial
vector<int> dijkstra(my_graph& graph, int v) {
    int V = graph.size();

    min_heap pq;
    vector<int> dist(V, INT_MAX);

    // O vértice inicial terá distância 0
    pq.push({0, v});
    dist[v] = 0;

    // Computando o caminho mínimo enquanto nossa fila de prioridades não estiver vazia
    while (!pq.empty()) { 
        // Encontrando o vértice com menor distância atualmente
        int minV = pq.top().second;
        pq.pop();

        // Atualizando as distâncias
        for (auto v : graph[minV]) {
            int w = v.first; // peso da aresta
            int u = v.second;
            
            // Atualizaremos se não visitamos o vértice ainda, se (minV, j) existir
            // e se a distância de minV + o peso de (minV, j) for menor que a distância de j
            if (dist[minV] + w < dist[u]) {
                dist[u] = dist[minV] + w;
                pq.push({dist[u], u});
            }
        }
    }

    return dist;
}

void DFS(my_graph& graph, int vis[], vector<int>& dijkstra, int dist[], int& ans, int M, int prev, int curr) {
    vis[curr] = 1;
    
    // Realizando a busca para os demais vértices vizinhos
    for (auto v : graph[curr]) {
        // Se ainda não visitamos o vértice iremos chamar a função recursivamente
        if (!vis[v.second]) {
            dist[v.second] = dist[curr] + v.first;
            DFS(graph, vis, dijkstra, dist, ans, M, curr, v.second);
        }

        // Encontramos o ciclo (chegamos em um vértice visitado por um outro caminho)
        else if (v.second != prev) {
            // Tamanho do caminho completo - caminho até o início do ciclo
            int cycleLen = (dist[curr] + v.first) - dist[v.second];
            
            // O mínimo que a minhoca deve percorrer para realizar esse caminho
            int temp = 2 * dijkstra[v.second] + cycleLen;

            // Se a minhoca passa pelo ciclo e se o menor caminho atual é menor que o global
            if (cycleLen >= M && temp < ans)
                ans = temp;
        }
    }
}

int main(int argc, const char** argv) {
    int S, T, Q;
    int u, v, w;
    int X, M;

    while(scanf("%d %d", &S, &T) != EOF) {
        // Montando o grafo
        my_graph graph(S);
        for (int i = 0; i < T; i++) {
            scanf("%d %d %d", &u, &v, &w);

            graph[u-1].push_back({w, v-1});
            graph[v-1].push_back({w, u-1});
        }

        // Lendo as consultas
        scanf("%d", &Q);
        for (int q = 0; q < Q; q++) {
            scanf("%d %d", &X, &M);
            
            // Calculando os caminhos mínimos via Dijkstra
            vector<int> minCosts = dijkstra(graph, X-1);
            
            int ans = INT_MAX;
            int vis[S], dist[S];
            for (int i = 0; i < S; i++)
                vis[i] = 0, dist[i] = 0;

            DFS(graph, vis, minCosts, dist, ans, M, -1, X-1);

            if (ans == INT_MAX)
                printf("-1\n");
            else
                printf("%d\n", ans);
        }
    }

    return 0;
}