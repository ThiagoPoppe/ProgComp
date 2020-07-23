#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int x, y, r;
} Sensor;

// Struct para o union-find 
typedef struct {
    int rank, parent;
} Group;

// Algoritmo de find do Union-Find usando Path Compression 
int Find(Group groups[], int u) {
    if (groups[u].parent != u)
        groups[u].parent = Find(groups, groups[u].parent);

    return groups[u].parent;
}

// Algoritmo de union do Union-Find usando União por rank
void Union(Group groups[], int u, int v) {
    // Encontrando os grupos de u e v
    int gU = Find(groups, u);
    int gV = Find(groups, v);

    // Se o rank de gU for maior, iremos anexar a árvore de gV na de gU
    if (groups[gU].rank > groups[gV].rank) {
        groups[gV].parent = gU;
    }

    // Faremos o inverso
    else if (groups[gV].rank > groups[gU].rank) {
        groups[gU].parent = gV;
    }

    // Senão, ambas possuem o mesmo rank, podendo anexar qualquer uma das duas árvores
    else {
        groups[gV].parent = gU;
        groups[gU].rank++;
    }
}

// Função que calcula a distância euclidiana de dois pontos
double euclid(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

// Função que retorna se dois sensores se interceptam
bool intercept(Sensor s1, Sensor s2) {
    return euclid(s1.x, s1.y, s2.x, s2.y) <= (s1.r + s2.r);
}

// Função que encontra os limites (largura e altura) de cada grupo
void findLim(vector<Sensor> s, Group groups[], int idx, int& U, int& D, int& L, int& R) {
    for (int i = 0; i < s.size(); i++) {
        // Se idx for "pai" do grupo
        if (Find(groups, i) == idx) {
                int currU = s[i].x - s[i].r; // Ponto superior
                int currD = s[i].x + s[i].r; // Ponto inferior
                int currL = s[i].y - s[i].r; // Ponto esquerdo
                int currR = s[i].y + s[i].r; // Ponto direito

                // Atualizando os limites do grupo
                if (currU < U)
                    U = currU;
                if (currD > D)
                    D = currD;
                if (currL < L)
                    L = currL;
                if (currR > R)
                    R = currR;
        }
    }
}

int main(int argc, const char** argv) {
    int M, N, K;
    cin >> M >> N >> K;

    // Criando um vetor de sensores e grupos
    vector<Sensor> sensors(K);
    Group groups[K];
    for (int i = 0; i < K; i++) {
        groups[i].parent = i;
        groups[i].rank = 0;
    }
        
    // Lendo os sensores
    for (int k = 0; k < K; k++) {
        int x, y, r;
        cin >> x >> y >> r;
        sensors[k] = {x, y, r};
    }

    // Agrupando sensores que se interceptam
    for (int i = 0; i < K; i++) {
        for (int j = i+1; j < K; j++) {
            if (intercept(sensors[i], sensors[j]))
                Union(groups, i, j);
        }
    }

    bool hasPath = true;
    for (int i = 0; i < K && hasPath; i++) {
        // Encontrando os limites do grupo
        int U = M, D = 0, L = N, R = 0;
        findLim(sensors, groups, i, U, D, L, R);

        // Verificando se bloqueia o caminho totalmente
        if (U <= 0 && D >= M)
            hasPath = false;
        else if (L <= 0 && R >= N)
            hasPath = false;
        else if (L <= 0 && U <= 0)
            hasPath = false;
        else if (R >= N && D >= M)
            hasPath = false;
    }

    if (hasPath)
        cout << "S" << endl;
    else
        cout << "N" << endl;

    return 0;
}