#include "indice.h"

// crea un indice que alberga una clave del tamanio especificado y una funcion para ordenar segun las claves
void indice_crear(T_Indice *p_indice, size_t tam_clave, int cmp(const void*, const void*))
{
    crearLista(&(p_indice->indice));
    p_indice->tam_clave = tam_clave;
    p_indice->cmp = cmp;
}

// inserta la clave de forma ordenada junto al numero de registro
int indice_insertar(T_Indice *p_indice, void *p_clave, unsigned nro_reg)
{
    void *info = malloc(sizeof(unsigned) + p_indice->tam_clave);
    if(!info)
        return ERROR;

    memcpy(info, p_clave, p_indice->tam_clave);

    ///desplazamiento + copia de tamclave
    memcpy(info + p_indice->tam_clave, &nro_reg, sizeof(unsigned));

    insertarOrdenado(&(p_indice->indice), info, sizeof(unsigned) + p_indice->tam_clave, p_indice->cmp);
    //printf("%li, %u\n", *((long*)info), *(unsigned*)(info + p_indice->tam_clave));
    free(info);

    return OK;
}

// recibe una clave a eliminar y devuelve el numero de registro
int indice_eliminar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg)
{
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
int indice_buscar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg)
{
    void *info = malloc(sizeof(unsigned)+p_indice->tam_clave);
    if(!info)
        return ERROR;
    memcpy(info, p_clave, p_indice->tam_clave);

    buscarElemento(&(p_indice->indice), info, (p_indice->tam_clave)+sizeof(unsigned), p_indice->cmp);

    memcpy(p_nro_reg, info+p_indice->tam_clave, sizeof(unsigned));

    free(info);
    return OK;
}

typedef struct
{
    FILE* fp;
    size_t Tam;
} indexfile;

// graba un archivo con el contenido del indice
int indice_grabar(T_Indice *p_indice, const char *path)
{
    indexfile f;
    f.fp = fopen(path, "wb");
    if(!f.fp)
        return ERROR;
    f.Tam = p_indice->tam_clave + sizeof(unsigned);

    mapLista(&(p_indice->indice), escribirRegEnArch, &f);

    fclose(f.fp);

    return OK;
}

void escribirRegEnArch(void* info, void* f)
{
    indexfile* t = (indexfile*)f;
    fwrite(info, t->Tam, 1, t->fp);
    //printf("%li, %u\n", *((long*)info), *(unsigned*)(info + sizeof(long)));
}


// carga el indice a partir del archivo ordenado
int indice_cargar(T_Indice *p_indice, const char *path)
{
    FILE *fp = fopen(path, "rb");
    void *info = malloc(p_indice->tam_clave + sizeof(unsigned));
    if(!fp)
        return ERROR;
    while(fread(info, p_indice->tam_clave + sizeof(unsigned), 1, fp))
    {
        //printf("%li, %u\n", *((long*)info), *(unsigned*)(info + p_indice->tam_clave));
        indice_insertar(p_indice, info, *((unsigned*)(info + p_indice->tam_clave)));
    }
    free(info);
    fclose(fp);
    return OK;
}

// vacia el indice
void indice_vaciar(T_Indice *p_indice)
{
    vaciarLista(&(p_indice->indice));
}
// recorre el indice en orden y ejecuta la accion en cada elemento

int indice_recorrer(T_Indice *p_indice, void accion(const void*,unsigned, void *), void *param)
{
    unsigned* nro_reg;
    tNodo * inicio = p_indice->indice;
    while(p_indice->indice)
    {
        nro_reg = (unsigned*)(p_indice->indice->elem + p_indice->tam_clave);
        accion(p_indice->indice->elem, *nro_reg, param);
        p_indice->indice = p_indice->indice->sig;
    }
    p_indice->indice = inicio;
    return OK;
}
