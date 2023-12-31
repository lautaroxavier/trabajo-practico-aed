#ifndef TP_SOCIOS_CLUB_INDICE_H
#define TP_SOCIOS_CLUB_INDICE_H

#include "lista-enlazada.h"

#define OK 1
#define ERROR 0


typedef struct
{
    size_t tam_clave;
    tLista indice;
    int (*cmp)(const void*, const void*);
}
        T_Indice;

// crea un indice que alberga una clave del tamanio especificado y una funcion para ordenar segun las claves
void indice_crear(T_Indice *p_indice, size_t tam_clave, int cmp(const void*, const void*));

// inserta la clave de forma ordenada junto al numero de registro
int indice_insertar(T_Indice *p_indice, void *p_clave, unsigned nro_reg);

// recibe una clave a eliminar y devuelve el numero de registro
int indice_eliminar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg);

// busca la clave y devuelve el nro de registro
int indice_buscar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg);

// graba un archivo con el contenido del indice
int indice_grabar(T_Indice *p_indice, const char *path);

void escribirRegEnArch(void* Orig, void* f);

// carga el indice a partir del archivo ordenado
int indice_cargar(T_Indice *p_indice, const char *path);

void leerRegDeArch(void* Orig, void* f);

// vacia el indice
void indice_vaciar(T_Indice *p_indice);

// recorre el indice en orden y ejecuta la accion en cada elemento
int indice_recorrer(T_Indice *p_indice, void accion(const void*, unsigned, void *), void *param);

#endif //TP_SOCIOS_CLUB_INDICE_H

