#include <iostream>
using namespace std;

int monto = 700;

// Función para calcular el retiro
int calcular(int cifra)
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

    if (monto >= retiro)
    {
        monto -= retiro;
        cout << "Retiro exitoso de " << retiro << " dolares" << endl;
        cout << "Su nuevo saldo es de: " << monto << " dolares" << endl;
    }
    else
    {
        cout << "Saldo insuficiente. Su saldo actual es de " << monto << " dolares" << endl;
    }
    return monto;
}

// Función principal
int main()
{
    int pin, seleccion, cifra, retiro;
    string usuario, repe, retiro_confirmacion;
    bool bucle = true;
    bool verificacion = true;

    cout << "         BIENVENIDO                  " << endl;
    cout << "Introduce tu nombre de usuario: ";
    cin >> usuario;
    cout << "Introduce tu contraseña: ";
    cin >> pin;

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
            cin >> pin;
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

            cout << "Confirmar retiro? (Si / No): ";
            cin >> retiro_confirmacion;

            if (retiro_confirmacion == "Si" || retiro_confirmacion == "si" || retiro_confirmacion == "SI")
                calcular(cifra);
            else
                cout << "Retiro cancelado" << endl;
            break;

        case 2:
            cout << "Su saldo actual es de " << monto << " dolares" << endl;
            break;
        case 3:
            int deposito;
            cout << "Ingrese la cantidad a depositar: ";
            cin >> deposito;

            if (deposito <= 0)
            {
                cout << "Cantidad inválida. El depósito debe ser mayor que cero." << endl;
                break;
            }
            else if (deposito > 9999)
            {
                cout << "Cantidad inválida. El depósito no puede exceder los 9,999 dolares." << endl;
                break;
            }
            else
            {
                monto += deposito;
                cout << "Depósito exitoso. Su nuevo saldo es de: " << monto << " dólares" << endl;
            }
            break;
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
            if (repe == "NO" || repe == "no" || repe == "No")
            {
                cout << "Gracias por usar nuestros servicios" << endl;
                bucle = false;
            }
        }
    } while (bucle == true);
}
