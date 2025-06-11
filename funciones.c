#include <stdio.h>
#include <string.h>
#include "funciones.h"

void registrarLibro(struct Libro libros[], int *cantidad) {
    if (*cantidad >= 10) {
        printf("No se pueden registrar mas libros.\n");
        return;
    }

    int id, existe = 0;
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);

    for (int i = 0; i < *cantidad; i++) {
        if (libros[i].id == id) {
            existe = 1;
            break;
        }
    }

    if (existe == 1) {
        printf("El ID ya esta registrado.\n");
        return;
    }

    libros[*cantidad].id = id;
    getchar(); // limpiar buffer

    printf("Ingrese titulo: ");
    fgets(libros[*cantidad].titulo, 100, stdin);
    //para cambiar el ultimo valor, muy largo pero funciona
    libros[*cantidad].titulo[strcspn(libros[*cantidad].titulo, "\n")] = 0;
    //jeje no hay ñ, escojí usar anio en lugar de la opción mas chistosa
    printf("Ingrese autor: ");
    fgets(libros[*cantidad].autor, 50, stdin);
    libros[*cantidad].autor[strcspn(libros[*cantidad].autor, "\n")] = 0;
    printf("Ingrese anio de publicacion: ");
    scanf("%d", &libros[*cantidad].anio);
    strcpy(libros[*cantidad].estado, "Disponible");

    (*cantidad)++;
    printf("Libro registrado correctamente.\n");
}

void mostrarLibros(struct Libro libros[], int cantidad) {
    printf("\nID\tTitulo\t\t\tAutor\t\t\tAnio\tEstado\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d\t%s\t\t%s\t\t%d\t%s\n",libros[i].id,libros[i].titulo,libros[i].autor,libros[i].anio,libros[i].estado);
    }
}

void buscarLibro(struct Libro libros[], int cantidad) {
    int opcion;
    printf("Buscar por:\n1. ID\n2. Titulo\n>> ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1) {
        int id;
        printf("Ingrese ID: ");
        scanf("%d", &id);
        for (int i = 0; i < cantidad; i++) {
            if (libros[i].id == id) {
                printf("Titulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                       libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
                return;
            }
        }
    } else if (opcion == 2) {
        char titulo[100];
        printf("Ingrese titulo: ");
        fgets(titulo, 100, stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        for (int i = 0; i < cantidad; i++) {
            if (strcmp(libros[i].titulo, titulo) == 0) {
                printf("ID: %d\nAutor: %s\nAnio: %d\nEstado: %s\n",
                       libros[i].id, libros[i].autor, libros[i].anio, libros[i].estado);
                return;
            }
        }
    }
    printf("Libro no encontrado.\n");
}

void actualizarEstado(struct Libro libros[], int cantidad) {
    int id;
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    for (int i = 0; i < cantidad; i++) {
        if (libros[i].id == id) {
            if (strcmp(libros[i].estado, "Disponible") == 0) {
                strcpy(libros[i].estado, "Prestado");
            } else {
                strcpy(libros[i].estado, "Disponible");
            }
            printf("Estado actualizado: %s\n", libros[i].estado);
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

void eliminarLibro(struct Libro libros[], int *cantidad) {
    int id;
    printf("Ingrese ID del libro a eliminar: ");
    scanf("%d", &id);
    for (int i = 0; i < *cantidad; i++) {
        if (libros[i].id == id) {
            for (int j = i; j < *cantidad - 1; j++) {
                libros[j] = libros[j + 1];
            }
            (*cantidad)--;
            printf("Libro eliminado.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}