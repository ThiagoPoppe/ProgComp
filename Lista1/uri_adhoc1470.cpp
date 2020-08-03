#include <bits/stdc++.h>
using namespace std;

// Debug
void print_vector(vector<int>& v) {
    for (int i : v)
        printf("%d ", i);
    printf("\n");
}

// Função que verifica se duas fitas são iguais
bool equal(vector<int>& t1, vector<int>& t2) {
    if (t1.size() != t2.size())
        return false;

    for (int i = 0; i < t1.size(); i++)
        if (t1[i] != t2[i])
            return false;
    return true;
}

// Função que verifica se uma fita é o inverso da outra
bool reverse(vector<int>& t1, vector<int>& t2) {
    if (t1.size() != t2.size())
        return false;

    int n = t1.size();
    for (int i = 0; i < n; i++)
        if (t1[i] != t2[n-1-i])
            return false;
    return true;
}

// Função que soma todos os elementos de uma fita
int sum(vector<int>& t) {
    int s = 0;
    for (int i = 0; i < t.size(); i++)
        s += t[i];

    return s;
}

// Função que dobra a fita
vector<int> fold_tape(vector<int>& t, int fold) {
    vector<int> folded;
    int n = t.size();

    // Casos onde a fita é dobrada no começo ou final
    if (fold == 0 || fold == n) {
        for (int i = n-1; i >= 0; i--)
            folded.push_back(t[i]);
    }

    // Caso onde a fita é dobrada no meio (|esquerda| == |direita|)
    else if (fold == (n-fold)) {
        for (int i = 0; i < n/2; i++) {
            int val = t[i] + t[n-1-i];
            folded.push_back(val);
        }
    }
    
    // Caso onde a fita é dobrada antes do meio (|esquerda| < |direita|)
    else if (fold < (n-fold)) {
        for (int i = n-1; i > 2*fold-1; i--) //adicionando os elementos restantes
            folded.push_back(t[i]);

        for (int i = 0; i < fold; i++) {
            int val = t[i] + t[2*fold-1-i];
            folded.push_back(val);
        }
    }

    // Caso onde a fita é dobrada depois do meio (|esquerda| > |direita|)
    else if (fold > (n-fold)) {
        for (int i = 0; i < 2*fold-n; i++) //adicionando os elementos iniciais
            folded.push_back(t[i]);

        int j = 0;
        for (int i = 2*fold-n; i < fold; i++) {
            int val = t[i] + t[n-1-j];
            folded.push_back(val);
            j++;
        }
    }

    return folded;
} 

// Função que dobra a fita tentando procurar a solução
bool foundSolution(vector<int>& t1, vector<int>& t2) {
    if (t1.size() < t2.size())
        return false;
    
    if (equal(t1, t2) || reverse(t1, t2))
        return true;

    for (int i = 1; i < t1.size(); i++) {
        vector<int> v = fold_tape(t1, i);
        
        if (foundSolution(v, t2))
            return true;
    }

    return false;
}

int main(int argc, const char** argv) {
    int N, M;
    while (scanf("%d", &N) != EOF) {
        vector<int> tape1(N);
        for (int i = 0; i < N; i++)
            scanf("%d", &tape1[i]);

        scanf("%d", &M);
        vector<int> tape2(M);
        for (int i = 0; i < M; i++)
            scanf("%d", &tape2[i]);

        // Se N == M verificamos se as fitas são iguais ou uma é o inverso da outra
        if (N == M) {
            if (equal(tape1, tape2) || reverse(tape1, tape2))
                printf("S\n");
            else
                printf("N\n");
        }

        // Se M == 1 verificamos se a soma da fita1 é igual a fita2
        else if (M == 1) {
            if (sum(tape1) == tape2[0])
                printf("S\n");
            else
                printf("N\n");
        }
        
        // Senão rodamos o algoritmo recursivo
        else {
            if (foundSolution(tape1, tape2))
                printf("S\n");
            else
                printf("N\n");
        }
   }

   return 0;
}