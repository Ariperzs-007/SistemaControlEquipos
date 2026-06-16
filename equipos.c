#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char codigo[20];
    char nombre[50];
    char marca[30];
    char responsable[50];
    char estado[20];
    float precio;
} Equipo;

void registrarEquipo();
void mostrarEquipos();


int main()
{
    menu();
    return 0;
}

void menu(){
    int opcion;

  
        printf("\n=================================\n");
        printf("   SISTEMA CONTROL DE EQUIPOS\n");
        printf("=================================\n");
        printf("1. Registrar equipo\n");
        printf("2. Mostrar equipos\n");



}

void registrarEquipo(){
    FILE *archivo;
    Equipo equipo;

    archivo = fopen("equipos.dat", "ab");

    if(archivo == NULL)
    {
        printf("\nError al abrir el archivo.\n");
        return;
    }

    printf("\n--- REGISTRAR EQUIPO ---\n");

    printf("Codigo: ");
    scanf("%s", equipo.codigo);

    printf("Nombre: ");
    scanf(" %[^\n]", equipo.nombre);

    printf("Marca: ");
    scanf(" %[^\n]", equipo.marca);

    printf("Responsable: ");
    scanf(" %[^\n]", equipo.responsable);

    printf("Estado: ");
    scanf(" %[^\n]", equipo.estado);

    printf("Precio: ");
    scanf("%f", &equipo.precio);

    fwrite(&equipo, sizeof(Equipo), 1, archivo);

    fclose(archivo);

    printf("\nEquipo registrado correctamente.\n");
}

void mostrarEquipos(){
    FILE *archivo;
    Equipo equipo;

    archivo = fopen("equipos.dat", "rb");

    if(archivo == NULL)
    {
        printf("\nNo existen registros.\n");
        return;
    }

    printf("\n--- LISTADO DE EQUIPOS ---\n");

    while(fread(&equipo, sizeof(Equipo), 1, archivo))
    {
        printf("\nCodigo      : %s", equipo.codigo);
        printf("\nNombre      : %s", equipo.nombre);
        printf("\nMarca       : %s", equipo.marca);
        printf("\nResponsable : %s", equipo.responsable);
        printf("\nEstado      : %s", equipo.estado);
        printf("\nPrecio      : Q%.2f", equipo.precio);
        printf("\n-------------------------------");
    }

    fclose(archivo);
}
