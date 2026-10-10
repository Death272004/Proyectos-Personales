# 🏧 Cajero Bancario

Simulador de cajero bancario escrito en **C++**, con un ejercicio adicional de
interfaz gráfica usando **Qt**.

## ✨ Funciones

- Acceso con PIN de seguridad (reintentos ilimitados).
- Retiro de efectivo con montos preestablecidos ($10, $20, $50, $100).
- Depósito de efectivo con validación (mayor a $0 y máximo $9,999).
- Consulta de saldo en cualquier momento.
- Menú con confirmación antes de cada operación.

## 🛠️ Compilación

### Versión de consola

Necesitas un compilador de C++ (g++, clang++ o MSVC).

```bash
g++ Cajero_Bancario.cpp -o cajero
./cagero
```

En Windows (PowerShell):

```powershell
g++ Cajero_Bancario.cpp -o cajero.exe
.\cajero.exe
```

### Versión gráfica (Qt)

`Mi_Cajero_GUI.cpp` es un ejercicio plantilla para practicar Qt. Sigue los
pasos del archivo y consulta [INSTALACION_QT.md](INSTALACION_QT.md) para
instalar Qt y configurar el proyecto `.pro`.

## 📂 Archivos

| Archivo | Descripción |
| --- | --- |
| `Cajero_Bancario.cpp` | Versión de consola completa. |
| `Mi_Cajero_GUI.cpp` | Ejercicio de interfaz con Qt (plantilla). |
| `Cajero_Bancario.pro` | Archivo de proyecto de Qt Creator. |
| `INSTALACION_QT.md` | Guía para instalar y configurar Qt. |

## 📖 Uso

```text
         BIENVENIDO
Introduce tu contraseña: ****

--------MENU--------
1. Retirar efectivo
2. Consultar saldo
3. Depositar efectivo
4. Salir
```

## 👤 Autor

**Richard Rodríguez** — [GitHub](https://github.com/Death272004)
