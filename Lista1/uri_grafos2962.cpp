#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

// Struct para guardar posição e raio do sensor
typedef struct {
    int x, y, r;
} Sensor;

// Debug
void printGallery(vector<vector<int>>& g) {
    cout << "Gallery size: (" << g.size() << ", " << g[0].size() << ")" << endl;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[0].size(); j++)
            cout << g[i][j] << " ";
        cout << endl;
    }
}

// Debug
void printSensors(vector<Sensor>& s) {
    cout << "Sensors size: " << s.size() << endl;
    for (int i = 0; i < s.size(); i++)
        cout << s[i].x << " " << s[i].y << " " << s[i].r << endl;
}

// Função que calcula o quadrado da distância euclidiana
double dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

// Função que escolhe a célula com menor distância até o alvo (otimização)
void nextCell(vector<vector<int>>& gallery, vector<int>& xv, vector<int>& yv, int& x, int& y) {
    double minDist = INT_MAX;
    int delIndex = -1;
    int M = gallery.size() - 1;
    int N = gallery[0].size() - 1;

    for (int i = 0; i < xv.size(); i++) {
        if (dist(xv[i], yv[i], M, N) < minDist) {
            x = xv[i], y = yv[i];
            delIndex = i;

            minDist = dist(xv[i], yv[i], M, N);
        }
    }

    // Removendo célula da lista de células
    xv.erase(xv.begin()+delIndex);
    yv.erase(yv.begin()+delIndex);
}

int main(int argc, const char** argv) {
    int M, N, K;
    cin >> M >> N >> K;

    // Criando galeria e sensores
    vector<vector<int>> gallery(M+1, vector<int>(N+1, 1)); // 0 -> inválido, 1 -> não explorado, 2 -> explorado
    vector<Sensor> sensors(K);

    // Lendo os sensores
    for (int k = 0; k < K; k++) {
        int x, y, r;
        cin >> x >> y >> r;
        sensors[k] = {x, y, r};
    }

    // Demarcando pontos inválidos
    int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1}; // direções em x (usaremos as 4 primeiras por enquanto)
    int dy[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; // direções em y (usaremos as 4 primeiras por enquanto)
    for (Sensor s : sensors) {
        for (int i = 0; i < 4; i++) {
            int x = s.x, y = s.y;
            for (int r = 0; r <= s.r; r++) {
                if (x < 0 || x > M || y < 0 || y > N) // ponto fora da área
                    break;

                gallery[x][y] = 0;
                x += dx[i]; y += dy[i];
            }
        }
    }

    printGallery(gallery);

    // vector<int> xv; xv.push_back(0);
    // vector<int> yv; yv.push_back(0);
    // bool found = false;

    // while (!found && !xv.empty() && !yv.empty()) {
    //     // printGallery(gallery);
    //     int x, y;
    //     nextCell(gallery, xv, yv, x, y);

    //     // Explorando os vizinhos de (x, y)
    //     for (int i = 0; i < 8; i++) {
    //         int nx = x + dx[i], ny = y + dy[i]; // nx e ny são os vizinhos na direção (dx[i],dy[i])
    //         if (nx < 0 || nx > M || ny < 0 || ny > N) // vizinho inválido
    //             continue;

    //         // Encontramos o alvo
    //         if (nx == M && ny == N) {
    //             found = true;
    //             break;
    //         }

    //         // Se for uma célula sem sensor e não explorada iremos adicionar à fila
    //         if (gallery[nx][ny] == 1) {
    //             xv.push_back(nx);
    //             yv.push_back(ny);
    //         }
    //     }

    //     // cout << "visitando célula (" << x << ", " << y << ")" << endl;
    //     gallery[x][y] = 2; // marcando célula atual como explorada
    // }

    // if (found)
    //     cout << "S" << endl;
    // else
    //     cout << "N" << endl;

    return 0;
}