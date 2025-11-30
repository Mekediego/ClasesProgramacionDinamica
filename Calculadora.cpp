//
// Created by Diego Chacón on 30/11/2025.
//
#include <iostream>
#include <cmath>     // Para pow y sqrt
using namespace std;

// Función para calcular factorial de un número entero
long long factorial(int n) {
    if (n < 0) return -1; // Factorial no definido para negativos
    long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int opcion;
    do {
        cout << "\n===== Calculadora =====\n";
        cout << "1. Suma\n";
        cout << "2. Resta\n";
        cout << "3. Multiplicación\n";
        cout << "4. División\n";
        cout << "5. Factorial\n";
        cout << "6. Potencia\n";
        cout << "7. Raíz cuadrada\n";
        cout << "0. Salir\n";
        cout << "=======================\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double a, b;
                cout << "Ingresa dos números: ";
                cin >> a >> b;
                cout << "Resultado: " << a + b << endl;
                break;
            }
            case 2: {
                double a, b;
                cout << "Ingresa dos números: ";
                cin >> a >> b;
                cout << "Resultado: " << a - b << endl;
                break;
            }
            case 3: {
                double a, b;
                cout << "Ingresa dos números: ";
                cin >> a >> b;
                cout << "Resultado: " << a * b << endl;
                break;
            }
            case 4: {
                double a, b;
                cout << "Ingresa dos números: ";
                cin >> a >> b;
                if (b == 0) {
                    cout << "Error: división entre cero.\n";
                } else {
                    cout << "Resultado: " << a / b << endl;
                }
                break;
            }
            case 5: {
                int n;
                cout << "Ingresa un número entero: ";
                cin >> n;
                long long res = factorial(n);
                if (res == -1) {
                    cout << "Error: factorial no definido para negativos.\n";
                } else {
                    cout << "Resultado: " << res << endl;
                }
                break;
            }
            case 6: {
                double base, exponente;
                cout << "Ingresa la base y el exponente: ";
                cin >> base >> exponente;
                cout << "Resultado: " << pow(base, exponente) << endl;
                break;
            }
            case 7: {
                double n;
                cout << "Ingresa un número: ";
                cin >> n;
                if (n < 0) {
                    cout << "Error: no se puede calcular raíz cuadrada de negativos.\n";
                } else {
                    cout << "Resultado: " << sqrt(n) << endl;
                }
                break;
            }
            case 0:
                cout << "Saliendo de la calculadora...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}