#include <bits/stdc++.h>

using namespace std;

// Função para calcular o maior tempo gasto para comer os sacos.
// Nesse caso, basta termos o cenário de apenas 1 comedor
int getUpperBound(vector<int>& bags) {
    int sum = 0;
    for (int i = 0; i < bags.size(); i++)
        sum += bags[i];
    
    return sum;
}

// Função para calcular o menor tempo gasto para comer os sacos.
// Esse valor será ditado pelo maior valor do nosso vetor, pois basta
// alocarmos um comedor para esse saco e os demais nos restantes de forma que
// os tempos gastos sejam menor ou igual ao tempo gasto pelo maior
int getLowerBound(vector<int>& bags) {
    int max = INT_MIN;
    for (int i = 0; i < bags.size(); i++)
        if (bags[i] > max)
            max = bags[i];

    return max;
}

// Função que determina o número de comedores mínimo dado um número máximo de pipocas,
// (posteriormente será o "mid") e o valor de T
int getNumEaters(vector<int>& bags, int maxPopcorn) {
    int total = 0;
    int n = 1; // começaremos com 1 comedor sempre

    for (int i = 0; i < bags.size(); i++) {
        total += bags[i];

        // Caso atingimos um valor maior do que o máximo, precisaremos de
        // outro comedor
        if (total > maxPopcorn) {
            total = bags[i];
            n++;
        }
    }

    return n;
}

// Função que determina a solução ótima do problema de comedores de pipoca.
// Nela usaremos uma solução baseada em busca binária, onde iremos procurar
// a solução ótima dentre as possíveis soluções do problema.
// -> A grande chave dessa solução é que:
//    - Caso encontremos mais comedores necessários do que o que temos, a solução
//      ótima deve estar na metade superior do nosso range, pois, com mais comedores
//      o valor de lower bound poderá subir, visto que pode ser que não mais o maior
//      valor do nosso vetor seja uma solução ótima válida. E vice-versa caso tenhamos
//      um número menor, em outras palavras, a solução está mais próxima do lower bound.
int optSolution(vector<int>& bags, int C) {
    // Determinando os valores mínimo e máximo do nosso range da busca
    int lo = getLowerBound(bags);
    int hi = getUpperBound(bags);

    // Loop da busca binária
    while (lo < hi) {
        int mid = (lo + hi) / 2; // cálculo para achar o "tempo médio"
        int nEaters = getNumEaters(bags, mid); // achando o número de comedores para mid

        // Já que precisamos de mais comedores do que o necessário, a solução
        // se encontra na metade superior do nosso range, aumentando nosso lower bound
        if (nEaters > C)
            lo = mid + 1;

        // Basta aplicarmos a lógica inversa do if anterior
        else
            hi = mid;
    }

    // Solução ótima do nosso problema
    return lo;
}

int main(int argc, const char** argv) {
    int N, C, T;
    cin >> N >> C >> T;

    // Inicializando os sacos de pipoca
    vector<int> bags(N);
    for (int i = 0; i < N; i++)
        cin >> bags[i];

    // Achando a solução ótima considerando uma unidade de tempo igual a 1,
    // depois tirando o teto da divisão desse valor por T ("unidade de tempo" da questão)
    // creio que isso fez com que a unidade de tempo do problema passasse a ser T
    int opt = optSolution(bags, C);
    cout << (int) ceil((double) opt / T) << endl;

    return 0;
}