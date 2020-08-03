#include <bits/stdc++.h>
using namespace std;

struct Team {
    int answers, penalty;
    int FA, TP;
};

// Função que compara dois times
bool scoresComp(const Team &s1, const Team &s2) {
    if (s1.answers != s2.answers)
        return s1.answers > s2.answers;

    // Caso s1.answers == s2.anwsers, desempatamos utilizando a penalidade
    return s1.penalty < s2.penalty;
}

// Função que determina o valor mínimo de EP
int findMin(vector<Team>& scores, int EP) {
    if (EP < 1) // estabelecendo o valor mínimo possível para EP
        return 1;

    // Construindo o novo vetor de pontuações
    vector<Team> newScores = scores;
    for (int i = 0; i < scores.size(); i++)
        newScores[i].penalty -= scores[i].FA;

    for (int i = 0; i < scores.size()-1; i++) {
        if (scores[i].answers == scores[i+1].answers && scores[i].answers != 0) {
            int x1 = scores[i].penalty;
            int x2 = scores[i+1].penalty;

            int y1 = newScores[i].penalty;
            int y2 = newScores[i+1].penalty;

            // O empate não existe mais
            if (x1 == x2 && y1 != y2)
                return EP+1;

            // A ordem não existe mais (ou ocorreu um empate que não existia)
            if (x1 < x2 && y1 >= y2)
                return EP+1;
        }
    }
    
    return findMin(newScores, EP-1);
}

// Função que determina o valor máximo de EP
int findMax(vector<Team>& scores, int EP) {
    bool infinity = true;

    // Construindo o novo vetor de pontuações
    vector<Team> newScores = scores;
    for (int i = 0; i < scores.size(); i++)
        newScores[i].penalty += scores[i].FA;

    for (int i = 0; i < scores.size()-1; i++) {
        if (scores[i].answers == scores[i+1].answers && scores[i].answers != 0) {
            int x1 = scores[i].penalty;
            int x2 = scores[i+1].penalty;

            int y1 = newScores[i].penalty;
            int y2 = newScores[i+1].penalty;

            // O empate não existe mais
            if (x1 == x2 && y1 != y2)
                return EP-1;

            // A ordem não existe mais (ou ocorreu um empate que não existia)
            if (x1 < x2 && y1 >= y2)
                return EP-1;

            // Eles não estão se aproximando (infinito)
            if (infinity) { // Se algum der falso será falso para sempre
                if (abs(x1-x2) <= abs(y1-y2))
                    infinity = true;
                else
                    infinity = false;
            }
        }
    }

    if (infinity)
        return -1;

    return findMax(newScores, EP+1);
}

int main(int argc, const char** argv) {
    int T, P;
    int A, S;
    char s[16];

    scanf("%d %d", &T, &P);
    while (T != 0 && P != 0) {
        vector<Team> scores(T, {0,0,0,0});

        for (int i = 0; i < T; i++) {
            for (int j = 0; j < P; j++) {
                scanf("%s", s);
                
                // Iremos contabilizar apenas se o problema foi resolvido
                if (s[strlen(s)-1] != '-') {
                    scores[i].answers++;
                    sscanf(s, "%d/%d", &A, &S);
                
                    scores[i].FA += A;
                    scores[i].TP += S;
                }
            }

            scores[i].penalty += scores[i].TP + 20 * scores[i].FA;
        }

        // Ordenando as pontuações de acordo com o número de problemas corretos e penalidade
        sort(scores.begin(), scores.end(), scoresComp);
        
        // Teremos um vetor apenas com 0's
        if (scores[0].answers == 0)
            printf("1 *\n");

        // // Apenas um competidor vencedor (onde os demais foram 0)
        // else if (scores[0].answers != scores[1].answers && scores[1].answers == 0)
        //     printf("1 *\n");

        // Senão, procuramos o valor de mínimo e máximo
        else {
            int min = findMin(scores, 19);
            int max = findMax(scores, 21);

            if (max == -1)
                printf("%d *\n", min);
            else
                printf("%d %d\n", min, max);
        }

        scanf("%d %d", &T, &P);
    }

    return 0;
}