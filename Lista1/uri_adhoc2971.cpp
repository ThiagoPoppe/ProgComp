#include <bits/stdc++.h>
#define MAX 13

// Função para converter as cartas em valores númericos
int conversion(char c) {
    switch (c) {
        case 'A': return 0;
        case '2': return 1;
        case '3': return 2;
        case '4': return 3;
        case '5': return 4;
        case '6': return 5;
        case '7': return 6;
        case '8': return 7;
        case '9': return 8;
        case 'D': return 9;
        case 'Q': return 10;
        case 'J': return 11;
        case 'K': return 12;
    }
}

// Função que verifica se uma "mão" é vencedora
bool hasWon(std::vector<int>& cards) {
    if (cards.size() != 4)
        return false;

    for (int i = 0; i < cards.size() - 1; i++)
        if (cards[i] != cards[i+1])
            return false;

    return true;
}

// Função que conta a frequência de cada carta retornando a carta correta da jogada
int play(std::vector<int>& cards) {
    int hash[MAX] = {0}; // criando um hash que guardará a frequência de cada carta

    // Contando a frequência
    for (int c : cards)
        hash[c]++;

    // Encontrando a carta com menor aparição (em caso de empate, escolheremos a de menor valor)
    int cardToRemove = -1;
    int min = INT_MAX;
    for (int i = 0; i < MAX; i++) {
        if (hash[i] > 0 && hash[i] < min) {
            min = hash[i];
            cardToRemove = i;
        }
    }

    return cardToRemove;
}

// Função que remove uma carta do jogador
void removeCard(std::vector<int>& cards, int cardToRemove) {
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i] == cardToRemove) {
            cards.erase(cards.begin() + i);
            break;
        }
    }
}

int main(int argc, const char** argv) {
    int N, K;
    int winner = -1;
    std::cin >> N >> K;

    std::vector<std::vector<int>> cards(N+1);
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 4; j++) {
            char c;
            std::cin >> c;
            cards[i].push_back(conversion(c));
        }
    }

    // 0 -> não possui curinga, 1 -> possui o curinga e não pode jogá-lo, 2 -> possui o curinga e deve jogá-lo
    std::vector<int> joker(N+1, 0);
    joker[K] = 1;

    // Verificando se temos algum vencedor mesmo antes do jogo começar
    for (int i = 1; i <= N; i++) {
        if (joker[i] == 0 && hasWon(cards[i])) {
            winner = i;
            break;
        }
    }

    // Podemos iniciar o jogo normalmente
    if (winner == -1) {
        while (true) {
            int next = (K % N) + 1;

            // O jogador K irá jogar normalmente
            if (joker[K] == 0) {
                int c = play(cards[K]);

                removeCard(cards[K], c);
                cards[next].push_back(c);
            }

            // O jogador K irá jogar normalmente, porém na próxima ele deverá jogar o curinga
            else if (joker[K] == 1) {
                int c = play(cards[K]);
                joker[K] = 2;

                removeCard(cards[K], c);
                cards[next].push_back(c);
            }

            // O jogador K deve se livrar do curinga, passando para o próximo
            else if (joker[K] == 2) {
                joker[K] = 0;
                joker[next] = 1;
            }

            // Temos um jogador vitorioso (temporariamente)
            if (joker[K] == 0 && hasWon(cards[K]))
                break;

            K = next;
        }

        // Verificando se temos outro jogador vitorioso
        for (int i = 1; i <= N; i++) {
            if (joker[i] == 0 && hasWon(cards[i])) {
                winner = i;
                break;
            }
        }
    }

    // Exibindo o jogador vencedor
    std::cout << winner << std::endl;
   
    return 0;
}