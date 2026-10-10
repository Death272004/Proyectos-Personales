import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import random

# Valores posibles al subir un substat en un artefacto de 5 estrellas.
VALORES_SUBSTATS = {
    "Vida Plana": [200, 239, 269, 299],
    "Ataque Plano": [14, 16, 18, 19],
    "Defensa Plana": [16, 19, 21, 23],
    "Vida %": [4.1, 4.7, 5.3, 5.8],
    "Ataque %": [4.1, 4.7, 5.3, 5.8],
    "Defensa %": [5.1, 5.8, 6.6, 7.3],
    "Maestria Elemental": [16, 19, 21, 23],
    "Recarga de Energia %": [4.5, 5.2, 5.8, 6.5],
    "Probabilidad CRIT %": [2.7, 3.1, 3.5, 3.9],
    "Daño CRIT %": [5.4, 6.2, 7.0, 7.8]
}

# Pesos de probabilidad oficial (aproximados) al revelar una nueva estadística en nivel 4
PESOS_SUBSTATS = {
    "Vida Plana": 6, "Ataque Plano": 6, "Defensa Plana": 6,
    "Vida %": 4, "Ataque %": 4, "Defensa %": 4,
    "Maestria Elemental": 4, "Recarga de Energia %": 4,
    "Probabilidad CRIT %": 3, "Daño CRIT %": 3
}

# Tipos de artefactos según Genshin Impact
TIPOS_ARTEFACTO = [
    "Flor de la Vida", 
    "Pluma de la Muerte", 
    "Arenas de Eón (Reloj)", 
    "Cáliz de Enotema", 
    "Tiara de Logos (Corona)"
]

# Las posibles estadísticas principales dependiendo del tipo de artefacto
MAIN_STATS_POR_TIPO = {
    "Flor de la Vida": ["Vida Plana"],
    "Pluma de la Muerte": ["Ataque Plano"],
    "Arenas de Eón (Reloj)": ["Ataque %", "Vida %", "Defensa %", "Maestria Elemental", "Recarga de Energia %"],
    "Cáliz de Enotema": [
        "Bono de Daño Pyro %", "Bono de Daño Hydro %", "Bono de Daño Cryo %", 
        "Bono de Daño Electro %", "Bono de Daño Anemo %", "Bono de Daño Geo %", 
        "Bono de Daño Dendro %", "Bono de Daño Físico %", 
        "Ataque %", "Vida %", "Defensa %", "Maestria Elemental"
    ],
    "Tiara de Logos (Corona)": ["Probabilidad CRIT %", "Daño CRIT %", "Bono de Curación %", "Ataque %", "Vida %", "Defensa %", "Maestria Elemental"]
}

class AplicacionGenshin:
    def __init__(self, root):
        self.root = root
        self.root.title("Simulador y Calculadora de Artefactos Genshin Impact")
        self.root.geometry("700x750")
        
        # Colores principales (Tema Artefacto 5 Estrellas - Genshin Impact)
        self.bg_color = "#1E202B"         # Fondo oscuro
        self.fg_color = "#ECE5CE"         # Texto crema 
        self.gold_color = "#DE9E48"       # Dorado 5 estrellas
        self.frame_bg = "#272A35"         # Fondo de los paneles
        self.btn_bg = "#E6D6BA"           # Fondo de botones
        self.btn_fg = "#2A2A35"           # Texto de botones
        
        self.root.configure(bg=self.bg_color, padx=20, pady=20)
        
        # Configurar Estilos (Ttk)
        style = ttk.Style()
        # Usar un tema más versátil de base si está disponible
        if 'clam' in style.theme_names():
            style.theme_use('clam')
            
        style.configure('TFrame', background=self.bg_color)
        style.configure('TLabelframe', background=self.frame_bg, bordercolor=self.gold_color)
        style.configure('TLabelframe.Label', background=self.frame_bg, foreground=self.gold_color, font=("Segoe UI", 10, "bold"))
        style.configure('TLabel', background=self.frame_bg, foreground=self.fg_color, font=("Segoe UI", 10))
        
        style.configure('Main.TLabel', background=self.bg_color, foreground=self.fg_color, font=("Segoe UI", 9))
        
        style.configure('TCombobox', fieldbackground=self.frame_bg, background=self.btn_bg, foreground="black")
        style.configure('TButton', background=self.gold_color, foreground=self.btn_fg, font=("Segoe UI", 10, "bold"), padding=5)
        style.map('TButton', background=[('active', '#F3C56D')])

        # Título
        tk.Label(root, text="✦ Simulador de Artefactos 5★ ✦", font=("Segoe UI", 18, "bold"), bg=self.bg_color, fg=self.gold_color).pack(pady=5)
        ttk.Label(root, text="Elige el tipo de artefacto, el stat principal y las estadísticas iniciales exactas.", style='Main.TLabel').pack(pady=5)
        
        # Frame de Información Principal
        frame_base = ttk.LabelFrame(root, text=" Información Base del Artefacto ", padding=15)
        frame_base.pack(fill="x", pady=5)
        
        ttk.Label(frame_base, text="Tipo de Artefacto:").grid(row=0, column=0, padx=5, pady=5, sticky="e")
        self.cb_tipo = ttk.Combobox(frame_base, values=TIPOS_ARTEFACTO, state="readonly", width=30)
        self.cb_tipo.grid(row=0, column=1, padx=5, pady=5)
        self.cb_tipo.bind("<<ComboboxSelected>>", self.actualizar_main_stats)
        
        ttk.Label(frame_base, text="Stat Principal:").grid(row=1, column=0, padx=5, pady=5, sticky="e")
        self.cb_main_stat = ttk.Combobox(frame_base, state="readonly", width=30)
        self.cb_main_stat.grid(row=1, column=1, padx=5, pady=5)
        self.cb_main_stat.bind("<<ComboboxSelected>>", self.actualizar_substats)

        # Frame para la entrada de datos de Substats
        self.frame_inputs = ttk.LabelFrame(root, text=" Substats Nivel 0 (Ingresa los números exactos) ", padding=15)
        self.frame_inputs.pack(fill="x", pady=10)

        self.comboboxes = []
        self.entradas_valores = []

        ttk.Label(self.frame_inputs, text="Tipo de Substat").grid(row=0, column=1, padx=5, pady=2)
        ttk.Label(self.frame_inputs, text="Valor Numérico (Ej: 3.9)").grid(row=0, column=2, padx=5, pady=2)

        for i in range(4):
            ttk.Label(self.frame_inputs, text=f"Substat {i+1}:").grid(row=i+1, column=0, padx=5, pady=5, sticky="e")
            cb = ttk.Combobox(self.frame_inputs, state="readonly", width=25)
            cb.grid(row=i+1, column=1, padx=5, pady=5)
            self.comboboxes.append(cb)

            entry = ttk.Entry(self.frame_inputs, width=15)
            entry.grid(row=i+1, column=2, padx=5, pady=5)
            self.entradas_valores.append(entry)

        # Configuración por defecto / inicialización al arrancar el programa
        self.cb_tipo.set(TIPOS_ARTEFACTO[0]) # Por defecto es Flor
        self.actualizar_main_stats()

        # Botones de Acción
        frame_btns = tk.Frame(root, bg=self.bg_color)
        frame_btns.pack(pady=15)

        ttk.Button(frame_btns, text="🎲 Simular a +20", command=self.simular_a_20, width=20).pack(side=tk.LEFT, padx=10)
        ttk.Button(frame_btns, text="📊 Ver Probabilidades", command=self.calcular_probabilidades, width=20).pack(side=tk.LEFT, padx=10)

        # Consola de texto para mostrar los resultados (Con estilo oscuro)
        self.consola = scrolledtext.ScrolledText(root, width=75, height=18, font=("Consolas", 10), 
                                                 bg="#151720", fg=self.gold_color, insertbackground="white",
                                                 highlightthickness=1, highlightbackground=self.gold_color)
        self.consola.pack(fill="both", expand=True, pady=10)

    def actualizar_main_stats(self, event=None):
        """Actualiza la lista de Stats principales al cambiar de artefacto (Ej. de Flor a Reloj)."""
        tipo_seleccionado = self.cb_tipo.get()
        stats_posibles = MAIN_STATS_POR_TIPO[tipo_seleccionado]
        
        self.cb_main_stat.config(values=stats_posibles)
        # Seleccionamos automáticamente la primera opción
        self.cb_main_stat.set(stats_posibles[0])
        
        # Como cambió el stat principal, hay que refrescar los substats permitidos
        self.actualizar_substats()

    def actualizar_substats(self, event=None):
        """Actualiza la lista de substats evitando que selecciones tu Stat Principal."""
        main_stat = self.cb_main_stat.get()
        
        # Todos los substats disponibles menos el que es nuestro Main Stat actual
        opciones_stats = ["(Ninguno)"] + [stat for stat in VALORES_SUBSTATS.keys() if stat != main_stat]
        
        for cb in self.comboboxes:
            current_val = cb.get()
            cb.config(values=opciones_stats)
            # Si el substat que ya estaba escogido ahora choca con el nuevo Main Stat, lo reseteamos
            if current_val == main_stat or current_val not in opciones_stats:
                cb.set("(Ninguno)")

    def print_consola(self, texto):
        self.consola.insert(tk.END, texto + "\n")
        self.consola.see(tk.END)

    def obtener_substats_usuario(self):
        """Retorna un diccionario leyendo los substats y los valores numéricos ingresados por el usuario"""
        substats = {}
        for i, cb in enumerate(self.comboboxes):
            stat = cb.get()
            if stat != "(Ninguno)" and stat not in substats:
                valor_str = self.entradas_valores[i].get()
                if not valor_str.strip():
                    messagebox.showerror("Error", f"Has seleccionado '{stat}' pero dejaste su casilla de valor vacía.")
                    return None
                try:
                    # Convertimos a flotante el valor que el jugador escribió
                    valor = float(valor_str)
                    substats[stat] = valor
                except ValueError:
                    messagebox.showerror("Error", f"El valor '{valor_str}' no es válido. Ingresa un número (usa punto para decimales).")
                    return None
        return substats

    def agregar_cuarto_stat(self, substats_actuales):
        """Agrega un 4to stat basándose en las probabilidades oficiales, evitando repeticiones y al Main Stat"""
        main_stat = self.cb_main_stat.get()
        # Filtramos para no añadir estadísticas que ya tenemos, ni el Stat Principal del artefacto
        opciones_validas = [stat for stat in PESOS_SUBSTATS.keys() if stat not in substats_actuales and stat != main_stat]
        pesos = [PESOS_SUBSTATS[stat] for stat in opciones_validas]
        
        nuevo_stat = random.choices(opciones_validas, weights=pesos, k=1)[0]
        valor_base = random.choice(VALORES_SUBSTATS[nuevo_stat])
        substats_actuales[nuevo_stat] = valor_base
        return nuevo_stat, valor_base

    def simular_a_20(self):
        self.consola.delete('1.0', tk.END) # Limpiar consola
        substats = self.obtener_substats_usuario()
        
        if substats is None:
            return  # Si hay error (casilla vacía o no numérica), detenemos la simulación
            
        tipo = self.cb_tipo.get()
        main_stat = self.cb_main_stat.get()

        if len(substats) < 3:
            messagebox.showwarning("Faltan datos", "Debes ingresar al menos 3 estadísticas (substats) y sus valores.")
            return

        self.print_consola(f"🌟 --- {tipo.upper()} NUEVO (+0) --- 🌟")
        self.print_consola(f"👑 Stat Principal: {main_stat}")
        self.print_consola("-----------------------------------------")
        for stat, valor in substats.items():
            self.print_consola(f"🔹 {stat}: {valor:.1f}" if "%" in stat else f"🔹 {stat}: {int(valor)}")
        self.print_consola("\nIniciando mejoras...")

        nivel = 0
        while nivel < 20:
            nivel += 4
            self.print_consola(f"\n🔼 Mejorando a nivel +{nivel}...")

            # Si estamos en nivel 4 y solo hay 3 stats, descubrimos el cuarto
            if nivel == 4 and len(substats) == 3:
                nuevo_stat, valor_base = self.agregar_cuarto_stat(substats)
                self.print_consola(f"✨ ¡Se descubrió un nuevo stat: {nuevo_stat} ({valor_base})!")
            else:
                # Subir un stat existente
                stat_elegido = random.choice(list(substats.keys()))
                valor_subida = random.choice(VALORES_SUBSTATS[stat_elegido])
                substats[stat_elegido] += valor_subida
                self.print_consola(f"⭐ ¡{stat_elegido} subió en {valor_subida}!")

        self.print_consola("\n✅ --- ARTEFACTO FINAL NIVEL +20 --- ✅")
        for stat, valor in substats.items():
            self.print_consola(f"🔹 {stat}: {valor:.1f}" if "%" in stat else f"🔹 {stat}: {int(valor)}")

    def calcular_probabilidades(self):
        self.consola.delete('1.0', tk.END)
        substats_iniciales = self.obtener_substats_usuario()
        
        if substats_iniciales is None:
            return  # Si hay un error de validación, detenemos aquí.
            
        main_stat = self.cb_main_stat.get()

        if len(substats_iniciales) < 3:
            messagebox.showwarning("Faltan datos", "Debes ingresar al menos 3 estadísticas (substats).")
            return

        simulaciones = 10000
        resultados = {stat: 0 for stat in VALORES_SUBSTATS.keys()}
        
        self.print_consola(f"Simulando {simulaciones} veces el camino de tu artefacto...")

        exitos_al_menos_dos_crit = 0

        for _ in range(simulaciones):
            # Clonamos solo las llaves para ser más rápidos
            stats_temp = list(substats_iniciales.keys())
            mejoras_crit = 0

            # 5 mejoras posibles
            for tirada in range(1, 6): # Nivel 4, 8, 12, 16, 20
                if tirada == 1 and len(stats_temp) == 3:
                    # Simular la revelación del nivel 4 (No puede ser el Main Stat)
                    opciones_validas = [s for s in PESOS_SUBSTATS.keys() if s not in stats_temp and s != main_stat]
                    pesos = [PESOS_SUBSTATS[s] for s in opciones_validas]
                    nuevo_stat = random.choices(opciones_validas, weights=pesos, k=1)[0]
                    stats_temp.append(nuevo_stat)
                else:
                    stat_mejorado = random.choice(stats_temp)
                    resultados[stat_mejorado] += 1
                    
                    if "CRIT" in stat_mejorado:
                        mejoras_crit += 1
            
            if mejoras_crit >= 2:
                exitos_al_menos_dos_crit += 1

        self.print_consola("\n📊 PROBABILIDADES ESTADÍSTICAS OBTENIDAS:")
        # Probabilidades promediadas sobre las 5 tiradas
        tiradas_totales = simulaciones * 5
        for stat, veces in resultados.items():
            if veces > 0:
                prob = (veces / tiradas_totales) * 100
                self.print_consola(f"- El stat '{stat}' atrajo el {prob:.1f}% de todas las mejoras.")

        prob_buen_artefacto = (exitos_al_menos_dos_crit / simulaciones) * 100
        self.print_consola(f"\n🎯 Tienes un {prob_buen_artefacto:.1f}% de probabilidad de que los stats CRÍTICOS")
        self.print_consola("   suban de nivel AL MENOS 2 VECES en total.")

        if prob_buen_artefacto > 40:
            self.print_consola("➡️ CONSEJO: ¡Es un excelente artefacto, mejóralo sin dudar!")
        elif prob_buen_artefacto > 20:
            self.print_consola("➡️ CONSEJO: Súbelo a +4 o +8. Si no sube lo que quieres, bótalo.")
        else:
            self.print_consola("➡️ CONSEJO: Riesgo alto. Úsalo como experiencia (food).")

if __name__ == "__main__":
    root = tk.Tk()
    app = AplicacionGenshin(root)
    root.mainloop()
