#include <iostream>
#include <string>
#include <vector>
#include <windows.h> // Solo para Windows
using namespace std;

struct Alumno {
    string nombre;
    int edad;
    float promedio;
};

int main() {
    // Activar UTF-8 en consola de Windows
    SetConsoleOutputCP(65001);

    int cantidad;
    cout << "¿Cuántos alumnos deseas registrar? ";
    cin >> cantidad;
    cin.ignore(); // Limpiar el buffer para getline

    // Crear un vector dinámico de alumnos
    vector<Alumno> grupo(cantidad);

    // Captura de datos
    for (int i = 0; i < cantidad; i++) {
        cout << "\nAlumno " << i + 1 << endl;

        cout << "Nombre: ";
        getline(cin, grupo[i].nombre);

        cout << "Edad: ";
        cin >> grupo[i].edad;

        cout << "Promedio: ";
        cin >> grupo[i].promedio;

        cin.ignore(); // Limpiar buffer para el siguiente nombre
    }

    // Mostrar resultados
    cout << "\nListado de alumnos registrados:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "Nombre: " << grupo[i].nombre << endl;
        cout << "Edad: " << grupo[i].edad << endl;
        cout << "Promedio: " << grupo[i].promedio << endl;
        cout << "-----------------------------" << endl;
    }

    return 0;
}