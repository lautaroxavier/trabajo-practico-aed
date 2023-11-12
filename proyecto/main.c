#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "indice.h"
#include "utilidad.h"

#define ARCH_BIN_SOCIOS "socios.dat"
#define ARCH_INDICE "socios.idx"

typedef struct
{
    int dia;
    int mes;
    int anio;
}
T_Fecha;

typedef struct
{
    long nro_socio; // 2 - 9.999.999
    char nya[61];
    long dni; // 10.001 - 99.999.999
    T_Fecha fecha_nac;
    char sexo; // 'F', 'M', 'O'
    T_Fecha fecha_afiliacion;
    char categoria[10]; // 'MENOR', 'CADETE', 'ADULTO', 'VITALICIO', 'HONORARIO', 'JUBILADO'
    T_Fecha fecha_ultima_cuota_paga;
    char estado; // 'A', 'I'
    T_Fecha fecha_baja; // debe ser vacio si el estado es 'A'
}
T_Reg_Socio;

void clrscr()
{
    system("@cls||clear");
}

int validar_categoria(char *categoria);

int validar_socio(T_Reg_Socio *p_socio);

void mostrar_socio(T_Reg_Socio *p_socio);

void trozar_campos_socio(char *src, T_Reg_Socio *p_socio);

int crear_arch_bin();

void mostrar_menu();

void verificar_arch_bin_socios();

void dar_de_alta_socio(T_Indice *pIndice);

void modificar_nombre_socio(T_Indice *pIndice);

void dar_de_baja_socio(T_Indice *pIndice);

void mostrar_inactivos(T_Indice *pIndice);

void mostrar_socios_activos(T_Indice *pIndice);

void mostrar_socios_atrasados(T_Indice *pIndice);

void primera_parte();

void segunda_parte();

int indice_asignar(T_Indice *p_indice, const char *path);

int main()
{
    primera_parte();
    segunda_parte();
    return 0;
}

int indice_asignar(T_Indice *p_indice, const char *path)
{
    // crea el indice a partir del archivo de socios
    // el indice solo debe contener los socios activos
    FILE* fp = fopen(path, "rb");
    unsigned reg = 0;
    T_Reg_Socio socio_tmp;
    if(!fp)
    {
        return ERROR;
    }
    while(fread(&socio_tmp, sizeof(T_Reg_Socio), 1, fp))
    {
        if(socio_tmp.estado == 'A')
        {
            indice_insertar(p_indice, &(socio_tmp.nro_socio), reg);
            //printf("nro socio: %li registro: %u\n", socio_tmp.nro_socio, reg);
        }
        reg++;
    }
    fclose(fp);

    return OK;
}

void mostrarClaveYReg(const void *clave, unsigned reg, void *s)
{
    printf("%li %u \n", *((long*)clave), reg);
}

void primera_parte()
{
    crear_arch_bin(); // convierte socios.txt a socios.dat
    //verificar_arch_bin_socios();
    T_Indice indice;
    indice_crear(&indice, sizeof(long), Compare_Long);
    indice_asignar(&indice,ARCH_BIN_SOCIOS);
    //indice_recorrer(&indice, mostrarClaveYReg, stdout);
    indice_grabar(&indice, ARCH_INDICE);
    indice_vaciar(&indice);
}

void segunda_parte()
{
    // hay que cargar el indice a partir del archivo creado en la primera parte
    char opcion;
    T_Indice indice_socios_activos;
    indice_crear(&indice_socios_activos, sizeof(long), Compare_Long);
    indice_cargar(&indice_socios_activos, ARCH_INDICE);
    //indice_recorrer(&indice_socios_activos, mostrarClaveYReg, stdout);
    do {
        mostrar_menu();
        fflush(stdin);
        scanf("%c", &opcion);
        opcion = toupper(opcion);
        //clrscr();
        switch (opcion)
        {
        case 'A':
            dar_de_alta_socio(&indice_socios_activos);
            break;
        case 'M':
            modificar_nombre_socio(&indice_socios_activos);
            break;
        case 'B':
            dar_de_baja_socio(&indice_socios_activos);
            break;
        case 'L':
            mostrar_inactivos(&indice_socios_activos);
            break;
        case 'V':
            mostrar_socios_activos(&indice_socios_activos);
            break;
        case 'P':
            mostrar_socios_atrasados(&indice_socios_activos);
            break;
        case 'S':
            break;
        default:
            printf("Opcion Invalida\n");
            break;
        }
    } while (opcion != 'S');
    // hay que volver a guardar el indice en un archivo y liberar la memoria
    indice_grabar(&indice_socios_activos, ARCH_INDICE);
    indice_vaciar(&indice_socios_activos);
}

void dar_de_alta_socio(T_Indice *pIndice)
{
    // IMPLEMETAR!!!
    // hay que cargar los datos del usuario en un registro de socio y validar los inputs necesarios
    // hay que buscar que el nro de socio no exista en el indice
    // si no esta en el indice, buscar que no este en el archivo como inactivo
    // si no existe en el indice o el archivo, agregarlo al archivo y al indice
    printf("Agregando nuevo socio...\n");
}

void modificar_nombre_socio(T_Indice *pIndice)
{
    // IMPLEMENTAR!!!
    // pedir un numero de socio
    // buscar el socio en el indice
    // si lo encuentra, pedir el nombre nuevo (validar el largo)
    // modificar el archivo con el nuevo nombre de socio y el indice
    printf("Modificando nombre de socio...\n");
}

void dar_de_baja_socio(T_Indice *pIndice)
{
    // IMPLEMENTAR!!!!
    // buscar el socio en el indice
    // si no esta en el indice, buscarlo  secuencialmente en el archivo de socios como inactivo e informarlo
    // si esta en el indice, modificar el registro en el archivo y sacarlo del indice
    printf("Dando de baja a socio...\n");
}

void mostrar_inactivos(T_Indice *pIndice)
{
    // IMPLEMENTAR!!!
    // buscar secuencialmente en el archivo los socios que esten inactivos
    // e ir insertandolos ordenados por nro de socio en una lista
    // mostrar la lista
    printf("Mostrando socios inactivos...\n");
}

void mostrar_socios_activos(T_Indice *pIndice)
{
    // IMPLEMENTAR!!!
    // recorrer el indice y mostrar los datos de cada socio
    printf("Mostrando socios activos...\n");
}

void mostrar_socios_atrasados(T_Indice *pIndice)
{
    // IMPLEMENTAR!!!
    // recorrer los socios activos usando el indice y buscandolos en el archivo
    // insertar los socios en una lista ordenados por fecha de ultimo pago
    // si la lista tiene mas de 10 elementos, eliminar el ultimo
    // cuando se termina de recorrer el indice se muestran los 10 registros que quedaron en la lista
    printf("Mostrando socios con cuota atrasada...\n");
}

int validar_categoria(char *categoria)
{
    char categorias[6][10] = {
        "MENOR",
        "CADETE",
        "ADULTO",
        "VITALICIO",
        "HONORARIO",
        "JUBILADO"
    };
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(categoria, categorias[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int validar_socio(T_Reg_Socio *p_socio)
{
    // validar nro socio
    if (p_socio->nro_socio < 2 || p_socio->nro_socio > 9999999)
    {
        return 0;
    }
    // validar dni
    if (p_socio->dni < 10001 || p_socio->dni > 99999999)
    {
        return 0;
    }
    // validar sexo
    if (p_socio->sexo != 'M' && p_socio->sexo != 'F' && p_socio->sexo != 'O')
    {
        return 0;
    }
    // verificar categoria
    if(!validar_categoria(p_socio->categoria))
    {
        return 0;
    }
    // verificar estado y fecha de baja
    if(p_socio->estado == 'A')
    {
        if (p_socio->fecha_baja.dia != 0 ||
            p_socio->fecha_baja.mes != 0 ||
            p_socio->fecha_baja.anio != 0)
            {
                return 0;
            }
    }
    else if (p_socio->estado != 'I')
    {
        return 0;
    }
    return 1;
}

void mostrar_socio(T_Reg_Socio *p_socio)
{
    printf("%ld | %s | %ld | %d/%d/%d | %c | %d/%d/%d | %s | %d/%d/%d | %c | %d/%d/%d\n",
            p_socio->nro_socio,
            p_socio->nya,
            p_socio->dni,
            p_socio->fecha_nac.dia,
            p_socio->fecha_nac.mes,
            p_socio->fecha_nac.anio,
            p_socio->sexo,
            p_socio->fecha_afiliacion.dia,
            p_socio->fecha_afiliacion.mes,
            p_socio->fecha_afiliacion.anio,
            p_socio->categoria,
            p_socio->fecha_ultima_cuota_paga.dia,
            p_socio->fecha_ultima_cuota_paga.mes,
            p_socio->fecha_ultima_cuota_paga.anio,
            p_socio->estado,
            p_socio->fecha_baja.dia,
            p_socio->fecha_baja.mes,
            p_socio->fecha_baja.anio);
}

void trozar_campos_socio(char *src, T_Reg_Socio *p_socio)
{
    // eliminar salto de linea
    char *aux = strchr(src, '\n');
    *aux = '\0';
    // leer la fecha de baja
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_baja.dia),
                                &(p_socio->fecha_baja.mes),
                                &(p_socio->fecha_baja.anio));
    *aux = '\0';
    // leer el estado
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%c", &(p_socio->estado));
    *aux = '\0';
    // leer fecha ultima cuota paga
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_ultima_cuota_paga.dia),
                                &(p_socio->fecha_ultima_cuota_paga.mes),
                                &(p_socio->fecha_ultima_cuota_paga.anio));
    *aux = '\0';
    // leer categoria
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%s", p_socio->categoria);
    *aux = '\0';
    // leer fecha afiliacion
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_afiliacion.dia),
                                &(p_socio->fecha_afiliacion.mes),
                                &(p_socio->fecha_afiliacion.anio));
    *aux = '\0';
    // leer sexo
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%c", &(p_socio->sexo));
    *aux = '\0';
    // leer fecha de nacimiento
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_nac.dia),
                                &(p_socio->fecha_nac.mes),
                                &(p_socio->fecha_nac.anio));
    *aux = '\0';
    // leer dni
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%ld", &(p_socio->dni));
    *aux = '\0';
    /// leer nombre y apellido
    aux = strrchr(src, '|');
    strcpy(p_socio->nya, aux + 1);
    *aux = '\0';
    // leer nro socio
    aux = src;
    sscanf(aux, "%ld", &(p_socio->nro_socio));
    *aux = '\0';
}

int crear_arch_bin()
{
    const char *archivo_txt = "socios.txt";
    char buffer[1000];
    T_Reg_Socio socio;
    FILE *p_arch_txt = fopen(archivo_txt, "rt");
    FILE *p_arch_bin = fopen("socios.dat", "wb");
    while(fgets(buffer, 1000, p_arch_txt))
    {
        trozar_campos_socio(buffer, &socio);
        if (!validar_socio(&socio))
        {
            printf("ERROR SOCIO INVALIDO\n");
            mostrar_socio(&socio);
            fclose(p_arch_bin);
            fclose(p_arch_txt);
            return 0;
        }
        //mostrar_socio(&socio);
        fwrite(&socio, sizeof(T_Reg_Socio), 1, p_arch_bin);
    }
    fclose(p_arch_bin);
    fclose(p_arch_txt);
    return 1;
}

void mostrar_menu()
{
    printf("A - Dar de alta nuevo socio\n");
    printf("M - Modificar nombre y apellido\n");
    printf("B - Dar de baja a un socio\n");
    printf("L - Mostrar socios dados de baja\n");
    printf("V - Mostrar socios activos ordenados por nro de socio\n");
    printf("P - Mostrar los 10 socios con mayor atraso en la cuota\n");
    printf("S - Salir\n");
}

void verificar_arch_bin_socios()
{
    FILE *fp = fopen("socios.dat", "rb");
    T_Reg_Socio socio;
    printf("LEYENDO socios.dat\n");
    while(fread(&socio, sizeof(T_Reg_Socio), 1, fp))
    {
        mostrar_socio(&socio);
    }
    fclose(fp);
}
