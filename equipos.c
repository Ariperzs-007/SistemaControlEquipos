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
void buscarEquipo();
void modificarEquipo();
void eliminarEquipo();
void menu();

int main(){
    menu();
    return 0;
}

void menu(){
    int opcion;

    do{

  
        printf("\n=================================\n");
        printf("   SISTEMA CONTROL DE EQUIPOS\n");
        printf("=================================\n");
        printf("1. Registrar equipo\n");
        printf("2. Mostrar equipos\n");
        printf("3. Buscar equipo\n");
        printf("4. Modificar equipo\n");
        printf("5. Eliminar equipo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");


        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                registrarEquipo();
                break;

            case 2:
                mostrarEquipos();
                break;

            case 3:
                buscarEquipo();
                break;

            case 4:
                modificarEquipo();
                break;

            case 5:
                eliminarEquipo();
                break;

            case 6:
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }
    } while(opcion != 6);
}

void registrarEquipo(){
    FILE *archivo;
    Equipo equipo;
    archivo = fopen("equipos.dat", "ab");
    if(archivo == NULL){
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

    if(archivo == NULL){
        printf("\nNo existen registros.\n");
        return;
    }
    printf("\n--- LISTADO DE EQUIPOS ---\n");

    while(fread(&equipo, sizeof(Equipo), 1, archivo)){
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
void buscarEquipo(){
    FILE *archivo;
    Equipo equipo;
    char codigoBuscar[20];
    int encontrado = 0;
    archivo = fopen("equipos.dat", "rb");

    if(archivo == NULL){
        printf("\nNo existe el archivo.\n");
        return;
    }

    printf("\nIngrese el codigo a buscar: ");
    scanf("%s", codigoBuscar);

    while(fread(&equipo, sizeof(Equipo), 1, archivo)){
        if(strcmp(equipo.codigo, codigoBuscar) == 0){
            encontrado = 1;
            printf("\nEquipo encontrado:\n");
            printf("Codigo      : %s\n", equipo.codigo);
            printf("Nombre      : %s\n", equipo.nombre);
            printf("Marca       : %s\n", equipo.marca);
            printf("Responsable : %s\n", equipo.responsable);
            printf("Estado      : %s\n", equipo.estado);
            printf("Precio      : Q%.2f\n", equipo.precio);

            break;
        }
    }

    if(!encontrado){
        printf("\nEquipo no encontrado.\n");
    }
    fclose(archivo);
}

void modificarEquipo(){
    FILE *archivo;
    Equipo equipo;
    char codigoBuscar[20];
    int encontrado = 0;
    archivo = fopen("equipos.dat", "rb+");

    if(archivo == NULL){
        printf("\nNo existe el archivo.\n");
        return;
    }

    printf("\nIngrese el codigo a modificar: ");
    scanf("%s", codigoBuscar);

    while(fread(&equipo, sizeof(Equipo), 1, archivo)){
        if(strcmp(equipo.codigo, codigoBuscar) == 0){
            encontrado = 1;

            printf("\nNuevo nombre: ");
            scanf(" %[^\n]", equipo.nombre);

            printf("Nueva marca: ");
            scanf(" %[^\n]", equipo.marca);

            printf("Nuevo responsable: ");
            scanf(" %[^\n]", equipo.responsable);

            printf("Nuevo estado: ");
            scanf(" %[^\n]", equipo.estado);

            printf("Nuevo precio: ");
            scanf("%f", &equipo.precio);

            fseek(archivo, -sizeof(Equipo), SEEK_CUR);
            fwrite(&equipo, sizeof(Equipo), 1, archivo);

            printf("\nEquipo modificado correctamente.\n");
            break;
        }
    }

    if(!encontrado){
        printf("\nEquipo no encontrado.\n");
    }

    fclose(archivo);
}

void eliminarEquipo(){
    FILE *archivo;
    FILE *temp;
    Equipo equipo;
    char codigoEliminar[20];
    int encontrado = 0;
    archivo = fopen("equipos.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(archivo == NULL){
        printf("\nNo existe el archivo.\n");
        return;
    }
    printf("\nIngrese el codigo a eliminar: ");
    scanf("%s", codigoEliminar);

    while(fread(&equipo, sizeof(Equipo), 1, archivo)){
        if(strcmp(equipo.codigo, codigoEliminar) == 0){
            encontrado = 1;
        }
        else{
            fwrite(&equipo, sizeof(Equipo), 1, temp);
        }
    }
    fclose(archivo);
    fclose(temp);
    remove("equipos.dat");
    rename("temp.dat", "equipos.dat");

    if(encontrado){
        printf("\nEquipo eliminado correctamente.\n");
    }
    else{
        printf("\nEquipo no encontrado.\n");
    }
}