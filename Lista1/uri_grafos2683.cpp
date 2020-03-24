#include <bits/stdc++.h>
#define INF INT_MAX

typedef std::pair<int, std::pair<int, int>> Gallery;

// Algoritmo de find do Union-Find
int Find(int parent[], int u) {
    if (parent[u] < 0)
        return u;
    else
        return Find(parent, parent[u]);
}

// Algoritmo de union do Union-Find
void Union(int parent[], int u, int v) {
    int pU = Find(parent, u);
    int pV = Find(parent, v);

    // Se pertencerem à conjuntos diferentes
    if (pU != pV) {
        // Escolhendo aquele que tiver mais nodes (menor valor)
        if (parent[pU] < parent[pV]) {
            parent[pU] += parent[pV];
            parent[pV] = u;
        }
        else {
            parent[pV] += parent[pU];
            parent[pU] = v;
        }
    }
}

// Algoritmo para achar a árvore geradora mínima via Kruskal
int findMinMSTCost(std::vector<Gallery>& graph, int V) {
    int minCost = 0;
    int parent[V];
    for (int i = 0; i < V; i++)
        parent[i] = -1;

    int numEdges = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (numEdges > V - 1)
            break;

        int cost = graph[i].first;
        std::pair<int, int> conn = graph[i].second;

        // Se a nova aresta não formar um ciclo
        if (Find(parent, conn.first) != Find(parent, conn.second)) {
            minCost += cost;
            Union(parent, conn.first, conn.second);
            numEdges++;
        }
    }

    return minCost;
}

// Algoritmo para achar a árvore geradora máxima via Kruskal
int findMaxMSTCost(std::vector<Gallery>& graph, int V) {
    int maxCost = 0;
    int parent[V];
    for (int i = 0; i < V; i++)
        parent[i] = -1;

    int numEdges = 0;
    for (int i = graph.size() - 1; i >= 0; i--) {
        if (numEdges > V - 1)
            break;

        int cost = graph[i].first;
        std::pair<int, int> conn = graph[i].second;

        // Se a nova aresta não formar um ciclo
        if (Find(parent, conn.first) != Find(parent, conn.second)) {
            maxCost += cost;
            Union(parent, conn.first, conn.second);
            numEdges++;
        }
    }

    return maxCost;
}

int main(int argc, const char** argv) {
    int N;
    int U, V, W;
    std::vector<Gallery> graph;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &U, &V, &W);
        graph.push_back({W, {U-1, V-1}});
    } // No final, V = número de vértices!

    // Ordenando os pesos para aplicarmos Kruskal
    std::sort(graph.begin(), graph.end());

    printf("%d\n%d\n", findMaxMSTCost(graph, V), findMinMSTCost(graph, V));
    
    return 0;
}