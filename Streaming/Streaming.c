#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Prototipo de la función
int evaluar_plan(int plan, int dispositivos);

int main()
{
    int seleccion, cantidad_D;
    bool repetidor = true; // El bucle debe iniciar en true

    while (repetidor)
    {
        repetidor = false; // Se reinicia en false al inicio
        printf("*****Bienvenido*****\n");
        printf("Paquete de Streaming\n");
        printf("1. Paquete Standard.\n");
        printf("2. Paquete VIP.\n");
        printf("3. Paquete VIP Plus.\n");
        printf("4. Salir\n");
        printf("Seleccione un paquete: ");
        scanf("%d", &seleccion);

        switch (seleccion) {
            case 1:
                printf("Has seleccionado el Paquete Standard.\n");

                do {
                    printf("Seleccione el numero de dispositivos:\n");
                    printf("1. Maximo 2 dispositivos\n");
                    printf("2. Maximo 4 dispositivos\n");
                    printf("3. Maximo 8 dispositivos\n");
                    printf("4. Regresar\n");
                    scanf("%d", &cantidad_D);

                    if(cantidad_D < 1 || cantidad_D > 4) {
                        printf("Selección no valida. Intente nuevamente.\n");
                    }

                } while (cantidad_D < 1 || cantidad_D > 4);

                if (cantidad_D != 4) {
                    int resultado = evaluar_plan(1, cantidad_D);
                    printf("La tarifa a pagar en su Plan Standard es de %d dolares.\n", resultado);
                } else {
                    printf("Regresando al menu principal...\n");
                    repetidor = true;
                }
            break;

            case 2:
                printf("Has seleccionado el Paquete VIP.\n");
                do {
                    printf("Seleccione el numero de dispositivos:\n");
                    printf("1. Maximo 2 dispositivos\n");
                    printf("2. Maximo 4 dispositivos\n");
                    printf("3. Maximo 8 dispositivos\n");
                    printf("4. Regresar\n");
                    scanf("%d", &cantidad_D);

                    if(cantidad_D < 1 || cantidad_D > 4) {
                        printf("Selección no valida. Intente nuevamente.\n");
                    }

                } while (cantidad_D < 1 || cantidad_D > 4);

                if (cantidad_D != 4) {
                    int resultado = evaluar_plan(2, cantidad_D);
                    printf("La tarifa a pagar en su Plan VIP es de %d dolares.\n", resultado);
                } else {
                    printf("Regresando al menu principal...\n");
                    repetidor = true;
                }
            break;

            case 3:
                printf("Has seleccionado el Paquete VIP Plus.\n");
                do {
                    printf("Seleccione el numero de dispositivos:\n");
                    printf("1. Maximo 2 dispositivos\n");
                    printf("2. Maximo 4 dispositivos\n");
                    printf("3. Maximo 8 dispositivos\n");
                    printf("4. Regresar\n");
                    scanf("%d", &cantidad_D);

                    if(cantidad_D < 1 || cantidad_D > 4) {
                        printf("Selección no valida. Intente nuevamente.\n");
                    }

                } while (cantidad_D < 1 || cantidad_D > 4);

                if (cantidad_D != 4) {
                    int resultado = evaluar_plan(3, cantidad_D);
                    printf("La tarifa a pagar en su Plan VIP Plus es de %d dolares.\n", resultado);
                } else {
                    printf("Regresando al menu principal...\n");
                    repetidor = true;
                }
            break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Selección no valida.\n");
                repetidor = true;
            break;
        }

        if (seleccion != 4) {
            char respuesta[3]; // suficiente para "Si", "No" + '\0'
            printf("Desea realizar otra cotizacion? (Si, No): ");
            scanf("%2s", respuesta);  // %2s evita overflow

            if (strcmp(respuesta, "Si") == 0 || strcmp(respuesta, "SI") == 0 || strcmp(respuesta, "si") == 0) {
                repetidor = true;
            } else {
                repetidor = false;
            }
        }
    }

    return 0;
}

// Definición de la función
int evaluar_plan(int plan, int dispositivos) {
    if (plan == 1 && dispositivos == 1) return 16;
    if (plan == 1 && dispositivos == 2) return 26;
    if (plan == 1 && dispositivos == 3) return 36;

    if (plan == 2 && dispositivos == 1) return 19;
    if (plan == 2 && dispositivos == 2) return 29;
    if (plan == 2 && dispositivos == 3) return 39;

    if (plan == 3 && dispositivos == 1) return 23;
    if (plan == 3 && dispositivos == 2) return 32;
    if (plan == 3 && dispositivos == 3) return 44;

    return -1; // combinación inválida
}
