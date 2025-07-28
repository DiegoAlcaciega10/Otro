#include <iostream>
using namespace std;

class Caja {
private:
    int valores[3];  // Valores de monedas disponibles: 1, 5, 10
public:
    Caja() {
        valores[0] = 10;
        valores[1] = 5;
        valores[2] = 1;
    }

    void mostrarMonedas() {
        cout << "Valores de monedas disponibles: ";
        for (int i = 0; i < 3; i++) {
            cout << valores[i] << " ";
        }
        cout << endl;
    }

    void intercambiar(int monedaIngresada) {
        cout << "Cambio para " << monedaIngresada << ": ";
        for (int i = 0; i < 3; i++) {
            while (monedaIngresada >= valores[i]) {
                cout << valores[i] << " ";
                monedaIngresada -= valores[i];
            }
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Cambio de monedas ===" << endl;
    Caja caja;
    char op = 'n';
    int moneda = 0;

    do {
        caja.mostrarMonedas();

        cout << "\nIngrese la moneda que desea intercambiar: ";
        cin >> moneda;

        caja.intercambiar(moneda);

        cout << "\n¿Desea salir? (s para salir, cualquier otra tecla para continuar): ";
        cin >> op;
        cout << endl;

    } while (op != 's');

    return 0;
}
