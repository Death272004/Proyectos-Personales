# ⚔️ Calculadora de Artefactos Genshin Impact

Simulador y calculadora de artefactos de **5 estrellas** de *Genshin Impact*,
con interfaz gráfica escrita en **Python** con `tkinter`.

## ✨ Funciones

- **Simular a +20:** introduce las estadísticas iniciales exactas de tu
  artefacto y simula las 5 mejoras (nivel 4, 8, 12, 16 y 20).
- **Descubrimiento del 4to stat:** si empiezas con 3 substats, el nivel 4
  revela el cuarto siguiendo las probabilidades oficiales del juego.
- **Ver probabilidades:** ejecuta 10 000 simulaciones de Monte Carlo y te
  dice qué porcentaje de mejoras recibió cada stat, y la probabilidad de que
  tus stats **CRÍTICOS** suban al menos 2 veces.
- **Consejo automático** según el resultado: si vale la pena subirlo, probar
  hasta +8 o usarlo como comida de experiencia.
- Interfaz oscura con tema dorado de artefacto 5★.

## 🛠️ Ejecución

Necesitas Python 3. `tkinter` viene incluido en la instalación estándar.

```bash
python calculadora_artefactos.py
```

> **Nota:** en algunas distribuciones de Linux hay que instalar tkinter por
> separado: `sudo apt install python3-tk`.

## 📖 Uso

1. Elige el **tipo de artefacto** (Flor, Pluma, Reloj, Cáliz o Corona).
2. Selecciona el **stat principal** correspondiente.
3. Ingresa tus **substats de nivel 0** con sus valores exactos (mínimo 3).
4. Pulsa **🎲 Simular a +20** o **📊 Ver Probabilidades**.

## 🧮 Datos del juego

Los valores de substat y sus pesos de probabilidad están basados en artefactos
de 5 estrellas. Se pueden ajustar en los diccionarios `VALORES_SUBSTATS` y
`PESOS_SUBSTATS` al inicio del archivo.

## 📂 Archivos

| Archivo | Descripción |
| --- | --- |
| `calculadora_artefactos.py` | Aplicación completa con interfaz Tkinter. |

## 👤 Autor

**Richard Rodríguez** — [GitHub](https://github.com/Death272004)
