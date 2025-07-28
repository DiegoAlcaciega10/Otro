#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Laberinto {
private:
    int** matriz;
    int N;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    bool** visitado;
    int** padreX;
    int** padreY;

    bool dentro(int x, int y) {
        return x >= 0 && y >= 0 && x < N && y < N;
    }

    void generarCaminoSeguro() {
        int x = 0, y = 0;
        matriz[x][y] = 1;
        while (x != N - 1 || y != N - 1) {
            if (x == N - 1)
                y++;
            else if (y == N - 1)
                x++;
            else {
                if (rand() % 2 == 0)
                    x++;
                else
                    y++;
            }
            matriz[x][y] = 1;
        }
    }

    void agregarCaminosAleatorios() {
        int cantidad = (N * N) / 2;
        for (int i = 0; i < cantidad; ++i) {
            int r = rand() % N;
            int c = rand() % N;
            matriz[r][c] = 1;
        }
    }

    bool buscarCaminoVoraz() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                visitado[i][j] = false;
                padreX[i][j] = -1;
                padreY[i][j] = -1;
            }

        int capacidad = N * N;
        int* colaX = new int[capacidad];
        int* colaY = new int[capacidad];
        int frente = 0, fin = 0;

        colaX[fin] = 0;
        colaY[fin] = 0;
        fin++;
        visitado[0][0] = true;

        while (frente < fin) {
            int x = colaX[frente];
            int y = colaY[frente];
            frente++;

            if (x == N - 1 && y == N - 1) {
                delete[] colaX;
                delete[] colaY;
                return true;
            }

            int movs[4][3];
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                int dist = (N - 1 - nx) + (N - 1 - ny);
                movs[i][0] = dist;
                movs[i][1] = dx[i];
                movs[i][2] = dy[i];
            }

            for (int i = 0; i < 3; ++i) {
                for (int j = i + 1; j < 4; ++j) {
                    if (movs[j][0] < movs[i][0]) {
                        for (int k = 0; k < 3; ++k) {
                            int temp = movs[i][k];
                            movs[i][k] = movs[j][k];
                            movs[j][k] = temp;
                        }
                    }
                }
            }

            for (int i = 0; i < 4; ++i) {
                int nx = x + movs[i][1];
                int ny = y + movs[i][2];
                if (dentro(nx, ny) && matriz[nx][ny] == 1 && !visitado[nx][ny]) {
                    colaX[fin] = nx;
                    colaY[fin] = ny;
                    fin++;
                    visitado[nx][ny] = true;
                    padreX[nx][ny] = x;
                    padreY[nx][ny] = y;
                }
            }
        }

        delete[] colaX;
        delete[] colaY;
        return false;
    }

    void marcarCamino() {
        int x = N - 1, y = N - 1;
        while (x != 0 || y != 0) {
            matriz[x][y] = 2;
            int px = padreX[x][y];
            int py = padreY[x][y];
            x = px;
            y = py;
        }
        matriz[0][0] = 2;
    }

public:
    Laberinto(int n) {
        N = n;
        matriz = new int* [N];
        visitado = new bool* [N];
        padreX = new int* [N];
        padreY = new int* [N];
        for (int i = 0; i < N; ++i) {
            matriz[i] = new int[N];
            visitado[i] = new bool[N];
            padreX[i] = new int[N];
            padreY[i] = new int[N];
        }
    }

    ~Laberinto() {
        for (int i = 0; i < N; ++i) {
            delete[] matriz[i];
            delete[] visitado[i];
            delete[] padreX[i];
            delete[] padreY[i];
        }
        delete[] matriz;
        delete[] visitado;
        delete[] padreX;
        delete[] padreY;
    }

    void generar() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                matriz[i][j] = 0;

        generarCaminoSeguro();
        agregarCaminosAleatorios();

        while (!buscarCaminoVoraz()) {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    matriz[i][j] = 0;

            generarCaminoSeguro();
            agregarCaminosAleatorios();
        }

        marcarCamino();
    }

    void imprimir() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matriz[i][j] == 0) cout << "#";
                else if (matriz[i][j] == 1) cout << ".";
                else cout << "*";
            }
            cout << endl;
        }
    }

    void imprimirMovimientos() {
        int x = N - 1;
        int y = N - 1;
        char* pasos = new char[N * N];
        int cont = 0;

        while (!(x == 0 && y == 0)) {
            int px = padreX[x][y];
            int py = padreY[x][y];

            if (px == x - 1 && py == y)
                pasos[cont++] = 'D';
            else if (px == x + 1 && py == y)
                pasos[cont++] = 'U';
            else if (px == x && py == y - 1)
                pasos[cont++] = 'R';
            else if (px == x && py == y + 1)
                pasos[cont++] = 'L';

            x = px;
            y = py;
        }

        cout << "\nMovimientos mínimos para llegar de (0,0) a (" << N-1 << "," << N-1 << "):\n";
        for (int i = cont - 1; i >= 0; i--) {
            switch (pasos[i]) {
                case 'U': cout << "Arriba "; break;
                case 'D': cout << "Abajo "; break;
                case 'L': cout << "Izquierda "; break;
                case 'R': cout << "Derecha "; break;
            }
        }
        cout << endl;
        delete[] pasos;
    }
};

int main() {
    srand(time(0));
    Laberinto lab(10);
    lab.generar();
    lab.imprimir();
    lab.imprimirMovimientos();
    return 0;
}
