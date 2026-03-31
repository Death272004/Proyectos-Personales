# Guía de Instalación de Qt para el Cajero Bancario

## Opción 1: Instalador Qt Online (Recomendado)

### Paso 1: Descargar Qt
1. Ve a: https://www.qt.io/download-qt-installer
2. Descarga el **Qt Online Installer** para Windows
3. Ejecuta el instalador descargado

### Paso 2: Instalación
1. Crea una cuenta gratuita de Qt (o inicia sesión)
2. Selecciona **Qt 6.6** o la versión más reciente
3. **IMPORTANTE**: En componentes, selecciona:
   - ✅ MinGW 11.2.0 64-bit (o la versión disponible)
   - ✅ Qt 6.6.x para MinGW
   - ✅ Qt Creator (IDE opcional pero recomendado)
4. Ubicación recomendada: `C:\Qt`
5. Completa la instalación (puede tardar 30-60 minutos)

### Paso 3: Configurar Variables de Entorno
1. Busca "Variables de entorno" en el menú de Windows
2. En "Variables del sistema", edita `Path`
3. Agrega estas rutas (ajusta según tu versión):
   ```
   C:\Qt\6.6.0\mingw_64\bin
   C:\Qt\Tools\mingw1120_64\bin
   ```
4. Haz clic en Aceptar y **reinicia VS Code**

### Paso 4: Verificar Instalación
Abre una terminal nueva y ejecuta:
```powershell
qmake --version
```
Deberías ver la versión de Qt instalada.

---

## Opción 2: Instalación Offline (Más rápida)

### Descargar Qt 6.6 Offline
1. Ve a: https://www.qt.io/offline-installers
2. Descarga **Qt 6.6.x for Windows**
3. Sigue los mismos pasos de instalación

---

## Compilar tu Cajero Bancario

### Método 1: Con qmake (Recomendado)
```powershell
cd "c:\Users\rrpin\Documents\Proyectos personales\Proyectos personales\Cajero\"
qmake Cajero_Bancario.pro
mingw32-make
.\release\CajeroBancario.exe
```

### Método 2: Con Qt Creator
1. Abre Qt Creator
2. File → Open File or Project
3. Selecciona `Cajero_Bancario.pro`
4. Presiona el botón verde de Play ▶️

### Método 3: Compilación directa
```powershell
g++ Cajero_Bancario.cpp -o CajeroBancario -I"C:/Qt/6.6.0/mingw_64/include" -L"C:/Qt/6.6.0/mingw_64/lib" -lQt6Core -lQt6Gui -lQt6Widgets -mwindows
```

---

## Conceptos Qt que aprendiste en el código

### 1. **Widgets** (Componentes visuales)
- `QLabel`: Etiquetas de texto
- `QLineEdit`: Campos de texto editables
- `QPushButton`: Botones
- `QComboBox`: Lista desplegable
- `QSpinBox`: Campo numérico con flechas

### 2. **Layouts** (Organización)
- `QVBoxLayout`: Organiza widgets verticalmente
- `QHBoxLayout`: Organiza widgets horizontalmente

### 3. **Eventos (Signals y Slots)**
```cpp
connect(boton, &QPushButton::clicked, this, &Clase::funcion);
```
- **Signal**: Evento que emite un widget (ej: `clicked`)
- **Slot**: Función que responde al evento

### 4. **Diálogos**
- `QMessageBox`: Mensajes emergentes
- `QDialog`: Ventanas modales personalizadas

### 5. **Estilos CSS**
```cpp
boton->setStyleSheet("background-color: #3498db; color: white;");
```

---

## Solución de Problemas

### Error: "qmake no se reconoce"
- Verifica que agregaste las rutas al Path
- Reinicia la terminal o VS Code

### Error al compilar: "cannot find -lQt6Core"
- Verifica la ruta de las librerías en el comando g++
- Usa qmake en lugar de compilación directa

### Ventana se cierra inmediatamente
- Ejecuta desde la terminal para ver errores
- Verifica que todas las DLLs de Qt estén accesibles

---

## Próximos Pasos para Mejorar

1. **Agregar iconos y recursos**
2. **Persistencia de datos** (guardar saldo en archivo)
3. **Múltiples usuarios** (base de datos)
4. **Validación de formularios**
5. **Temas personalizados** (QSS avanzado)
6. **Animaciones** (QPropertyAnimation)
