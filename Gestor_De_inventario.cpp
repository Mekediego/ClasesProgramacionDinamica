//
// Created by Diego Chacón on 30/11/2025.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para sort
#include <iomanip>   // Para formato de salida
#include <locale> // Para usar caracteres UTF-8 (aceptar acentos y ñ)

using namespace std;

// -----------------------------
// Clase Producto
// -----------------------------
class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    Producto(string n, double p, int c) : nombre(n), precio(p), cantidad(c) {}

    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    void mostrar() const {
        cout << left << setw(15) << nombre
             << setw(10) << fixed << setprecision(2) << precio
             << setw(10) << cantidad << endl;
    }
};

// -----------------------------
// Funciones auxiliares
// -----------------------------

// Mostrar todos los productos
void listarProductos(const vector<Producto>& inventario) {
    if (inventario.empty()) {
        cout << "No hay productos registrados.\n";
        return;
    }
    cout << left << setw(15) << "Nombre"
         << setw(10) << "Precio"
         << setw(10) << "Cantidad" << endl;
    cout << "-----------------------------------\n";
    for (const auto& p : inventario) {
        p.mostrar();
    }
}

// Buscar producto por nombre
void buscarProducto(const vector<Producto>& inventario, const string& nombre) {
    bool encontrado = false;
    for (const auto& p : inventario) {
        if (p.getNombre() == nombre) {
            cout << "Producto encontrado:\n";
            p.mostrar();
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se encontró el producto \"" << nombre << "\".\n";
    }
}

// Ordenar por precio
void ordenarPorPrecio(vector<Producto>& inventario) {
    sort(inventario.begin(), inventario.end(),
         [](const Producto& a, const Producto& b) {
             return a.getPrecio() < b.getPrecio();
         });
    cout << "Inventario ordenado por precio.\n";
}

// Ordenar por cantidad
void ordenarPorCantidad(vector<Producto>& inventario) {
    sort(inventario.begin(), inventario.end(),
         [](const Producto& a, const Producto& b) {
             return a.getCantidad() < b.getCantidad();
         });
    cout << "Inventario ordenado por cantidad.\n";
}

// -----------------------------
// Programa principal
// -----------------------------
int main() {
    system("chcp 65001"); // Activa UTF-8 en consola de Windows
    std::locale::global(std::locale("")); // Activa UTF-8 en C++4
    vector<Producto> inventario;
    int opcion;

    do {
        cout << "\n===== Sistema de Inventario =====\n";
        cout << "1. Agregar producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Ordenar por precio\n";
        cout << "5. Ordenar por cantidad\n";
        cout << "0. Salir\n";
        cout << "=================================\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // limpiar buffer

        switch (opcion) {
            case 1: {
                string nombre;
                double precio;
                int cantidad;
                cout << "Nombre del producto: ";
                getline(cin, nombre);
                cout << "Precio: ";
                cin >> precio;
                cout << "Cantidad: ";
                cin >> cantidad;
                inventario.emplace_back(nombre, precio, cantidad);
                cout << "Producto agregado.\n";
                break;
            }
            case 2:
                listarProductos(inventario);
                break;
            case 3: {
                string nombre;
                cout << "Nombre a buscar: ";
                getline(cin, nombre);
                buscarProducto(inventario, nombre);
                break;
            }
            case 4:
                ordenarPorPrecio(inventario);
                break;
            case 5:
                ordenarPorCantidad(inventario);
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}