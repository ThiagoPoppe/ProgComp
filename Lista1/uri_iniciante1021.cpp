#include <bits/stdc++.h>

int main(int argc, const char** argv) {
    double v;
    int notas[] = {100, 50, 20, 10, 5, 2};
    int moedas[] = {50, 25, 10, 5, 1};
    
    scanf("%lf", &v);

    // Separando notas das moedas
    int n = (int) v;
    int m = (int) (v * 100) % 100;

    // Calculando notas
    printf("NOTAS:\n");
    for (int i = 0; i < 6; i++) {
        printf("%d nota(s) de R$ %d.00\n", n / notas[i], notas[i]);
        n %= notas[i];
    }

    // Calculando moedas
    printf("MOEDAS:\n");
    printf("%d moeda(s) de R$ 1.00\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%d moeda(s) de R$ %.2f\n", m / moedas[i], (float) moedas[i] / 100);
        m %= moedas[i];
    }

    return 0;
}