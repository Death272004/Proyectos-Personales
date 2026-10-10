// EJERCICIO: Crear tu primer aplicación con Qt
// 
// PASO 1: Incluir las librerías necesarias
// Incluimos <QApplication>, <QWidget>, <QPushButton>, <QLabel> y <QVBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>


// PASO 2: Crear la función main
int main(int argc, char *argv[])
{
    // Crear la aplicación
    QApplication app(argc, argv);

    // Crear una ventana
    QWidget ventana;
    ventana.setWindowTitle("Mi Cajero");
    ventana.resize(300, 150);

    // Crear un botón y una etiqueta que muestra el saldo
    int saldo = 700;
    QLabel *etiquetaSaldo = new QLabel("Saldo: $700");
    QPushButton *botonRetirar = new QPushButton("Retirar $10");

    // Signals y Slots: al hacer clic en el botón se descuenta el monto
    // y se actualiza la etiqueta con el nuevo saldo
    QObject::connect(botonRetirar, &QPushButton::clicked, [&]() {
        saldo -= 10;
        etiquetaSaldo->setText(QString("Saldo: $%1").arg(saldo));
    });

    // Organizar los widgets dentro de la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(etiquetaSaldo);
    layout->addWidget(botonRetirar);
    ventana.setLayout(layout);

    // Mostrar la ventana
    ventana.show();

    // Ejecutar la aplicación
    return app.exec();
}


// 🎯 OBJETIVO DE ESTE EJERCICIO:
// Crear una ventana simple con un botón que al hacer clic muestre un mensaje
// (aquí: un botón que descuenta $10 del saldo y actualiza la etiqueta)

// 📚 CONCEPTOS A APRENDER:
// - QApplication: Maneja la aplicación
// - QWidget: Ventana base
// - QPushButton: Botón clicable
// - QLabel: Etiqueta de texto (muestra el saldo)
// - Signals y Slots: Eventos (connect)
// - Lambdas: la función que se ejecuta al hacer clic
