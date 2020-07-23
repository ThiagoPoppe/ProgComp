#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char** argv) {
    int n;
    scanf("%d", &n);
    
    for (int c = 0; c < n; c++) {
        int numCols=1; // já consideramos a coluna Totals
        char line[32], name[32], val[32]; // strings para lermos cada linha, nome e números respectivamente
        vector<string> names, values;

        // Lendo o cabeçalho
        scanf("%s", line);

        // Corrigindo o cabeçalho + computando o número de colunas que temos
        for (int i = 0; line[i] == 'P'; i+=2)
            printf("P%d ", numCols++);
        printf("Totals\n");

        // Lendo as demais linhas do arquivo e salvando em um vetor
        bool finished = false;
        while (!finished) {
            scanf(" %[A-z]%[0-9]", name, val);
            names.push_back(name);
            values.push_back(val);

            if (strcmp(name, "TP") == 0)
                finished = true;
        }

        
    }

    return 0;
}