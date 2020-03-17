#include <bits/stdc++.h>

int main(int argc, const char** argv) {
    // Tem que usar string pois o número pode ser muito grande!
    std::string numero;
    std::cin >> numero;

    int result = 0;

    // Convertendo cada caractere para inteiro ('0' -> 0, etc)
    // Somamos os caracteres e tiramos o módulo logo em seguida (forma esperta de fazer operações % 3)
    for (char c : numero)
        result += c % '0';

    // % 3 foi o padrão observado!
    std::cout << result % 3 << std::endl;

    return 0;
}