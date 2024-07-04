#include <stdio.h>
#include <string.h>

void cargarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][4]);
void guardarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][4]);

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4]);
void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][4]);
void imprimirReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]);
void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]);
