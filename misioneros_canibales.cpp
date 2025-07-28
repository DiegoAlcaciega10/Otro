
#include <iostream>
using namespace std;

struct Estado {
    int misionerosIzq, canibalesIzq;
    int misionerosDer, canibalesDer;
    bool boteIzquierda;
};

class Nodo {
public:
    Estado estado;
    Nodo* padre;
    Nodo** hijos;
    int numHijos;

    Nodo(Estado e, Nodo* p = nullptr) {
        estado = e;
        padre = p;
        hijos = nullptr;
        numHijos = 0;
    }

    ~Nodo() {
        for (int i = 0; i < numHijos; ++i) {
            delete hijos[i];
        }
        delete[] hijos;
    }
};

const int movimientos[5][2] = {
    {2, 0}, // 2 misioneros
    {0, 2}, // 2 caníbales
    {1, 1}, // 1 misionero y 1 caníbal
    {1, 0}, // 1 misionero
    {0, 1}  // 1 caníbal
};

bool esEstadoValido(int mIzq, int cIzq, int mDer, int cDer) {
    if (mIzq < 0 || cIzq < 0 || mDer < 0 || cDer < 0) return false;
    if ((mIzq > 0 && mIzq < cIzq) || (mDer > 0 && mDer < cDer)) return false;
    return true;
}

bool sonIguales(Estado a, Estado b) {
    return a.misionerosIzq == b.misionerosIzq &&
           a.canibalesIzq == b.canibalesIzq &&
           a.boteIzquierda == b.boteIzquierda;
}

bool estaEnCamino(Nodo* nodo, Estado estado) {
    while (nodo != nullptr) {
        if (sonIguales(nodo->estado, estado)) return true;
        nodo = nodo->padre;
    }
    return false;
}

void imprimirSolucion(Nodo* nodo) {
    if (nodo == nullptr) return;
    imprimirSolucion(nodo->padre);
    Estado e = nodo->estado;
    cout << "Izq: M=" << e.misionerosIzq << " C=" << e.canibalesIzq
         << " | Der: M=" << e.misionerosDer << " C=" << e.canibalesDer
         << " | Bote: " << (e.boteIzquierda ? "Izquierda" : "Derecha") << endl;
}

bool buscarSolucion(Nodo* nodo, int total) {
    Estado e = nodo->estado;
    if (e.misionerosIzq == 0 && e.canibalesIzq == 0) {
        imprimirSolucion(nodo);
        return true;
    }

    Nodo** hijos = new Nodo*[10];
    int contador = 0;

    for (int i = 0; i < 5; ++i) {
        int m = movimientos[i][0];
        int c = movimientos[i][1];
        Estado nuevo = e;

        if (e.boteIzquierda) {
            nuevo.misionerosIzq -= m;
            nuevo.canibalesIzq -= c;
            nuevo.misionerosDer += m;
            nuevo.canibalesDer += c;
        } else {
            nuevo.misionerosIzq += m;
            nuevo.canibalesIzq += c;
            nuevo.misionerosDer -= m;
            nuevo.canibalesDer -= c;
        }
        nuevo.boteIzquierda = !e.boteIzquierda;

        if (esEstadoValido(nuevo.misionerosIzq, nuevo.canibalesIzq, nuevo.misionerosDer, nuevo.canibalesDer) &&
            !estaEnCamino(nodo, nuevo)) {
            hijos[contador] = new Nodo(nuevo, nodo);
            ++contador;
        }
    }

    nodo->hijos = hijos;
    nodo->numHijos = contador;

    for (int i = 0; i < contador; ++i) {
        if (buscarSolucion(nodo->hijos[i], total)) return true;
    }

    return false;
}

int main() {
    int total;
    cout << "Ingrese el numero de misioneros y canibales: ";
    cin >> total;

    Estado inicial = {total, total, 0, 0, true};
    Nodo* raiz = new Nodo(inicial);

    if (!buscarSolucion(raiz, total)) {
        cout << "No hay solucion.\n";
    }

    delete raiz;
    return 0;
}
