# Proyecto de la VERSIÓN GRÁFICA del cajero (interfaz con Qt)
# Para compilar la versión de consola usa en su lugar Cajero_Bancario.pro

QT += core gui widgets

TARGET = CajeroBancarioGUI
TEMPLATE = app

CONFIG += c++11

SOURCES += Mi_Cajero_GUI.cpp

# Iconos y recursos
# RESOURCES += recursos.qrc

# Configuración de Windows
win32 {
    RC_ICONS = icono.ico
}
