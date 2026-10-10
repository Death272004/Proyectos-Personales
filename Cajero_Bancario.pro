QT += core gui widgets

TARGET = CajeroBancario
TEMPLATE = app

CONFIG += c++11

SOURCES += Cajero_Bancario.cpp

# Iconos y recursos
# RESOURCES += recursos.qrc

# Configuración de Windows
win32 {
    RC_ICONS = icono.ico
}
