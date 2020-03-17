#include <bits/stdc++.h>

int braille2digit(std::string l1, std::string l2) {
    if (l1[0] == '*' && l1[1] == '.' && l2[0] == '.' && l2[1] == '.') return 1;
    if (l1[0] == '*' && l1[1] == '.' && l2[0] == '*' && l2[1] == '.') return 2;
    if (l1[0] == '*' && l1[1] == '*' && l2[0] == '.' && l2[1] == '.') return 3;
    if (l1[0] == '*' && l1[1] == '*' && l2[0] == '.' && l2[1] == '*') return 4;
    if (l1[0] == '*' && l1[1] == '.' && l2[0] == '.' && l2[1] == '*') return 5;
    if (l1[0] == '*' && l1[1] == '*' && l2[0] == '*' && l2[1] == '.') return 6;
    if (l1[0] == '*' && l1[1] == '*' && l2[0] == '*' && l2[1] == '*') return 7;
    if (l1[0] == '*' && l1[1] == '.' && l2[0] == '*' && l2[1] == '*') return 8;
    if (l1[0] == '.' && l1[1] == '*' && l2[0] == '*' && l2[1] == '.') return 9;
    if (l1[0] == '.' && l1[1] == '*' && l2[0] == '*' && l2[1] == '*') return 0;
}

void digit2braille(char d, std::string& l1, std::string& l2) {
    if (d == '1') { l1 += "*."; l2 += ".."; }
    if (d == '2') { l1 += "*."; l2 += "*."; }
    if (d == '3') { l1 += "**"; l2 += ".."; }
    if (d == '4') { l1 += "**"; l2 += ".*"; }
    if (d == '5') { l1 += "*."; l2 += ".*"; }
    if (d == '6') { l1 += "**"; l2 += "*."; }
    if (d == '7') { l1 += "**"; l2 += "**"; }
    if (d == '8') { l1 += "*."; l2 += "**"; }
    if (d == '9') { l1 += ".*"; l2 += "*."; }
    if (d == '0') { l1 += ".*"; l2 += "**"; }
}

void di2br(std::string digits) {
    std::string l1, l2, l3;
    for (int i = 0; i < digits.size(); i++) {
        digit2braille(digits[i], l1, l2);
        l3 += "..";
        if (i < digits.size() - 1) {
            l1 += " ";
            l2 += " ";
            l3 += " ";
        }
    }

    std::cout << l1 << "\n" << l2 << "\n" << l3 << std::endl;
}

int main(int argc, const char** argv) {
    int n;
    std::cin >> n;
    while (n != 0) {
        char c;
        std::cin >> c;

        if (c == 'S') {
            std::string digits;
            std::cin >> digits;

            di2br(digits);
        }
        else if (c == 'B') {
            // Ignorando o \n para não termos erros no getline
            std::cin.ignore(2, '\n');
            std::string braille[3];
            for (int i = 0; i < 3; i++)
                std::getline(std::cin, braille[i]);

            // Braille -> Dígitos
            for (int i = 0; i < braille[0].size(); i += 3)
                std::cout << braille2digit(braille[0].substr(i, 2), braille[1].substr(i, 2));
            std::cout << std::endl;
        }

        std::cin >> n;
    }
    return 0;
}