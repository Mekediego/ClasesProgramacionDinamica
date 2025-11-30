//
// Created by meked on 30/11/2025.
//
#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>    // Para limpiar el buffer de entrada
#include <iomanip>   // Formato de salida (decimales)

/*
  Sistema de Cajero Automático
  - Operaciones: Consulta de saldo, Depósito, Retiro, Transferencia
  - Clases: Account (modelo), ATM (aplicación/menú)
  - Validaciones: cuenta existente, montos > 0, fondos suficientes, entradas numéricas seguras
*/

// ------------------------
// Clase Account (Cuenta)
// ------------------------
class Account {
private:
    std::string number;   // Número de cuenta (ID único)
    std::string owner;    // Nombre del titular
    double balance;       // Saldo disponible

public:
    // Constructor
    Account(const std::string& number, const std::string& owner, double initialBalance = 0.0)
        : number(number), owner(owner), balance(initialBalance) {}

    // Getters
    const std::string& getNumber() const { return number; }
    const std::string& getOwner()  const { return owner; }
    double getBalance()            const { return balance; }

    // Depósito: suma al saldo si el monto es válido
    bool deposit(double amount) {
        if (amount <= 0.0) return false;
        balance += amount;
        return true;
    }

    // Retiro: resta del saldo si el monto es válido y hay fondos
    bool withdraw(double amount) {
        if (amount <= 0.0) return false;
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    // Transferencia: intenta retirar de esta cuenta y depositar en otra
    bool transferTo(Account& destination, double amount) {
        if (&destination == this) return false; // no transferir a sí misma
        if (amount <= 0.0) return false;
        if (amount > balance) return false;
        balance -= amount;
        destination.balance += amount;
        return true;
    }
};

// ------------------------
// Utilidades de entrada
// ------------------------

// Limpia el estado de cin tras una entrada inválida y descarta el resto de la línea
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Lee un double de forma segura con mensaje y retorna el valor
double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        } else {
            std::cout << "Entrada inválida. Por favor, ingresa un número.\n";
            clearInput();
        }
    }
}

// Lee una cadena (sin espacios recortados) para IDs o nombres
std::string readString(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

// ------------------------
// Clase ATM (Aplicación)
// ------------------------
class ATM {
private:
    // Mapa de cuentas por número de cuenta
    std::unordered_map<std::string, Account> accounts;

    // Obtiene puntero a cuenta si existe, nullptr si no
    Account* getAccount(const std::string& number) {
        auto it = accounts.find(number);
        if (it == accounts.end()) return nullptr;
        return &it->second;
    }

    // Muestra el menú principal
    void printMenu() const {
        std::cout << "\n===== Cajero Automático =====\n";
        std::cout << "1. Consultar saldo\n";
        std::cout << "2. Depositar\n";
        std::cout << "3. Retirar\n";
        std::cout << "4. Transferir\n";
        std::cout << "5. Crear cuenta\n";
        std::cout << "6. Listar cuentas\n";
        std::cout << "0. Salir\n";
        std::cout << "=============================\n";
    }

    // Consulta de saldo mostrando formato fijo con 2 decimales
    void checkBalance() {
        std::string number = readString("Número de cuenta: ");
        Account* acc = getAccount(number);
        if (!acc) {
            std::cout << "La cuenta no existe.\n";
            return;
        }
        std::cout << "Titular: " << acc->getOwner() << "\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Saldo: $" << acc->getBalance() << "\n";
    }

    // Depósito con validación de monto
    void deposit() {
        std::string number = readString("Número de cuenta: ");
        Account* acc = getAccount(number);
        if (!acc) {
            std::cout << "La cuenta no existe.\n";
            return;
        }
        double amount = readDouble("Monto a depositar: ");
        if (!acc->deposit(amount)) {
            std::cout << "Monto inválido. Debe ser mayor a 0.\n";
            return;
        }
        std::cout << "Depósito exitoso. Nuevo saldo: $" << std::fixed << std::setprecision(2) << acc->getBalance() << "\n";
    }

    // Retiro con validación de fondos
    void withdraw() {
        std::string number = readString("Número de cuenta: ");
        Account* acc = getAccount(number);
        if (!acc) {
            std::cout << "La cuenta no existe.\n";
            return;
        }
        double amount = readDouble("Monto a retirar: ");
        if (!acc->withdraw(amount)) {
            std::cout << "Operación inválida. Verifica que el monto sea > 0 y que tengas fondos suficientes.\n";
            return;
        }
        std::cout << "Retiro exitoso. Nuevo saldo: $" << std::fixed << std::setprecision(2) << acc->getBalance() << "\n";
    }

    // Transferencia entre cuentas
    void transfer() {
        std::string from = readString("Cuenta origen: ");
        Account* accFrom = getAccount(from);
        if (!accFrom) {
            std::cout << "La cuenta origen no existe.\n";
            return;
        }

        std::string to = readString("Cuenta destino: ");
        Account* accTo = getAccount(to);
        if (!accTo) {
            std::cout << "La cuenta destino no existe.\n";
            return;
        }

        double amount = readDouble("Monto a transferir: ");
        if (!accFrom->transferTo(*accTo, amount)) {
            std::cout << "Transferencia inválida. Verifica que el monto sea > 0, que no sea la misma cuenta y que haya fondos suficientes.\n";
            return;
        }
        std::cout << "Transferencia exitosa.\n";
        std::cout << "Saldo origen: $" << std::fixed << std::setprecision(2) << accFrom->getBalance() << "\n";
        std::cout << "Saldo destino: $" << std::fixed << std::setprecision(2) << accTo->getBalance() << "\n";
    }

    // Crear una nueva cuenta
    void createAccount() {
        std::string number = readString("Nuevo número de cuenta (ID): ");
        if (getAccount(number)) {
            std::cout << "Ya existe una cuenta con ese número.\n";
            return;
        }
        std::string owner = readString("Nombre del titular: ");
        double initial = readDouble("Saldo inicial (puede ser 0): ");
        if (initial < 0.0) {
            std::cout << "El saldo inicial no puede ser negativo.\n";
            return;
        }

        accounts.emplace(number, Account(number, owner, initial));
        std::cout << "Cuenta creada exitosamente.\n";
    }

    // Listar cuentas registradas (útil para pruebas)
    void listAccounts() const {
        if (accounts.empty()) {
            std::cout << "No hay cuentas registradas.\n";
            return;
        }
        std::cout << "\n--- Cuentas ---\n";
        std::cout << std::left << std::setw(15) << "Cuenta" << std::setw(20) << "Titular" << std::setw(12) << "Saldo" << "\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << std::fixed << std::setprecision(2);
        for (const auto& kv : accounts) {
            const Account& acc = kv.second;
            std::cout << std::left << std::setw(15) << acc.getNumber()
                      << std::setw(20) << acc.getOwner()
                      << std::setw(12) << acc.getBalance() << "\n";
        }
    }

public:
    // Constructor: opcionalmente puedes precargar cuentas de prueba
    ATM() {
        // Cuentas de ejemplo para probar rápido
        accounts.emplace("1001", Account("1001", "Ana Perez", 1500.00));
        accounts.emplace("1002", Account("1002", "Diego Lopez", 800.00));
        accounts.emplace("1003", Account("1003", "Maria Ruiz", 0.00));
    }

    // Bucle principal del menú
    void run() {
        while (true) {
            printMenu();
            int option;
            std::cout << "Selecciona una opción: ";
            if (!(std::cin >> option)) {
                std::cout << "Entrada inválida. Debes ingresar un número.\n";
                clearInput();
                continue;
            }
            clearInput();

            switch (option) {
                case 1: checkBalance();    break;
                case 2: deposit();         break;
                case 3: withdraw();        break;
                case 4: transfer();        break;
                case 5: createAccount();   break;
                case 6: listAccounts();    break;
                case 0:
                    std::cout << "Gracias por usar el cajero. ¡Hasta luego!\n";
                    return;
                default:
                    std::cout << "Opción no válida.\n";
            }
        }
    }
};

// ------------------------
// Función principal
// ------------------------
int main() {
    ATM app;
    app.run();
    return 0;
}