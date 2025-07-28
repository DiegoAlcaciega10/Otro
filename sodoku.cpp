#include <iostream>
using namespace std;

const int N = 9;

bool esValido(int sudoku[N][N], int fila, int col, int num) {
    // Verifica si el número ya está en la fila o columna
    for (int i = 0; i < N; i++) {
        if (sudoku[fila][i] == num || sudoku[i][col] == num)
            return false;
    }

    // Verifica si el número ya está en el subcuadro 3x3
    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (sudoku[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool resolverSudoku(int sudoku[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        for (int col = 0; col < N; col++) {
            if (sudoku[fila][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (esValido(sudoku, fila, col, num)) {
                        sudoku[fila][col] = num;
                        if (resolverSudoku(sudoku)) return true;
                        sudoku[fila][col] = 0; // backtrack
                    }
                }
                return false;
            }
        }
    }
    return true; // completado
}

void imprimirSudoku(int sudoku[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        for (int col = 0; col < N; col++) {
            cout << sudoku[fila][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    int sudoku[N][N] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},
        
        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    cout << "Sudoku original:\n";
    imprimirSudoku(sudoku);

    if (resolverSudoku(sudoku)) {
        cout << "\nSudoku resuelto:\n";
        imprimirSudoku(sudoku);
    } else {
        cout << "\nNo se pudo resolver el Sudoku.\n";
    }

    return 0;
}
