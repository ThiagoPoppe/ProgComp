#include <bits/stdc++.h>

typedef long long int lli_t;

// Função que computa o fatorial de um número
lli_t fat(lli_t n) {
    lli_t f = 1;
    for (lli_t i = 2; i <= n; i++)
        f *= i;

    return f;
}

int main(int argc, const char** argv) {
    lli_t n;
    std::set<lli_t> s;
    
    scanf("%lld", &n);

    // Retirando todos os fatores 2 do número
    while (n % 2 == 0) {
        s.insert(2);
        n /= 2;
    }

    for (lli_t i = 3; i <= sqrt(n); i += 2) {
        // Caso onde encontramos um divisor
        while (n % i == 0) {
            s.insert(i);
            n /= i;
        }
    }

    // Se 'n' for maior do que 2 'n' é primo!
    if (n > 2)
        s.insert(n);

    lli_t res = 0;
    for (lli_t i = 2; i <= s.size(); i++)
        res += fat(s.size()) / (fat(i) * fat(s.size() - i));


    printf("%lld\n", res);

    return 0;
}