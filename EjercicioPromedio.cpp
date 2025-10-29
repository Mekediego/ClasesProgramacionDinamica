#include <iostream>
#include <windows.h> // Solo en Windows
using namespace std;

int main() {
    SetConsoleOutputCP(65001); // Activa UTF-8 en consola de Windows

    const int TAM = 5;
    double numeros[TAM];
    double suma = 0;
    double promedio;
    double minimo;
    double maximo;

    cout << "Calculamos la suma, promedio, mínimo y máximo:" << endl;

    for (int i = 0; i < TAM; i++) {
        cout << "Ingrese el número " << i + 1 << ": ";
        cin >> numeros[i];
        suma += numeros[i];
    }

    minimo = numeros[0];
    maximo = numeros[0];

    for (int i = 0; i < TAM; i++) {
        if (numeros[i] < minimo)
            minimo = numeros[i];
        if (numeros[i] > maximo)
            maximo = numeros[i];
    }

    promedio = suma / TAM;

    cout << "Suma: " << suma << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Mínimo: " << minimo << endl;
    cout << "Máximo: " << maximo << endl;

    return 0;
}