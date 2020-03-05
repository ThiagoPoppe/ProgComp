#include <bits/stdc++.h>

// Algoritmo de busca em profundidade
void DFS(int grafo[26][26], int size, int v, int visited[26], int cc) {
    visited[v] = cc;
    for (int i = 0; i < size; i++)
        if (grafo[v][i] == 1 && visited[i] == -1)
            DFS(grafo, size, i, visited, cc);
}

void find_cc(int grafo[26][26], int size) {
    int cc = 0;
    int visited[26];
    for (int i = 0; i < 26; i++)
        visited[i] = -1;

    // Rodamos a DFS para cada vértice, contando o número de componentes conexos
    for (int i = 0; i < size; i++) {
        if (visited[i] == -1) {
            DFS(grafo, size, i, visited, cc);
            cc++;
        }
    }

    // Imprimindo os vértices de cada componente em ordem crescente
    for (int i = 0; i < cc; i++) {        
        for (int j = 0; j < size; j++) {
            if (visited[j] == i)
                printf("%c,", j + 'a');
        }
        printf("\n");
    }

    printf("%d connected components\n\n", cc);
}

int main(int argc, const char** argv) {
    int n;
    int v, e;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v, &e);

        // Criando o grafo
        int grafo[26][26] = {{0}};

        // Populando o grafo
        for (int j = 0; j < e; j++) {
            char x, y;
            scanf(" %c %c", &x, &y);
            grafo[x % 'a'][y % 'a'] = 1;
            grafo[y % 'a'][x % 'a'] = 1;
        }

        // Encontrando o número de componentes conexos
        printf("Case #%d:\n", i+1);
        find_cc(grafo, v);
    }

    return 0;
}