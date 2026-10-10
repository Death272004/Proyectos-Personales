// EJERCICIO RESUELTO: tu primer aplicación con Qt — Cajero Bancario con GUI
// ---------------------------------------------------------------------------
// Esta versión gráfica replica la lógica de la versión de consola
// (ver Cajero_Bancario.cpp): PIN de seguridad, retiros preestablecidos,
// depósitos validados y consulta de saldo.
//
// PASO 1: Incluir las librerías necesarias
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <QString>
#include <QFont>

// Constantes del cajero (mismos valores que la versión de consola)
const int PIN_CORRECTO    = 1234;   // PIN de acceso
const int SALDO_INICIAL   = 700;    // saldo con el que arranca la cuenta
const int LIMITE_DEPOSITO = 9999;   // monto máximo que se puede depositar

// PASO 2: Crear la función main
int main(int argc, char *argv[])
{
    // Crear la aplicación
    QApplication app(argc, argv);

    // Estado de la cuenta. Se usa dentro de las lambdas, así que se declara
    // antes que los conect() para que puedan capturarlo por referencia.
    int saldo = SALDO_INICIAL;

    // =======================================================================
    // VENTANA PRINCIPAL (se crea primero, pero se muestra al validar el PIN)
    // =======================================================================
    QWidget ventanaPrincipal;
    ventanaPrincipal.setWindowTitle("Mi Cajero — Bancario");
    ventanaPrincipal.resize(380, 360);

    // Etiqueta principal y etiqueta del saldo
    QLabel *etiquetaTitulo = new QLabel("Cajero Bancario");
    QLabel *etiquetaSaldo  = new QLabel("Su saldo es de: $700");

    // Hacemos la etiqueta del saldo más grande y en negritas
    QFont fuenteSaldo = etiquetaSaldo->font();
    fuenteSaldo.setPointSize(14);
    fuenteSaldo.setBold(true);
    etiquetaSaldo->setFont(fuenteSaldo);
    etiquetaSaldo->setAlignment(Qt::AlignCenter);

    // Función que refresca la etiqueta del saldo. Como se captura por
    // referencia en cada lambda, basta con llamarla tras cualquier operación.
    auto actualizarSaldo = [&]() {
        etiquetaSaldo->setText(QString("Su saldo es de: $%1").arg(saldo));
    };

    // ----------------------------------------------------------------------
    // Grupo de RETIROS: botones por cada monto preestablecido
    // ----------------------------------------------------------------------
    QGroupBox *grupoRetiros = new QGroupBox("Retirar efectivo");
    QGridLayout *gridRetiros = new QGridLayout;

    // Fábrica de botones de retiro: crea el botón y le conecta su acción.
    // El monto se captura por valor para que cada botón tenga el suyo.
    auto crearBotonRetiro = [&](const QString &texto, int monto) {
        QPushButton *boton = new QPushButton(texto);
        QObject::connect(boton, &QPushButton::clicked, [&, monto]() {

            // Validar que haya saldo suficiente
            if (saldo < monto) {
                QMessageBox::warning(&ventanaPrincipal, "Saldo insuficiente",
                                     QString("No tiene saldo suficiente.\n"
                                             "Su saldo actual es de $%1.").arg(saldo));
                return;
            }

            // Confirmar la operación antes de descontar (como en consola)
            QMessageBox::StandardButton confirmar =
                QMessageBox::question(&ventanaPrincipal, "Confirmar retiro",
                                      QString("¿Confirmar retiro de $%1?").arg(monto),
                                      QMessageBox::Yes | QMessageBox::No);

            if (confirmar != QMessageBox::Yes)
                return;   // el usuario canceló

            saldo -= monto;
            actualizarSaldo();
        });
        return boton;
    };

    gridRetiros->addWidget(crearBotonRetiro("Retirar $10",  10),  0, 0);
    gridRetiros->addWidget(crearBotonRetiro("Retirar $20",  20),  0, 1);
    gridRetiros->addWidget(crearBotonRetiro("Retirar $50",  50),  1, 0);
    gridRetiros->addWidget(crearBotonRetiro("Retirar $100", 100), 1, 1);
    grupoRetiros->setLayout(gridRetiros);

    // ----------------------------------------------------------------------
    // Grupo de DEPÓSITO: campo numérico con rango validado + botón
    // ----------------------------------------------------------------------
    QGroupBox *grupoDeposito = new QGroupBox("Depositar efectivo");
    QHBoxLayout *layoutDeposito = new QHBoxLayout;

    // QSpinBox ya bloquea valores fuera de rango (1 a 9999), igual que la
    // validación de la versión de consola.
    QSpinBox *campoDeposito = new QSpinBox;
    campoDeposito->setRange(1, LIMITE_DEPOSITO);
    campoDeposito->setPrefix("$ ");
    campoDeposito->setValue(100);
    campoDeposito->setAlignment(Qt::AlignCenter);

    QPushButton *botonDepositar = new QPushButton("Depositar");
    QObject::connect(botonDepositar, &QPushButton::clicked, [&]() {
        int monto = campoDeposito->value();
        saldo += monto;
        actualizarSaldo();
        QMessageBox::information(&ventanaPrincipal, "Depósito exitoso",
                                 QString("Depositaste $%1.\n"
                                         "Su nuevo saldo es de $%2.").arg(monto).arg(saldo));
    });

    layoutDeposito->addWidget(campoDeposito);
    layoutDeposito->addWidget(botonDepositar);
    grupoDeposito->setLayout(layoutDeposito);

    // ----------------------------------------------------------------------
    // Botones de CONSULTA y SALIDA
    // ----------------------------------------------------------------------
    QPushButton *botonConsultar = new QPushButton("Consultar saldo");
    QObject::connect(botonConsultar, &QPushButton::clicked, [&]() {
        QMessageBox::information(&ventanaPrincipal, "Consulta de saldo",
                                 QString("Su saldo actual es de $%1.").arg(saldo));
    });

    QPushButton *botonSalir = new QPushButton("Salir");
    QObject::connect(botonSalir, &QPushButton::clicked, &ventanaPrincipal, &QWidget::close);

    // Organizar la ventana principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addWidget(etiquetaSaldo);
    layoutPrincipal->addWidget(grupoRetiros);
    layoutPrincipal->addWidget(grupoDeposito);

    // Los dos últimos botones, lado a lado
    QHBoxLayout *layoutBotonesFinales = new QHBoxLayout;
    layoutBotonesFinales->addWidget(botonConsultar);
    layoutBotonesFinales->addWidget(botonSalir);
    layoutPrincipal->addLayout(layoutBotonesFinales);

    ventanaPrincipal.setLayout(layoutPrincipal);

    // =======================================================================
    // VENTANA DE ACCESO: pide el PIN antes de mostrar el cajero
    // =======================================================================
    QWidget ventanaLogin;
    ventanaLogin.setWindowTitle("Mi Cajero — Acceso");
    ventanaLogin.resize(320, 170);

    QLabel *etiquetaBienvenida = new QLabel("Bienvenido al Cajero Bancario");
    QLabel *etiquetaPin        = new QLabel("Ingrese su PIN:");

    // QLineEdit en modo Password oculta lo que se escribe (no se ve en pantalla)
    QLineEdit *campoPin = new QLineEdit;
    campoPin->setEchoMode(QLineEdit::Password);
    campoPin->setMaxLength(4);
    campoPin->setPlaceholderText("••••");
    campoPin->setAlignment(Qt::AlignCenter);
    // Solo acepta dígitos
    campoPin->setValidator(new QIntValidator(0, 9999, campoPin));

    QPushButton *botonIngresar = new QPushButton("Ingresar");

    // Acción de intentar ingresar. Se deja en una lambda para poder llamarla
    // tanto desde el botón como desde la tecla Enter del campo.
    auto intentarIngreso = [&]() {
        bool esNumero = false;
        int pin = campoPin->text().toInt(&esNumero);   // toInt evita excepciones

        if (esNumero && pin == PIN_CORRECTO) {
            ventanaLogin.hide();          // se cierra el acceso
            ventanaPrincipal.show();      // y se abre el cajero
        } else {
            // PIN incorrecto: se avisa y se deja listo para reintentar
            QMessageBox::warning(&ventanaLogin, "Acceso denegado",
                                 "PIN incorrecto. Inténtelo de nuevo.");
            campoPin->clear();
            campoPin->setFocus();
        }
    };

    QObject::connect(botonIngresar, &QPushButton::clicked, intentarIngreso);
    // Enter en el campo de PIN también intenta ingresar
    QObject::connect(campoPin, &QLineEdit::returnPressed, intentarIngreso);

    QVBoxLayout *layoutLogin = new QVBoxLayout;
    layoutLogin->addWidget(etiquetaBienvenida);
    layoutLogin->addWidget(etiquetaPin);
    layoutLogin->addWidget(campoPin);
    layoutLogin->addWidget(botonIngresar);
    ventanaLogin.setLayout(layoutLogin);

    // Mostrar primero la ventana de acceso y ejecutar la aplicación
    ventanaLogin.show();
    return app.exec();
}


// 🎯 OBJETIVO DE ESTE EJERCICIO (COMPLETADO):
// Crear una ventana que pida un PIN, muestre el saldo y permita retirar y
// depositar dinero, replicando el comportamiento de la versión de consola.
//
// 📚 CONCEPTOS A APRENDER:
// - QApplication: Maneja la aplicación
// - QWidget: Ventana base
// - QPushButton: Botón clicable
// - QLabel: Etiqueta de texto (muestra el saldo)
// - QLineEdit: Campo de texto (aquí, con contraseña oculta)
// - QSpinBox: Campo numérico con flechas y rango validado
// - QGroupBox: Contenedor con título para agrupar widgets
// - QVBoxLayout / QHBoxLayout / QGridLayout: Organización de widgets
// - Signals y Slots: Eventos (connect)
// - Lambdas: la función que se ejecuta al hacer clic
// - QMessageBox: Mensajes de aviso, confirmación e información

// ▶️ CÓMO COMPILARLO:
//   qmake Mi_Cajero_GUI.pro
//   mingw32-make          (o make en Linux/macOS)
//
// PIN de prueba: 1234
