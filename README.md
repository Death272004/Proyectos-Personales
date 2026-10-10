# 🏧 Cajero Bancario

Simulador de cajero bancario escrito en **C++**, en dos versiones: una de
**consola** y otra **gráfica con Qt**, ambas con la misma lógica.

## ✨ Funciones

- Acceso con PIN de seguridad (reintentos ilimitados).
- Retiro de efectivo con montos preestablecidos ($10, $20, $50, $100).
- Depósito de efectivo con validación (mayor a $0 y máximo $9,999).
- Consulta de saldo en cualquier momento.
- Confirmación antes de cada retiro.

## 🛠️ Compilación

### Versión de consola

Necesitas un compilador de C++ (g++, clang++ o MSVC).

```bash
g++ Cajero_Bancario.cpp -o cajero
./cajero
```

En Windows (PowerShell):

```powershell
g++ Cajero_Bancario.cpp -o cajero.exe
.\cajero.exe
```

### Versión gráfica (Qt)

`Mi_Cajero_GUI.cpp` es una aplicación completa con dos ventanas: acceso con
PIN oculto y cajero con botones de retiro, depósito y consulta de saldo.

Consulta [INSTALACION_QT.md](INSTALACION_QT.md) para instalar Qt.

```bash
# Con qmake (recomendado)
qmake Mi_Cajero_GUI.pro
mingw32-make      # o make en Linux/macOS
./CajeroBancarioGUI
```

Compilación directa sin qmake:

```bash
g++ Mi_Cajero_GUI.cpp -o cajero_gui \
    $(pkg-config --cflags --libs Qt6Widgets) -fPIC
./cajero_gui
```

> **PIN de prueba:** `1234`

## 📂 Archivos

| Archivo | Descripción |
| --- | --- |
| `Cajero_Bancario.cpp` | Versión de consola completa. |
| `Mi_Cajero_GUI.cpp` | Versión gráfica completa con Qt. |
| `Cajero_Bancario.pro` | Proyecto Qt para la versión de consola. |
| `Mi_Cajero_GUI.pro` | Proyecto Qt para la versión gráfica. |
| `INSTALACION_QT.md` | Guía para instalar y configurar Qt. |

## 📖 Uso

La versión de consola presenta este menú:

```text
         BIENVENIDO
Introduce tu contraseña: ****

--------MENU--------
1. Retirar efectivo
2. Consultar saldo
3. Depositar efectivo
4. Salir
```

La versión gráfica muestra el saldo, cuatro botones de retiro, un campo de
depósito con rango validado (1–9,999) y botones de consulta y salida.

## 👤 Autor

**Richard Rodríguez** — [GitHub](https://github.com/Death272004)
