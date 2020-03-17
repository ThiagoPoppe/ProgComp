#include <bits/stdc++.h>

int main(int argc, const char** argv) {
    int n;
    std::string s;

    std::cin >> n;
    while (n != 0) {
        std::map<char, int> keys;
        int i = 0; // "Ponteiro" para o início da frase
        int maxLength = 0;

        // Leitura da linha ignorando o \n deixado pelo std::cin
        std::cin.ignore(2, '\n');
        std::getline(std::cin, s);

        for (int j = 0; j < s.size(); j++) {
            keys[s[j]]++;
            
            while (keys.size() > n) {
                keys[s[i++]]--;
                if (keys[s[i-1]] == 0) {
                    keys.erase(s[i-1]);
                    break;
                }
            }

            int currentLength = (j - i) + 1;
            if (currentLength > maxLength)
                maxLength = currentLength;
        }

        std::cout << maxLength << std::endl;
        std::cin >> n;
    }
    return 0;
}