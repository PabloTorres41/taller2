#include <stdio.h>
#include "funciones.h"
#include <string.h>

// Cargar los datos desde los archivos
void cargarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][4]) {
    FILE *archivo;
    int i;

    // Cargar habitaciones y precios
    archivo = fopen("habitaciones.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir habitaciones.txt\n");
        return;
    }
    for (i = 0; i < 9; i++) {
        fscanf(archivo, "%s %s %s %lf", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], &precios[i]);
    }
    fclose(archivo);

    // Cargar clientes
    archivo = fopen("clientes.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir clientes.txt\n");
        return;
    }
    for (i = 0; i < 5; i++) {
        fscanf(archivo, "%s %s", clientes[i][0], clientes[i][1]);
    }
    fclose(archivo);

    // Cargar reservas
    archivo = fopen("reservas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir reservas.txt\n");
        return;
    }
    for (i = 0; i < 10; i++) {
        fscanf(archivo, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]);
    }
    fclose(archivo);
}

// Guardar los datos en los archivos
void guardarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][4]) {
    FILE *archivo;
    int i;

    // Guardar habitaciones y precios
    archivo = fopen("habitaciones.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir habitaciones.txt\n");
        return;
    }
    for (i = 0; i < 9; i++) {
        fprintf(archivo, "%s %s %s %.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
    }
    fclose(archivo);

    // Guardar clientes
    archivo = fopen("clientes.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir clientes.txt\n");
        return;
    }
    for (i = 0; i < 5; i++) {
        fprintf(archivo, "%s %s\n", clientes[i][0], clientes[i][1]);
    }
    fclose(archivo);

    // Guardar reservas
    archivo = fopen("reservas.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir reservas.txt\n");
        return;
    }
    for (i = 0; i < 10; i++) {
        fprintf(archivo, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
    }
    fclose(archivo);
}

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el tamaño de habitación que desea buscar: ");
    scanf("%s", tipo);
    printf("#\t\tTamaño\t\tHotel\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Seleccione la habitación que desea reservar: ");
    scanf("%d", numHabitacion); 
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char hotel[40];
    printf("Ingrese el nombre del hotel que desea buscar: ");
    scanf("%s", hotel);
    printf("#\t\tTamaño\t\tHotel\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Seleccione la habitación que desea reservar: ");
    scanf("%d", numHabitacion);
}

void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    int indiceCliente = -1;

    printf("Ingrese su cédula: ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            indiceCliente = i;
            break;
        }
    }
    if (indiceCliente == -1) {
        for (int i = 0; i < 5; i++) {
            if (strcmp(clientes[i][1], "") == 0) {
                indiceCliente = i;
                strcpy(clientes[indiceCliente][1], cedula);
                printf("Ingrese su nombre: ");
                scanf("%s", clientes[indiceCliente][0]);
                break;
            }
        }
    }

    if (indiceCliente == -1) {
        printf("No hay espacio para nuevos clientes.\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = indiceCliente; // Índice del cliente
            reservas[i][1] = numHabitacion - 1; // Ajuste del índice de la habitación
            reservas[i][2] = 0; // Estado de la reserva
            reservas[i][3] = 0; // Estado de pago (0 = no pagado, 1 = pagado)
            printf("Reserva realizada con éxito. Número de reserva: %d\n", i + 1);
            guardarDatos(clientes, habitaciones, precios, reservas);
            return;
        }
    }
    printf("No hay espacio para nuevas reservas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    int indiceCliente = -1;

    printf("Ingrese su cédula: ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            indiceCliente = i;
            break;
        }
    }
    if (indiceCliente == -1) {
        printf("Cliente no encontrado.\n");
        *numReserva = -1;
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == indiceCliente) {
            *numReserva = i;
            printf("Reserva encontrada. Número de reserva: %d\n", *numReserva + 1);
            return;
        }
    }
    printf("No se encontraron reservas para la cédula ingresada.\n");
    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (numReserva < 0 || numReserva >= 10 || reservas[numReserva][0] == -1) {
        printf("Número de reserva inválido o reserva no encontrada.\n");
        return;
    }

    int clienteIndice = reservas[numReserva][0];
    int habitacionIndice = reservas[numReserva][1];
    int estadoReserva = reservas[numReserva][2];

    printf("Detalles de la Reserva:\n");
    printf("Número de Reserva: %d\n", numReserva + 1);
    printf("Cliente: %d\n", clienteIndice + 1); // Índice del cliente mostrado como 1 basado
    printf("Habitación: %s\n", habitaciones[habitacionIndice][0]);
    printf("Tamaño: %s\n", habitaciones[habitacionIndice][1]);
    printf("Hotel: %s\n", habitaciones[habitacionIndice][2]);
    printf("Precio: %.2lf\n", precios[habitacionIndice]);
    printf("Estado de la Reserva: %s\n", estadoReserva ? "Pagada" : "No Pagada");
}

void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (numReserva < 0 || numReserva >= 10 || reservas[numReserva][0] == -1) {
        printf("Número de reserva inválido o reserva no encontrada.\n");
        return;
    }

    if (reservas[numReserva][2] == 1) {
        printf("La reserva ya ha sido pagada.\n");
        return;
    }

    int habitacionIndice = reservas[numReserva][1];

    printf("Detalles de la Reserva:\n");
    printf("Número de Reserva: %d\n", numReserva + 1);
    printf("Habitación: %s\n", habitaciones[habitacionIndice][0]);
    printf("Tamaño: %s\n", habitaciones[habitacionIndice][1]);
    printf("Hotel: %s\n", habitaciones[habitacionIndice][2]);
    printf("Precio: %.2lf\n", precios[habitacionIndice]);

    char confirmarPago;
    printf("¿Desea confirmar el pago? (s/n): ");
    scanf(" %c", &confirmarPago);

    if (confirmarPago == 's' || confirmarPago == 'S') {
        reservas[numReserva][2] = 1;
        printf("Pago realizado con éxito. La reserva ahora está marcada como pagada.\n");
        guardarDatos(clientes, habitaciones, precios, reservas);
    } else {
        printf("Pago no realizado.\n");
    }
}
