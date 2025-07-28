#include <iostream>
using namespace std;

class Estado {
public:
    int mIzq, cIzq;
    int mDer, cDer;
    bool boteIzq;

    Estado(int mi = 0, int ci = 0, int md = 0, int cd = 0, bool b = true)
        : mIzq(mi), cIzq(ci), mDer(md), cDer(cd), boteIzq(b) {}

    bool esValido(int total) {
        if (mIzq < 0 || cIzq < 0 || mDer < 0 || cDer < 0) return false;
        if ((mIzq > 0 && mIzq < cIzq) || (mDer > 0 && mDer < cDer)) return false;
        if (mIzq > total || mDer > total || cIzq > total || cDer > total) return false;
        return true;
    }

    bool esFinal(int total) {
        return mDer == total && cDer == total && !boteIzq;
    }

    void mostrar() {
        cout << "Izq: M=" << mIzq << " C=" << cIzq
             << " | Der: M=" << mDer << " C=" << cDer
             << " | Bote: " << (boteIzq ? "Izquierda" : "Derecha") << endl;
    }

    bool igual(Estado otro) {
        return mIzq == otro.mIzq && cIzq == otro.cIzq &&
               mDer == otro.mDer && cDer == otro.cDer &&
               boteIzq == otro.boteIzq;
    }
};

class Solucionador {
    Estado* pila;
    Estado* visitados;
    int topePila;
    int topeVisitados;
    int capacidad;
    int total;

public:
    Solucionador(int n) {
        capacidad = 1000;
        pila = new Estado[capacidad];
        visitados = new Estado[capacidad];
        topePila = 0;
        topeVisitados = 0;
        total = n;
    }

    ~Solucionador() {
        delete[] pila;
        delete[] visitados;
    }

    void push(Estado e) {
        if (topePila < capacidad) {
            pila[topePila++] = e;
        }
    }

    Estado pop() {
        return pila[--topePila];
    }

    bool vacia() {
        return topePila == 0;
    }

    bool yaVisitado(Estado e) {
        for (int i = 0; i < topeVisitados; i++) {
            if (visitados[i].igual(e)) return true;
        }
        return false;
    }

    void marcarVisitado(Estado e) {
        if (topeVisitados < capacidad) {
            visitados[topeVisitados++] = e;
        }
    }

    void resolver() {
        Estado inicial(total, total, 0, 0, true);
        push(inicial);
        marcarVisitado(inicial);

        while (!vacia()) {
            Estado actual = pop();
            actual.mostrar();

            if (actual.esFinal(total)) {
                cout << "¡Solución encontrada!" << endl;
                return;
            }

            for (int m = 0; m <= 2; ++m) {
                for (int c = 0; c <= 2; ++c) {
                    if (m + c >= 1 && m + c <= 2) {
                        Estado nuevo = actual;
                        if (actual.boteIzq) {
                            nuevo.mIzq -= m;
                            nuevo.cIzq -= c;
                            nuevo.mDer += m;
                            nuevo.cDer += c;
                        } else {
                            nuevo.mIzq += m;
                            nuevo.cIzq += c;
                            nuevo.mDer -= m;
                            nuevo.cDer -= c;
                        }
                        nuevo.boteIzq = !actual.boteIzq;

                        if (nuevo.esValido(total) && !yaVisitado(nuevo)) {
                            push(nuevo);
                            marcarVisitado(nuevo);
                        }
                    }
                }
            }
        }

        cout << "No hay solución." << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese el número de misioneros y caníbales: ";
    cin >> n;
    Solucionador solucion(n);
    solucion.resolver();
    return 0;
}
