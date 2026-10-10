# ⚡ Pokémon Finder

Buscador de Pokémon construido con **HTML**, **CSS** y **JavaScript** puro,
que consume la [PokéAPI](https://pokeapi.co).

## ✨ Funciones

- **Búsqueda** por nombre, ID o por **habilidad** (lista los Pokémon que la
  poseen).
- Ficha del Pokémon con sprite, tipos, habilidades y estadísticas base con
  barras de progreso.
- **Cadena de evolución** completa, navegable (haz clic en una evolución para
  buscarla).
- **⚔️ Modo VS:** compara dos Pokémon, sus stats y el multiplicador de daño
  según sus tipos.
- **❤️ Favoritos:** guarda y elimina Pokémon de tu lista, con opción de
  borrar todo.
- **📜 Historial:** registro de tus últimas 50 búsquedas, con borrado
  individual o total.
- Todo se guarda en `localStorage`, sin backend.

## 🛠️ Cómo ejecutarlo

Necesitas un navegador con acceso a internet (para la API).

```bash
# Opción 1: abrir directamente
start Index.html      # Windows
xdg-open Index.html   # Linux
open Index.html       # macOS
```

O con un servidor local (recomendado):

```bash
python -m http.server 8000
# y abre http://localhost:8000
```

## 📂 Archivos

| Archivo | Descripción |
| --- | --- |
| `Index.html` | Estructura de la interfaz. |
| `Color.css` | Estilos, badges de tipos y animaciones. |
| `PokeAPI.js` | Toda la lógica: búsquedas, favoritos, historial y modo VS. |

## 🔗 API utilizada

- [PokéAPI](https://pokeapi.co) — datos de Pokémon, habilidades, tipos y
  cadenas de evolución.
- Sprites de los Pokémon desde el repositorio oficial de sprites.

## 👤 Autor

**Richard Rodríguez** — [GitHub](https://github.com/Death272004)
