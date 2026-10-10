/*
 * Proyecto: Calculadora de planes de Streaming
 * Calcula la tarifa a pagar según el paquete elegido (Standard, VIP o
 * VIP Plus) y la cantidad de dispositivos incluidos (2, 4 u 8).
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Prototipo de la función
int evaluar_plan(int plan, int dispositivos);

// Prototipo: int leer_entero(const char *mensaje)
// Propósito: imprime el mensaje y lee un entero validado. Si el usuario escribe
//            algo que no es un número, limpia el búfer de entrada y vuelve a
//            pedir el valor (evita el bucle infinito de scanf sin validar).
int leer_entero(const char *mensaje);

// Prototipo: void limpiar_linea(void)
// Propósito: descarta todo lo que quede pendiente en la línea actual del búfer
//            de entrada para que la siguiente lectura empiece limpia.
void limpiar_linea(void);

// Prototipo: bool cotizar_paquete(const char *nombre_paquete, int plan)
// Propósito: muestra el menú de dispositivos, traduce la opción del menú a la
//            cantidad real de dispositivos (2, 4 u 8), muestra la tarifa y
//            devuelve true si hizo la cotización o false si eligió "Regresar".
bool cotizar_paquete(const char *nombre_paquete, int plan);

// Prototipo: bool es_si(const char *respuesta)
// Propósito: indica si la respuesta del usuario significa "sí"; acepta
//            "Si", "SI", "si", "sí", "SÍ", "Sí", etc. (normaliza a minúsculas).
bool es_si(const char *respuesta);

int main()
{
    bool repetidor = true; // El menú se repite hasta salir o responder "No"

    while (repetidor)
    {
        printf("*****Bienvenido*****\n");
        printf("Paquete de Streaming\n");
        printf("1. Paquete Standard.\n");
        printf("2. Paquete VIP.\n");
        printf("3. Paquete VIP Plus.\n");
        printf("4. Salir\n");

        int seleccion = leer_entero("Seleccione un paquete: ");
        bool preguntar = true; // ¿Se pregunta si desea otra cotización?

        switch (seleccion) {
            case 1:
                preguntar = cotizar_paquete("Standard", 1);
            break;

            case 2:
                preguntar = cotizar_paquete("VIP", 2);
            break;

            case 3:
                preguntar = cotizar_paquete("VIP Plus", 3);
            break;

            case 4:
                printf("Saliendo...\n");
                repetidor = false;
            break;

            default:
                printf("Selección no valida.\n");
            break;
        }

        // Solo se pregunta por otra cotización si se hizo una (o entró inválida);
        // al elegir "Regresar" se vuelve al menú principal sin preguntar.
        if (preguntar && repetidor) {
            char respuesta[16]; // suficiente para "Si", "No", "sí" + '\0'
            printf("Desea realizar otra cotizacion? (Si, No): ");
            if (scanf("%15s", respuesta) != 1) {
                respuesta[0] = '\0'; // Entrada agotada: se responde como "No"
            }
            limpiar_linea();

            repetidor = es_si(respuesta);
        }
    }

    return 0;
}

// Definición de la función: lee un entero validando la entrada del usuario
int leer_entero(const char *mensaje)
{
    int valor;
    int resultado;

    printf("%s", mensaje);
    while ((resultado = scanf("%d", &valor)) != 1) {
        if (resultado == EOF) { // Se acabó la entrada (Ctrl+D o fin de archivo)
            printf("\nEntrada no disponible.\n");
            return 4; // Se interpreta como "Salir"/"Regresar" para terminar
        }
        printf("Entrada no valida. Debe ingresar un numero.\n");
        limpiar_linea(); // Se descarta lo que quedó en el búfer
        printf("%s", mensaje);
    }
    limpiar_linea(); // Se descarta el resto de la línea (si lo hay)

    return valor;
}

// Definición de la función: limpia el búfer hasta el final de la línea
void limpiar_linea(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Se descarta el carácter
    }
}

// Definición de la función: reconoce la respuesta "sí" en sus variantes
bool es_si(const char *respuesta)
{
    char texto[16];
    size_t i;

    // Se copia la respuesta al buffer local (evita desbordes)
    for (i = 0; respuesta[i] != '\0' && i < sizeof(texto) - 1; i++) {
        texto[i] = respuesta[i];
    }
    texto[i] = '\0';

    // Se normaliza a minúsculas: letras A-Z y la "Í" en UTF-8 (0xC3 0x8D -> 0xC3 0xAD)
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = (char)(texto[i] + ('a' - 'A'));
        } else if ((unsigned char)texto[i] == 0xC3 && (unsigned char)texto[i + 1] == 0x8D) {
            texto[i + 1] = (char)0xAD; // Í -> í
        }
    }

    return strcmp(texto, "si") == 0 || strcmp(texto, "sí") == 0;
}

// Definición de la función: menú de dispositivos + cotización de un paquete
bool cotizar_paquete(const char *nombre_paquete, int plan)
{
    int opcion;

    printf("Has seleccionado el Paquete %s.\n", nombre_paquete);

    do {
        printf("Seleccione el numero de dispositivos:\n");
        printf("1. Maximo 2 dispositivos\n");
        printf("2. Maximo 4 dispositivos\n");
        printf("3. Maximo 8 dispositivos\n");
        printf("4. Regresar\n");
        opcion = leer_entero("Opcion: ");

        if (opcion < 1 || opcion > 4) {
            printf("Selección no valida. Intente nuevamente.\n");
        }

    } while (opcion < 1 || opcion > 4);

    if (opcion == 4) {
        printf("Regresando al menu principal...\n");
        return false; // Regresar al menú principal sin preguntar
    }

    // Se traduce la opción del menú a la cantidad real de dispositivos:
    // opción 1 -> 2 dispositivos, opción 2 -> 4, opción 3 -> 8
    int dispositivos = (opcion == 1) ? 2 : (opcion == 2) ? 4 : 8;

    int resultado = evaluar_plan(plan, dispositivos);
    printf("La tarifa a pagar en su Plan %s es de %d dolares.\n", nombre_paquete, resultado);

    return true; // Sí se hizo la cotización
}

// Definición de la función
/*
 * Tabla de precios en dólares (NO cambiar):
 *
 *   Paquete        2 dispositivos   4 dispositivos   8 dispositivos
 *   Standard             16               26               36
 *   VIP                  19               29               39
 *   VIP Plus             23               32               44
 *
 * plan: 1 = Standard, 2 = VIP, 3 = VIP Plus
 * dispositivos: cantidad real de dispositivos (2, 4 u 8)
 */
int evaluar_plan(int plan, int dispositivos) {
    if (plan == 1 && dispositivos == 2) return 16;
    if (plan == 1 && dispositivos == 4) return 26;
    if (plan == 1 && dispositivos == 8) return 36;

    if (plan == 2 && dispositivos == 2) return 19;
    if (plan == 2 && dispositivos == 4) return 29;
    if (plan == 2 && dispositivos == 8) return 39;

    if (plan == 3 && dispositivos == 2) return 23;
    if (plan == 3 && dispositivos == 4) return 32;
    if (plan == 3 && dispositivos == 8) return 44;

    return -1; // combinación inválida
}
