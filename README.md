# 📺 Calculadora de Planes de Streaming

Programa en **C** que calcula la tarifa mensual de planes de streaming según
el paquete elegido y el número de dispositivos.

## ✨ Funciones

- Tres paquetes disponibles:
  - **Standard** — $16 / $26 / $36
  - **VIP** — $19 / $29 / $39
  - **VIP Plus** — $23 / $32 / $44
- Selección de dispositivos: hasta 2, 4 u 8.
- Menú con opción de regresar y repetir la cotización.
- Validación de entradas.

## 🛠️ Compilación y ejecución

Necesitas un compilador de C (gcc, clang o MSVC).

```bash
gcc Streaming.c -o streaming
./streaming
```

En Windows (PowerShell):

```powershell
gcc Streaming.c -o streaming.exe
.\streaming.exe
```

## 📖 Uso

```text
*****Bienvenido*****
Paquete de Streaming
1. Paquete Standard.
2. Paquete VIP.
3. Paquete VIP Plus.
4. Salir
Seleccione un paquete:
```

Luego eliges el número de dispositivos y el programa muestra la tarifa a pagar.

## 📂 Archivos

| Archivo | Descripción |
| --- | --- |
| `Streaming.c` | Código fuente completo. |

## 👤 Autor

**Richard Rodríguez** — [GitHub](https://github.com/Death272004)
