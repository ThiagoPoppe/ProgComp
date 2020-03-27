#include <bits/stdc++.h>

typedef std::pair<int, int> myPair;

using namespace std;

void print_vector(std::vector<int>& v) {
    for (int i : v)
        printf("%d ", i);
    printf("\n");
}

void print_vector(std::vector<bool>& v) {
    for (bool b : v)
        printf(b ? "1 " : "0 ");
    printf("\n");
}

int main(int argc, const char** argv) {
    int N, C, T;
    int time = 0, done = 0;

    scanf("%d %d %d", &N, &C, &T);

    // Criando variáveis
    vector<int> bags(N); // vetor para os sacos de pipoca
    vector<int> compLocation; // vetor para o local dos competidores
    vector<bool> hasComp(N, false); // vetor para indicar se há um competidor
    vector<myPair> v(N); // vetor auxiliar para acharmos os C maiores números do vetor bags

    // Lendo os sacos de pipoca
    for (int i = 0; i < N; i++) {
        int P;
        scanf("%d", &P);

        bags[i] = P;
        v[i] = make_pair(P, i);
    }

    // Computando os C maiores números e pegando seus índices
    std::sort(v.begin(), v.end());
    for (int i = N - 1; i > N - 1 - C; i--) {
        int index = v[i].second;

        hasComp[index] = true;
        compLocation.push_back(index);
    }

    // // Debug
    printf("N=%d, C=%d, T=%d\n", N, C, T);
    printf("bags:    "); print_vector(bags);
    printf("hasComp: "); print_vector(hasComp);

    // Loop para contarmos o tempo gasto
    while (done < N) {
        // Loop para cada competidor
        for (int& loc : compLocation) {
            int rest = bags[loc] - T; // comer pipoca

            // Não terminamos o saco, assim, finalizando nossa rodada
            if (rest > 0) {
                 bags[loc] = rest;
            }

            // Terminamos um saco
            else if (rest == 0) {
                bags[loc] = rest;
                done++;
            }

            // Podemos passar para outro saco!
            // else {
            // }
        }

        time++;
    }

    printf("%d\n", time);

    return 0;
}