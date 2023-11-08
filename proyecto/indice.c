#include "indice.h"

// crea un indice que alberga una clave del tamanio especificado y una funcion para ordenar segun las claves
void indice_crear(T_Indice *p_indice, size_t tam_clave, int cmp(const void*, const void*)) {
    crearLista(&(p_indice->indice));
    p_indice->tam_clave = tam_clave;
    p_indice->cmp = cmp;
}
// inserta la clave de forma ordenada junto al numero de registro
int indice_insertar(T_Indice *p_indice, void *p_clave, unsigned nro_reg) {
    void *info = malloc(sizeof(unsigned)+p_indice->tam_clave);
    if(!info)
        return ERROR;

    memcpy(info, p_clave, p_indice->tam_clave);
    ///desplazamiento + copia de tamclave
    memcpy(info+p_indice->tam_clave, &nro_reg, sizeof(unsigned));

    insertarOrdenado(&(p_indice->indice), info, sizeof(unsigned)+p_indice->tam_clave, p_indice->cmp);

    free(info);
    return OK;
}
// recibe una clave a eliminar y devuelve el numero de registro
int indice_eliminar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg) {
    void *info = malloc(sizeof(unsigned)+p_indice->tam_clave);
    if(!info)
        return ERROR;
    memcpy(info, p_clave, p_indice->tam_clave);

    eliminarElemento(&(p_indice->indice), info, (p_indice->tam_clave)+sizeof(unsigned), p_indice->cmp);
    memcpy(p_nro_reg, info+p_indice->tam_clave, sizeof(unsigned));

    free(info);
    return OK;
}
// busca la clave y devuelve el nro de registro
int indice_buscar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg) {
    void *info = malloc(sizeof(unsigned)+p_indice->tam_clave);
    if(!info)
        return ERROR;
    memcpy(info, p_clave, p_indice->tam_clave);
///ESTO NO TIENE QUE SER ELIMINAR ELEMENTO, TIENE QUE SER BUSCAR ELEMENTO
//  eliminarElemento(&(p_indice->indice), info, (p_indice->tam_clave)+sizeof(unsigned), p_indice->cmp);
    memcpy(p_nro_reg, info+p_indice->tam_clave, sizeof(unsigned));

    free(info);
    return OK;
}
// carga el indice a partir del archivo ordenado
int indice_cargar(T_Indice *p_indice, const char *path) {

    /**abrir archivo como lectura
    cargarlo en el indice/invocar indice recorrer y llamar la funcion leerDeArch
    **/
    return OK;
}
// graba un archivo con el contenido del indice
int indice_grabar(T_Indice *p_indice, const char *path) {

    FILE *fp = fopen(path, "wb");
    if(!fp)
        return ERROR;

//  indice_recorrer(p_indice, escribirRegEnArch, fp);

    fclose(fp);

    return OK;
}
// vacia el indice
void indice_vaciar(T_Indice *p_indice) {
    vaciarLista(&(p_indice->indice));
}
// recorre el indice en orden y ejecuta la accion en cada elemento
int indice_recorrer(T_Indice *p_indice, void accion(const void*, unsigned, void *), void *param)
{
    return OK;
}

//int escribirEnArch(const void *pclave, const unsigned nro_reg, void *fp)
//{
////    void *info = malloc(sizeof(unsigned)+p_indice->tam_clave);
////    if(!info)
////        return ERROR;
////
////    memcpy(info, p_clave, p_indice->tam_clave);
////    memcpy(info+p_indice->tam_clave, &nro_reg, sizeof(unsigned));
////    p_indice->
////    fwrite(info, sizeof(unsigned)+p_indice->tam_clave, 1, fp);
////
////    free(info);
//
//    fwrite()
//
//    return OK;
//}
