import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack; // <-- Librería para usar pila 

public class PIla {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Queue<Integer> cola = new LinkedList<>();
        Stack<Integer> pila = new Stack<Integer>();
        // variables de los menus
        int menuPrincipal, menuPila, menuCola;
        // variables de eliminacion de elementos
        int eliminarPila, eliminarCola;
        // variables de ingreso de elementos
        int ingresoPila = 0;
        int ingresoCola = 0;
        // variables de repeticion
        int principal = 0;
        int programP = 0;
        int programC = 0;
        int errores = 0;
        // variables de control
        int max = 6;
        int cantidad = 0;
        int total = 0;

        // Repetidor Principal
        do {
            // Repetidor del menu principal
            do {
                System.out.println(" ____________SELECION____________");
                System.out.println("Selecciona 1 para usar pila.");
                System.out.println("Selecciona 2 para usar cola.");
                System.out.println("Selecciona 3 para terminar el programa.");
                menuPrincipal = sc.nextInt();
            } while (menuPrincipal < 1 || menuPrincipal > 3);

            // Selecion de menu principal
            switch (menuPrincipal) {
                case 1:
                    // se reinicia el repetidor de la pila para poder volver a entrar
                    programP = 0;
                    // Repetidor de la pila
                    do {
                        // Repetidor del menu pila
                        do {
                            System.out.println(" ____________MENU____________");
                            System.out.println(" Selecciona 1 para Ingresar número a la pila.");
                            System.out.println(" Selecciona 2 para Mostrar Pila.");
                            System.out.println(" Selecciona 3 para Eliminar último número de la pila.");
                            System.out.println(" Selecciona 4 para Salir de pila.");
                            menuPila = sc.nextInt();
                        } while (menuPila < 1 || menuPila > 4);

                        // Selecion de menu pila
                        switch (menuPila) {
                            case 1:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuPila + "-------");
                                System.out.println("");

                                // Repetidor para verificar que la cantidad de elementos a ingresar no supere el
                                // contenedor y no sea negativa
                                do {
                                    // Se muestra el limite del contenedor y se pregunta cuantos elementos va a
                                    // ingresar
                                    System.out.println("límite del contenedor." + max);
                                    System.out.println("Cuántos elementos desea ingresar a la pila.");
                                    ingresoPila = sc.nextInt();
                                    // Si la cantidad de elementos a ingresar es mayor al contenedor
                                    // o es negativa se le manda un mensaje al usuario
                                    if (ingresoPila > max || ingresoPila <= 0) {
                                        System.out.println("");
                                        System.out.println("Cantidad nula.");
                                        System.out.println(
                                                "Por favor ingrese una cantidad dentro del máximo del contenedor.");
                                        System.out.println("");
                                    }
                                } while (ingresoPila > max || ingresoPila <= 0);

                                // se reinician las variables de control para esta operacion
                                errores = 0;
                                total = 0;
                                // Repetidor para ingresar los elementos a la pila
                                // se inicializa la variable x en 0
                                int x = 0;
                                do {
                                    // se incrementa la variable x en 1
                                    x++;
                                    // Si la pila ya esta llena entonces se le manda un mensaje al usuario.
                                    if (pila.size() == max) {
                                        System.out.println("El  estado de la pila actual es:" + pila);
                                        System.out.println("límite del contenedor.");
                                        // se iguala errores a 1 para salir del repetidor
                                        errores = 1;
                                        // si no esta lleno se permitira la ingresión de elementos
                                    } else {
                                        // se le pide al usuario que ingrese un número a la pila
                                        System.out.print("Ingrese un número " + x + " a la pila:");
                                        cantidad = sc.nextInt();
                                        // se acumula los elementos ingresados
                                        total += cantidad;

                                        // Si el total de elementos acumulados es mayor a 99 entonces
                                        // se le manda un mensaje al usuario.
                                        if (total >= 99) {
                                            System.out.println("");
                                            System.out.println("El acumulado superó el límite del contenedor.");
                                            System.out.println("Por favor introduzca valores más bajos.");
                                            // se le resta a total la ultima cantidad ingresada
                                            total -= cantidad;
                                            System.out.println("");
                                        } else {
                                            // si no supera el limite se ingresa el elemento a la pila
                                            pila.push(cantidad);
                                        }
                                        // se muestra el estado actual de la pila
                                        System.out.println("El  estado de la pila actual es:" + pila);
                                        System.out.println("");
                                        // Si x es igual a la cantidad pedida o a la cantidad maxima
                                        // del contenedor se le manda un mensaje al usuario
                                        if (x == max || x == ingresoPila) {
                                            System.out.println("Alcanzó la cantidad de elemento introducido");
                                            System.out.println("");
                                            errores = 1;
                                        }
                                    }
                                } while (errores <= 0);
                                break;

                            case 2:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuPila + "-------");
                                System.out.println("");
                                // Mostrar si la pila esta vacia
                                System.out.println("La pila está vacía?:" + pila.isEmpty());
                                // Mostrar los elementos de la pila
                                System.out.println("El  estado de la pila actual es:" + pila);
                                // Mostrar el elemento que esta en la parte superior de la pila
                                if (pila.isEmpty() == false) {
                                    System.out.println("Elemento en la parte superior: " + pila.peek());
                                    System.out.println("");
                                }
                                break;

                            case 3:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuPila + "-------");
                                System.out.println("");
                                // Verificar si la pila no esta vacia
                                if (!pila.isEmpty()) {
                                    // Preguntar si esta seguro de eliminar el ultimo elemento
                                    int confirmacion = 0;
                                    // Repetidor para verificar que la opcion ingresada sea valida
                                    do {
                                        System.out.println("¿Quiere eliminar el último elemento?");
                                        System.out.println("1. Si, 2. No ");
                                        eliminarPila = sc.nextInt();
                                        // Si la opcion es 1 o 2 se iguala confirmacion a 1 para salir del repetidor
                                        if (eliminarPila == 1 || eliminarPila == 2) {
                                            confirmacion = 1;
                                        } else {
                                            System.out.println("");
                                            System.out.println("Opción no válida, por favor ingrese 1 o 2.");
                                            System.out.println("");
                                        }
                                    } while (confirmacion == 0);
                                    // Si la opcion es 1 se elimina el ultimo elemento
                                    switch (eliminarPila) {
                                        case 1:
                                            // Mostrar el estado actual de la pila
                                            System.out.println("El estado de la pila es:" + pila);
                                            // Eliminar el ultimo elemento y mostrarlo
                                            System.out.println("Número eliminado: " + pila.pop());
                                            // Mostrar el estado actualizado de la pila
                                            System.out.println("El estado de la pila actualizado es:" + pila);
                                            System.out.println("");
                                            break;
                                        case 2:
                                            // Si la opcion es 2 no se elimina ningun elemento
                                            System.out.println("No se elimino ningun elemento.");
                                            System.out.println("");
                                            break;
                                    }
                                    // Si la pila esta vacia se le manda un mensaje al usuario
                                } else {
                                    System.out.println("La pila está vacía, no se puede eliminar ningún elemento.");
                                }
                                break;
                            case 4:
                                // Salir del menu pila
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuPila + "-------");
                                System.out.println("");
                                System.out.println("Se ha salido de la pila.");
                                System.out.println("");
                                // se iguala programP a 1 para salir del repetidor de la pila
                                programP = 1;
                                break;
                        }
                        // Repetidor del menu pila
                    } while (programP == 0);
                    break;

                case 2:
                    // se reinicia el repetidor de la cola para poder volver a entrar
                    programC = 0;
                    // Repetidor cola
                    do {
                        // Repetidor del menu cola
                        do {
                            System.out.println(" ____________MENU____________");
                            System.out.println(" Selecciona 1 para Ingresar número a la cola.");
                            System.out.println(" Selecciona 2 para Mostrar cola.");
                            System.out.println(" Selecciona 3 para Eliminar último número de la cola.");
                            System.out.println(" Selecciona 4 para Salir de cola.");
                            menuCola = sc.nextInt();
                        } while (menuCola < 1 || menuCola > 4);

                        // Seleccion de menu cola
                        switch (menuCola) {
                            case 1:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuCola + "-------");
                                System.out.println("");
                                // Repetidor para verificar que la cantidad de elementos a ingresar no supere el
                                // contenedor y no sea negativa
                                do {
                                    System.out.println("límite del contenedor." + max);
                                    System.out.println("Cuántos elementos desea ingresar a la cola.");
                                    ingresoCola = sc.nextInt();

                                    if (ingresoCola > max || ingresoCola <= 0) {
                                        System.out.println("");
                                        System.out.println("Cantidad nula.");
                                        System.out.println(
                                                "Por favor ingrese una cantidad dentro del máximo del contenedor.");
                                        System.out.println("");
                                    }
                                } while (ingresoCola > max || ingresoCola <= 0);
                                // se reinician las variables de control para esta operacion
                                errores = 0;
                                total = 0;
                                // Repetidor para ingresar los elementos a la cola
                                // se inicializa la variable j en 0
                                int j = 0;
                                do {
                                    // se incrementa la variable j en 1
                                    j++;
                                    // Si la cola ya esta llena entonces se le manda un mensaje al usuario.
                                    if (cola.size() == max) {
                                        System.out.println("El  estado de la cola actual es:" + cola);
                                        System.out.println("límite del contenedor.");
                                        // se iguala errores a 1 para salir del repetidor
                                        errores = 1;
                                        // si no esta lleno se permitira la ingresión de elementos
                                    } else {
                                        // se le pide al usuario que ingrese un número a la cola
                                        System.out.println("Ingrese un número " + j + " a la cola.");
                                        cantidad = sc.nextInt();
                                        // se acumula los elementos ingresados
                                        total = total + cantidad;
                                        // Si el total de elementos acumulados es mayor a 99 entonces
                                        // se le manda un mensaje al usuario.
                                        if (total >= 99) {
                                            System.out.println("");
                                            System.out.println("El acumulado superó el límite del contenedor.");
                                            System.out.println("Por favor introduzca valores más bajos.");
                                            // se le resta a total la ultima cantidad ingresada
                                            total -= cantidad;
                                            System.out.println("");
                                        } else {
                                            // si no supera el limite se ingresa el elemento a la cola
                                            cola.add(cantidad);
                                        }
                                        // se muestra el estado actual de la cola
                                        System.out.println("El  estado de la cola actual es:" + cola);
                                        System.out.println("");
                                        // Si j es igual a la cantidad pedida o a la cantidad maxima
                                        // del contenedor se le manda un mensaje al usuario
                                        if (j == max || j == ingresoCola) {
                                            System.out.println("Alcanzó la cantidad de elemento introducido");
                                            System.out.println("");
                                            errores = 1;
                                        }
                                    }
                                } while (errores <= 0);
                                break;

                            case 2:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuCola + "-------");
                                System.out.println("");
                                // Mostrar si la cola esta vacia
                                System.out.println("La cola está vacía?:" + cola.isEmpty());
                                // Mostrar el elemento que esta en la parte frontal de la cola
                                System.out.println("El  estado de la cola actual es:" + cola);
                                // Mostrar los elementos de la cola
                                if (cola.isEmpty() == false) {
                                    System.out.println("Elemento en la parte frontal: " + cola.peek());
                                    System.out.println("");
                                }
                                break;

                            case 3:
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuCola + "-------");
                                System.out.println("");
                                // Verificar si la cola no esta vacia
                                if (!cola.isEmpty()) {
                                    // Preguntar si esta seguro de eliminar el primer elemento
                                    int confirmacionC = 0;
                                    // Repetidor para verificar que la opcion ingresada sea valida
                                    do {
                                        System.out.println("¿Quiere eliminar el primer elemento de la cola?");
                                        System.out.println("1. Si, 2. No ");
                                        eliminarCola = sc.nextInt();
                                        // Si la opcion es 1 o 2 se iguala confirmacion a 1 para salir del repetidor
                                        if (eliminarCola == 1 || eliminarCola == 2) {
                                            confirmacionC = 1;
                                        } else {
                                            System.out.println("");
                                            System.out.println("Opción no válida, por favor ingrese 1 o 2.");
                                            System.out.println("");
                                        }
                                    } while (confirmacionC == 0);
                                    // Si la opcion es 1 se elimina el primer elemento
                                    switch (eliminarCola) {
                                        case 1:
                                            // Mostrar el estado actual de la cola
                                            System.out.println("El estado de la cola es:" + cola);
                                            // Eliminar el primer elemento y mostrarlo
                                            System.out.println("Número eliminado: " + cola.poll());
                                            // Mostrar el estado actualizado de la cola
                                            System.out.println("El estado de la cola actualizado es:" + cola);
                                            System.out.println("");
                                            break;
                                        case 2:
                                            // Si la opcion es 2 no se elimina ningun elemento
                                            System.out.println("No se elimino ningun elemento.");
                                            System.out.println("");
                                            break;
                                    }
                                } else {
                                    System.out.println("La cola está vacía, no se puede eliminar ningún elemento.");
                                }
                                break;

                            case 4:
                                // Salir del menu cola
                                System.out.println("");
                                System.out.println("------Caso seleccionado es: " + menuCola + "-------");
                                System.out.println("");
                                System.out.println("Se ha salido de la cola.");
                                System.out.println("");
                                // se iguala programC a 1 para salir del repetidor de la cola
                                programC = 1;
                                break;
                        }
                        // Repetidor del menu cola
                    } while (programC == 0);
                    break;

                case 3:

                    System.out.println("");
                    System.out.println("Se ha salido del programa.");
                    System.out.println("");
                    principal = 1;
            }
            // Repetidor principal
        } while (principal <= 0);
        sc.close();
    }
}
