#include <bits/stdc++.h>

/*
    Anotações:
    1) As tábuas possuem a mesma largura mas comprimentos diferentes!
    2) O piso do salão é retangular.
    3) Tábuas justapostas, sem sobreposição, cobrindo assim todo o piso do salão.
    4) Todas as tábuas devem estar no mesmo sentido, e se uma tábua é muito pequena, podemos
       usar no máximo outra tábua para completar o piso.
    5) Objetivo: saber se é possível forrar o piso sem serrar as tábuas e se sim, qual o menor número!
*/

bool fitsVertical(int m, int l)   { return m % l == 0; }
bool fitsHorizontal(int n, int l) { return n % l == 0; }

int min(int a, int b) { return a < b ? a : b; }

int buildSol(std::vector<int>& x, int& val, int& low, int& hi, int& s, int& numBoards) {
    // Eliminando tábuas maiores do que o limite
    while (x[hi] > val)
        hi--;

    // Colocando tábuas com comprimento igual ao limite
    while (x[hi] == val && s > 0) {
        s--;
        hi--;
        numBoards++;
    }

    // Casos onde devemos usar duas tábuas
    while (low < hi && s > 0) {
        if (x[low] + x[hi] == val) {
            s--;
            hi--; low++;
            numBoards += 2;
        }

        else if (x[low] + x[hi] < val)
            low++;

        else if (x[low] + x[hi] > val)
            hi--;
    }
}

int checkSolHorizontal(std::vector<int>& x, int m, int n, int l) {
    if (!fitsHorizontal(n, l))
        return -1;
    
    int low = 0, hi = x.size() - 1;
    int numBoards = 0, s = n / l;

    buildSol(x, m, low, hi, s, numBoards);

    if (s > 0)
        return -1;
    
    return numBoards;
}

int checkSolVertical(std::vector<int>& x, int m, int n, int l) {
    if (!fitsVertical(m, l))
        return -1;

    int low = 0, hi = x.size() - 1;
    int numBoards = 0, s = m / l;

    buildSol(x, n, low, hi, s, numBoards);

    if (s > 0)
        return -1;
    
    return numBoards;
}

int main(int argc, const char** argv) {
    int m, n; // m -> dimensão em x ("largura"), n -> dimensão em y ("altura")
    int l, k;

    scanf("%d %d", &m, &n);

    while (m != 0 && n != 0) {
        scanf("%d", &l);
        scanf("%d",&k);

        // Declarando nosso vetor com k posições
        std::vector<int> x(k);

        // Lendo os comprimentos e convertendo para centímetros
        for (int i = 0; i < k; i++) {
            scanf("%d", &x[i]);
            x[i] *= 100;
        }

        // Ordenando nosso vetor de comprimentos
        std::sort(x.begin(), x.end());

        m *= 100; n *= 100;
        int s1 = checkSolHorizontal(x, m, n, l);
        int s2 = checkSolVertical(x, m, n, l);

        if (s1 == -1 && s2 == -1)
            printf("impossivel\n");
        else if (s1 != -1 && s2 == -1)
            printf("%d\n", s1);
        else if (s1 == -1 && s2 != -1)
            printf("%d\n", s2);
        else
            printf("%d\n", min(s1, s2));
        
        scanf("%d %d", &m, &n);
    }

    return 0;
}