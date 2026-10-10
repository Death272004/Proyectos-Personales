#include <iostream>
#include <string>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// Si el usuario escribió algo que no es un número, evita el bucle infinito de cin
void revisar_entrada()
{
    if (cin.fail())
    {
        if (cin.eof())
        {
            cout << endl << "Entrada finalizada. Adiós" << endl;
            exit(0);
        }
        cin.clear();          // limpia el estado de error
        cin.ignore(1000, '\n'); // descarta lo que quedó en el búfer
        cout << "Entrada inválida, intenta de nuevo." << endl;
    }
}

// Función para leer la contraseña sin mostrarla al escribirla
string leer_contrasena()
{
    string texto = "";
    char c;

    // descartar el salto de línea que quedó de la lectura anterior
    int proximo = 0;
    while ((proximo = cin.peek()) == '\n' || proximo == '\r')
        cin.get();

#ifdef _WIN32
    // Windows: _getch() de <conio.h> no imprime lo que se teclea
    while ((c = _getch()) != '\r' && c != '\n')
    {
        if (c == '\b')
        {
            if (!texto.empty())
            {
                texto.erase(texto.size() - 1);
                cout << "\b \b";
            }
        }
        else
            texto += c;
    }
#else
    // Linux / macOS: con <termios.h> apagamos la visualización de la consola
    struct termios entrada_original, entrada_oculta;
    bool es_terminal = false;

    if (tcgetattr(STDIN_FILENO, &entrada_original) == 0)
    {
        es_terminal = true;
        entrada_oculta = entrada_original;
        entrada_oculta.c_lflag &= ~ECHO; // no mostrar lo que se escribe
        tcsetattr(STDIN_FILENO, TCSANOW, &entrada_oculta);
    }

    while (cin.get(c) && c != '\n' && c != '\r')
        texto += c;

    if (es_terminal)
        tcsetattr(STDIN_FILENO, TCSANOW, &entrada_original); // restaurar la consola

    revisar_entrada(); // por si la entrada llegó al final
#endif

    cout << endl;
    return texto;
}

// Convierte lo escrito en el PIN; devuelve -1 si no es un número
int convertir_pin(const string &texto)
{
    if (texto.empty())
        return -1;

    int valor = 0;
    for (char letra : texto)
    {
        if (letra < '0' || letra > '9')
            return -1;
        valor = valor * 10 + (letra - '0');
    }
    return valor;
}

// Función para calcular el retiro
void calcular(int cifra, int &monto)
{
    int retiro = 0;

    if (cifra == 1)
        retiro = 10;
    else if (cifra == 2)
        retiro = 20;
    else if (cifra == 3)
        retiro = 50;
    else if (cifra == 4)
        retiro = 100;

    if (retiro == 0)
    {
        cout << "Opción no válida" << endl;
        return;
    }

    if (monto >= retiro)
    {
        monto -= retiro;
        cout << "Retiro exitoso de " << retiro << " dólares" << endl;
        cout << "Su nuevo saldo es de: " << monto << " dólares" << endl;
    }
    else
    {
        cout << "Saldo insuficiente. Su saldo actual es de " << monto << " dólares" << endl;
    }
}

// Función principal
int main()
{
    int pin, seleccion, cifra;
    int monto = 700; // saldo inicial (variable local, se pasa a calcular por referencia)
    string usuario, repe, retiro_confirmacion;
    bool bucle = true;
    bool verificacion = true;

    cout << "         BIENVENIDO                  " << endl;
    cout << "Introduce tu nombre de usuario: ";
    cin >> usuario;
    revisar_entrada();

    cout << "Introduce tu contraseña: ";
    pin = convertir_pin(leer_contrasena());

    while (verificacion == true)
    {
        if (pin == 1234)
        {
            cout << "Acceso concedido" << endl;
            bucle = true;
            break;
        }
        else
        {
            cout << "Acceso denegado, intenta de nuevo: ";
            pin = convertir_pin(leer_contrasena());
        }
    }

    do
    {
        cout << "--------MENU--------" << endl;
        cout << "1. Retirar efectivo" << endl;
        cout << "2. Consultar saldo" << endl;
        cout << "3. Depositar efectivo" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> seleccion;
        revisar_entrada();

        switch (seleccion)
        {
        case 1:
            cout << "Cantidad de efectivo que se va a retirar" << endl;
            cout << "1: 10$" << endl;
            cout << "2: 20$" << endl;
            cout << "3: 50$" << endl;
            cout << "4: 100$" << endl;
            cout << "Elige una opcion: ";
            cin >> cifra;
            revisar_entrada();

            cout << "Confirmar retiro? (Si / No): ";
            cin >> retiro_confirmacion;
            revisar_entrada();

            if (retiro_confirmacion == "Si" || retiro_confirmacion == "si" || retiro_confirmacion == "SI")
                calcular(cifra, monto);
            else
                cout << "Retiro cancelado" << endl;
            break;

        case 2:
            cout << "Su saldo actual es de " << monto << " dólares" << endl;
            break;
        case 3:
        {
            int deposito;
            cout << "Ingrese la cantidad a depositar: ";
            cin >> deposito;
            revisar_entrada();

            if (deposito <= 0)
            {
                cout << "Cantidad inválida. El depósito debe ser mayor que cero." << endl;
                break;
            }
            else if (deposito > 9999)
            {
                cout << "Cantidad inválida. El depósito no puede exceder los 9,999 dólares." << endl;
                break;
            }
            else
            {
                monto += deposito;
                cout << "Depósito exitoso. Su nuevo saldo es de: " << monto << " dólares" << endl;
            }
            break;
        }
        case 4:
            cout << "Gracias por usar nuestros servicios" << endl;
            bucle = false;
            break;
        default:
            cout << "Opción no válida" << endl;
        }
        if (bucle == true)
        {
            cout << "Desea continuar (SI/NO)? ";
            cin >> repe;
            revisar_entrada();
            if (repe == "NO" || repe == "no" || repe == "No")
            {
                cout << "Gracias por usar nuestros servicios" << endl;
                bucle = false;
            }
        }
    } while (bucle == true);
}

/*
FIRMA DEL PROGRAMA:
Cajero Bancario (consola) - C++ estándar, sin dependencias extra.
Autor: Death272004
Funciones: iniciar sesión con PIN, retirar, depositar y consultar saldo.
Saldo inicial: 700 dólares. PIN de prueba: 1234.
*/
