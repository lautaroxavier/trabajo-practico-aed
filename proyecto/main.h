#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "indice.h"

#define ARCH_BIN_SOCIOS "socios.dat"
#define ARCH_INDICE "socios.idx"

int Compare_Long(const void* N1,const void* N2)
{
    return (int)(*(long*)N1 - *(long*)N2);
}

typedef struct
{
    tLista *p_lista;
    int cant;
    FILE *fp;
}
params_atrasados;

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

void presioneParaContinuar();

int validar_categoria(char *categoria);

int validar_socio(T_Reg_Socio *p_socio);

void mostrar_socio(T_Reg_Socio *p_socio);

void trozar_campos_socio(char *src, T_Reg_Socio *p_socio);

int crear_arch_bin();

void mostrar_menu();

void verificar_arch_bin_socios();

void dar_de_alta_socio(T_Indice *pIndice, FILE *p_arch);

void modificar_nombre_socio(T_Indice *pIndice, FILE *p_arch);

void dar_de_baja_socio(T_Indice *pIndice, FILE *p_arch);

void mostrar_inactivos(T_Indice *pIndice, FILE *p_arch);

void mostrar_socios_activos(T_Indice *pIndice, FILE *p_arch);

void mostrar_socios_atrasados(T_Indice *pIndice, FILE *p_arch);

void primera_parte();

void segunda_parte();

int indice_asignar(T_Indice *p_indice, const char *path);

int buscar_socio_archivo(T_Reg_Socio *, unsigned *nro_reg, FILE *p_arch);

int grabar_socio_archivo(T_Reg_Socio *, unsigned *, FILE *);

void pedir_nombre(char *);

void pedir_dni(long *);

void pedir_genero(char *p_genero);

void pedir_categoria(char *);

void pedir_fecha(T_Fecha *, char *s);

void leer_nesimo_reg_arch(const void *, unsigned, void *);

int cmp_socio_fecha_baja(const void *, const void *);

void ordenar_socios_atrasados(const void *, unsigned, void *);

void mostrar_socio2(void *, void *);

int validar_fecha(T_Fecha*);

int es_bisiesto(int anio);

#endif // MAIN_H_INCLUDED
