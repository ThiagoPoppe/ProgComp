#include <bits/stdc++.h>

// Função que verifica se o char 'a' está a esquerda de um char 'b' dada uma string 's' com tamanho N
bool esquerda(char a, char b, char s[53], int N) {
    int pA = -1, pB = -1;
    for (int i = 0; i < N; i++) {
        if (a == s[i])
            pA = i;
        else if (b == s[i])
            pB = i;
        else if (pA != -1 && pB != -1)
            break;
    }

    return pA < pB ? true : false;
}

// Função que insere o char 'c' na árvore
void insere_arv(char arv[53], char c, char s[53], int pos, int N) {
    int esq = 2*pos + 1;
    int dir = 2*pos + 2;

    if (esquerda(c, arv[pos], s, N)) {
        if (arv[esq] == '-')
            arv[esq] = c;
        else
            insere_arv(arv, c, s, esq, N);
    }
    else {
        if (arv[dir] == '-')
            arv[dir] = c;
        else
            insere_arv(arv, c, s, dir, N);
    }
}

// Função que realiza o percurso posfixo
void posfixo(char arv[53], int i) {
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if (arv[esq] != '-')
        posfixo(arv, esq);
    if (arv[dir] != '-')
        posfixo(arv, dir);

    printf("%c", arv[i]);
}

int main(int argc, const char** argv) {
    int C, N;
    char arv[53];
    char s1[53], s2[53];

    scanf("%d", &C);
    
    for (int i = 0; i < C; i++) {
        // Lendo os percursos transversais
        scanf("%d", &N);
        scanf("%s %s", s1, s2);

        // Inicializando a árvore
        for (int i = 0; i < 53; i++)
            arv[i] = '-';

        // Construindo a árvore
        arv[0] = s1[0];
        for (int j = 1; j < N; j++) {
            insere_arv(arv, s1[j], s2, 0, N);
        }

        // Imprimindo o percurso posfixo
        posfixo(arv, 0);
        printf("\n");
    }

    return 0;
}