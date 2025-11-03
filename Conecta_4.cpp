//
// Created by Chacón González José Diego on 03/11/2025.
//
#include <iostream> // Para entrada/salida en consola
#include <vector> // Para usar vectores dinámicos
#include <locale> // Para usar caracteres UTF-8 (aceptar acentos y ñ)
using namespace std;

// Constantes para el tamaño del tablero

const int FILAS = 6;
const int COLUMNAS = 7;

// Clase que encapsula toda la lógica del juego

class Conecta4 {
private:
    vector<vector<char>> tablero; // Matriz del tablero
    char jugadorActual; // 'X' para jugador 1, 'O' para jugador 2

public:
    // Constructor: inicializa el tablero vacío y asigna el primer turno
    Conecta4() {
        tablero = vector<vector<char>>(FILAS, vector<char>(COLUMNAS, '.'));
        jugadorActual = 'X'; // Jugador 1 comienza
    }
    // Muestra el tablero en consola
    void mostrarTablero() {
        cout << "\n 1 2 3 4 5 6 7\n";
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                cout << " " << tablero[i][j];
            }
            cout << "\n";
        }
    }

    bool columnaLlena(int col) {
        return tablero[0][col] != '.';
    }

    bool colocarFicha(int col) {
        if (col < 0 || col >= COLUMNAS || columnaLlena(col)) return false;
        for (int fila = FILAS - 1; fila >= 0; --fila) {
            if (tablero[fila][col] == '.') {
                tablero[fila][col] = jugadorActual;
                return true;
            }
        }
        return false;
    }

    bool verificarGanador() {
        // Horizontal
        for (int i = 0; i < FILAS; ++i)
            for (int j = 0; j <= COLUMNAS - 4; ++j)
                if (tablero[i][j] == jugadorActual &&
                    tablero[i][j+1] == jugadorActual &&
                    tablero[i][j+2] == jugadorActual &&
                    tablero[i][j+3] == jugadorActual)
                    return true;

        // Vertical
        for (int i = 0; i <= FILAS - 4; ++i)
            for (int j = 0; j < COLUMNAS; ++j)
                if (tablero[i][j] == jugadorActual &&
                    tablero[i+1][j] == jugadorActual &&
                    tablero[i+2][j] == jugadorActual &&
                    tablero[i+3][j] == jugadorActual)
                    return true;

        // Diagonal ↘
        for (int i = 0; i <= FILAS - 4; ++i)
            for (int j = 0; j <= COLUMNAS - 4; ++j)
                if (tablero[i][j] == jugadorActual &&
                    tablero[i+1][j+1] == jugadorActual &&
                    tablero[i+2][j+2] == jugadorActual &&
                    tablero[i+3][j+3] == jugadorActual)
                    return true;

        // Diagonal ↗
        for (int i = 3; i < FILAS; ++i)
            for (int j = 0; j <= COLUMNAS - 4; ++j)
                if (tablero[i][j] == jugadorActual &&
                    tablero[i-1][j+1] == jugadorActual &&
                    tablero[i-2][j+2] == jugadorActual &&
                    tablero[i-3][j+3] == jugadorActual)
                    return true;

        return false;
    }

    bool tableroLleno() {
        for (int j = 0; j < COLUMNAS; ++j)
            if (!columnaLlena(j)) return false;
        return true;
    }

    void cambiarTurno() {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    void jugar() {
        int columna;
        bool jugando = true;

        while (jugando) {
            mostrarTablero();
            cout << "\nTurno del jugador " << (jugadorActual == 'X' ? "1 (X)" : "2 (O)") << ". Elige columna (1-7): ";
            cin >> columna;
            columna -= 1;

            if (!colocarFicha(columna)) {
                cout << "Movimiento inválido. Intenta otra columna.\n";
                continue;
            }

            if (verificarGanador()) {
                mostrarTablero();
                cout << "\n¡Jugador " << (jugadorActual == 'X' ? "1 (X)" : "2 (O)") << " gana!\n";
                jugando = false;
            } else if (tableroLleno()) {
                mostrarTablero();
                cout << "\n¡Empate! El tablero está lleno.\n";
                jugando = false;
            } else {
                cambiarTurno();
            }
        }
    }
};

int main() {
    system("chcp 65001"); // Activa UTF-8 en consola de Windows
    std::locale::global(std::locale("")); // Activa UTF-8 en C++4
    char opcion;
    do {
        Conecta4 juego;
        juego.jugar();
        cout << "\n¿Desean jugar otra partida? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    cout << "Gracias por jugar Conecta 4.\n";
    return 0;
}