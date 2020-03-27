#include <bits/stdc++.h>

using namespace std;

bool areEqual(vector<bool>& v1, vector<bool>& v2) {
    for (int i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;
}

int findSolution(vector<bool>& lamps, vector<vector<int>>& switches) {
    int n = 0;
    vector<bool> initialState = lamps; // guardando o estado inicial

    while (true) {
        for (int i = 0; i < switches.size(); i++) {
            n++;
            for (int l : switches[i])
                lamps[l] = !lamps[l]; // atualizando cada lâmpada

            // Se todas as lâmpadas estiverem apagadas, paramos
            if (find(lamps.begin(), lamps.end(), true) == lamps.end())
                return n;

            // Se voltarmos para o estado inicial, entramos em um loop e podemos parar
            if (areEqual(lamps, initialState) == true && i == switches.size() - 1)
                return -1;
        }
    }
}

int main(int argc, const char** argv) {
    int nSwitches, nLamps, nLampsOn;
    scanf("%d %d", &nSwitches, &nLamps);

    // Criando o vetor de lâmpadas e interruptores
    vector<bool> lamps(nLamps, false);
    vector<vector<int>> switches(nSwitches);

    // Iniciando as lâmpadas ligadas
    scanf("%d", &nLampsOn);
    for (int i = 0; i < nLampsOn; i++) {
        int x; scanf("%d", &x);
        lamps[x-1] = true;
    }

    // Lendo as lâmpadas associadas a cada interruptor
    for (int i = 0; i < nSwitches; i++) {
        int X, Y;
        scanf("%d", &X);
        for (int j = 0; j < X; j++) {
            scanf("%d", &Y);
            switches[i].push_back(Y-1);
        }
    }

    printf("%d\n", findSolution(lamps, switches));

    // printf("Estado inicial: ");
    // for (bool b : lamps)
    //     printf(b ? "on " : "off ");
    // printf("\n\n");

    // for (int i = 0; i < 5; i++) {
    //     printf("Passada %d:\n", i+1);
    //     for (auto s : switches) {
    //         for (int l : s)
    //             lamps[l] = !lamps[l];

    //         for (bool b : lamps)
    //             printf(b ? "on " : "off ");
    //         printf("\n");
    //     }
    //     printf("\n");
    // }

    return 0;
}