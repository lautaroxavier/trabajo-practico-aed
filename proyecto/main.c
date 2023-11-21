#include "main.h"

int main()
{
    //primera_parte();
    //verificar_arch_bin_socios();
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
    FILE *fp = fopen(ARCH_BIN_SOCIOS, "rb+");
    if (!fp)
    {
        printf("ERROR: no se pudo abrir el archivo de socios.\n");
        return;
    }
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
                dar_de_alta_socio(&indice_socios_activos, fp);
                presioneParaContinuar();
                break;
            case 'M':
                modificar_nombre_socio(&indice_socios_activos, fp);
                presioneParaContinuar();
                break;
            case 'B':
                dar_de_baja_socio(&indice_socios_activos, fp);
                presioneParaContinuar();
                break;
            case 'L':
                mostrar_inactivos(&indice_socios_activos, fp);
                presioneParaContinuar();
                break;
            case 'V':
                mostrar_socios_activos(&indice_socios_activos, fp);
                presioneParaContinuar();
                break;
            case 'P':
                mostrar_socios_atrasados(&indice_socios_activos, fp);
                presioneParaContinuar();
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
    fclose(fp);
}

void dar_de_alta_socio(T_Indice *pIndice, FILE *p_arch)
{
    T_Reg_Socio nuevo_socio;
    unsigned reg = -1;
    //indice_recorrer(pIndice, mostrarClaveYReg, stdout);
    printf("Ingrese el numero de socio: ");
    fflush(stdin);
    scanf("%lu", (unsigned long*)&(nuevo_socio.nro_socio));
    if(indice_buscar(pIndice, &nuevo_socio.nro_socio, &reg))
    {
        printf("El socio ya está activo\n");
        return;
    }
    if(buscar_socio_archivo(&nuevo_socio, &reg, p_arch))
    {
        printf("Socio inactivo. El socio será dado de alta.\n");
    }
    else
    {
        pedir_nombre(nuevo_socio.nya);
        pedir_dni(&nuevo_socio.dni);
        pedir_fecha(&nuevo_socio.fecha_nac, "Ingrese fecha de nacimiento: ");
        pedir_genero(&nuevo_socio.sexo);
        pedir_fecha(&nuevo_socio.fecha_afiliacion, "Ingrese fecha de afiliacion: ");
        pedir_categoria(nuevo_socio.categoria);
        pedir_fecha(&nuevo_socio.fecha_ultima_cuota_paga, "Ingrese fecha de ultima cuota paga: ");
    }
    nuevo_socio.estado = 'A';
    nuevo_socio.fecha_baja.anio = 0;
    nuevo_socio.fecha_baja.mes = 0;
    nuevo_socio.fecha_baja.dia = 0;
    grabar_socio_archivo(&nuevo_socio, &reg, p_arch);
    indice_insertar(pIndice, &nuevo_socio.nro_socio, reg);
    printf("Socio nro %lu agregado con exito!!!\n", (unsigned long)nuevo_socio.nro_socio);
}

void modificar_nombre_socio(T_Indice *pIndice, FILE *p_arch)
{
    T_Reg_Socio socio_reg;
    unsigned nro_reg = -1;
    printf("Ingrese el numero de socio: ");
    fflush(stdin);
    scanf("%lu", (unsigned long *)&socio_reg.nro_socio);
    if(!indice_buscar(pIndice, &socio_reg.nro_socio, &nro_reg))
    {
        printf("ERROR: el socio no esta activo.\n");
        return;
    }
    buscar_socio_archivo(&socio_reg, &nro_reg, p_arch);
    pedir_nombre(socio_reg.nya);
    grabar_socio_archivo(&socio_reg, &nro_reg, p_arch);
    printf("Modificando nombre de socio...\n");
}

void dar_de_baja_socio(T_Indice *pIndice, FILE *p_arch)
{
    // IMPLEMENTAR!!!!
    // buscar el socio en el indice
    // si no esta en el indice, buscarlo  secuencialmente en el archivo de socios como inactivo e informarlo
    // si esta en el indice, modificar el registro en el archivo y sacarlo del indice
    T_Reg_Socio socio_reg;
    unsigned nro_reg = -1;
    printf("Ingrese el numero de socio: ");
    fflush(stdin);
    scanf("%lu", (unsigned long *)&socio_reg.nro_socio);
    if(!indice_eliminar(pIndice, &socio_reg.nro_socio, &nro_reg))
    {
        printf("ERROR: el socio no esta activo.\n");
        return;
    }
    buscar_socio_archivo(&socio_reg, &nro_reg, p_arch);
    socio_reg.estado = 'I';
    socio_reg.fecha_baja.anio = 2023;
    socio_reg.fecha_baja.mes = 11;
    socio_reg.fecha_baja.dia = 21;
    grabar_socio_archivo(&socio_reg, &nro_reg, p_arch);
    printf("El socio ha sido dado de baja...\n");
}

void mostrar_inactivos(T_Indice *pIndice, FILE *p_arch)
{
    // IMPLEMENTAR!!!
    // buscar secuencialmente en el archivo los socios que esten inactivos
    // e ir insertandolos ordenados por nro de socio en una lista
    // mostrar la lista
    T_Reg_Socio socio_tmp;
    printf("MOSTRANDO SOCIOS INACTIVOS...\n");
    fseek(p_arch, 0L, SEEK_SET);
    while(fread(&socio_tmp, sizeof(T_Reg_Socio), 1, p_arch))
    {
        if(socio_tmp.estado == 'I')
        {
            mostrar_socio(&socio_tmp);
        }
    }
}

void mostrar_socios_activos(T_Indice *pIndice, FILE *p_arch)
{
    // IMPLEMENTAR!!!
    // recorrer el indice y mostrar los datos de cada socio
    printf("MOSTRANDO SOCIOS ACTIVOS...\n");
    indice_recorrer(pIndice, leer_nesimo_reg_arch, p_arch);
}

void mostrar_socios_atrasados(T_Indice *pIndice, FILE *p_arch)
{
    // IMPLEMENTAR!!!
    // recorrer los socios activos usando el indice y buscandolos en el archivo
    // insertar los socios en una lista ordenados por fecha de ultimo pago
    // si la lista tiene mas de 10 elementos, eliminar el ultimo
    // cuando se termina de recorrer el indice se muestran los 10 registros que quedaron en la lista
    tLista socios_atrasados;
    params_atrasados params;
    params.fp = p_arch;
    params.cant = 0;
    params.p_lista = &socios_atrasados;
    crearLista(&socios_atrasados);
    indice_recorrer(pIndice, ordenar_socios_atrasados, &params);
    printf("MOSTRANDO LOS 10 SOCIOS MAS ATRASADOS CON LA CUOTA...\n");
    mapLista(&socios_atrasados, mostrar_socio2, NULL);
    vaciarLista(&socios_atrasados);
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
        if (strcmpi(categoria, categorias[i]) == 0)
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

// buscar el socio en el archivo a partir del campo nro de socio
// y copia la informacion del resto de los campos
int buscar_socio_archivo(T_Reg_Socio *p_socio, unsigned *nro_reg, FILE *p_arch)
{
    unsigned orden = 0;
    T_Reg_Socio socio_tmp;
    fseek(p_arch, 0, SEEK_SET);
    while (fread(&socio_tmp, sizeof(T_Reg_Socio), 1, p_arch))
    {
        if (p_socio->nro_socio == socio_tmp.nro_socio)
        {
            memcpy(p_socio, &socio_tmp, sizeof(T_Reg_Socio));
            *nro_reg = orden;
            return 1;
        }
        orden++;
    }
    return 0;
}

// SI EL NUMERO DE REGISTRO ES MAYOR O IGUAL A CERO, PISAR EL REGISTRO EN ESA POSICION
// SI NO, GRABAR EL REGISTRO AL FINAL Y COPIAR EL NUMERO DE REGISTRO
int grabar_socio_archivo(T_Reg_Socio *p_socio, unsigned *p_reg, FILE *p_arch)
{
    unsigned cant_reg;
    fseek(p_arch, 0L, SEEK_END);
    cant_reg = (unsigned)(ftell(p_arch) / sizeof(T_Reg_Socio));
    if (*p_reg < cant_reg)
    {
        fseek(p_arch, (*p_reg) * sizeof(T_Reg_Socio), SEEK_SET);
        fwrite(p_socio, sizeof(T_Reg_Socio), 1, p_arch);
        return 1;
    }
    // PONER AL FINAL
    fseek(p_arch, 0, SEEK_END);
    fwrite(p_socio, sizeof(T_Reg_Socio), 1, p_arch);
    *p_reg = cant_reg;
    return 1;
}

void pedir_nombre(char *p_dest)
{
    printf("Ingrese el nombre y apellido: ");
    fflush(stdin);
    fgets(p_dest, 60, stdin);
    p_dest[strcspn(p_dest, "\n")] = '\0';
}

void pedir_dni(long *p_dni)
{
    char buffer[100];
    char *ptr;
    printf("Ingrese el DNI: ");
    fflush(stdin);
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    *p_dni = strtol(buffer, &ptr, 10);
}

void pedir_genero(char *p_genero)
{
    do {
        printf("Ingrese el sexo: ");
        fflush(stdin);
        scanf("%c", p_genero);
        *p_genero = toupper(*p_genero);
    }
    while (*p_genero != 'M' && *p_genero != 'F' && *p_genero != 'O');
}

void pedir_categoria(char *s)
{
    do {
        printf("Ingrese la categoria del socio: ");
        fflush(stdin);
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
    }
    while(!validar_categoria(s));
}

void pedir_fecha(T_Fecha *p_fecha, char *s)
{
    printf("%s", s);
    printf("Ingrese dia: ");
    fflush(stdin);
    scanf("%d", &(p_fecha->dia));
    printf("Ingrese mes: ");
    fflush(stdin);
    scanf("%d", &(p_fecha->mes));
    printf("Ingrese anio: ");
    fflush(stdin);
    scanf("%d", &(p_fecha->anio));
}

void leer_nesimo_reg_arch(const void *p_clave, unsigned nro_reg, void *pf)
{
    T_Reg_Socio socio_tmp;
    fseek((FILE*)pf, nro_reg * sizeof(T_Reg_Socio), SEEK_SET);
    fread(&socio_tmp, sizeof(T_Reg_Socio), 1, (FILE*)pf);
    mostrar_socio(&socio_tmp);
}

int cmp_socio_fecha_baja(const void *r1, const void *r2)
{
    T_Reg_Socio *psocio1 = (T_Reg_Socio *)r1;
    T_Reg_Socio *psocio2 = (T_Reg_Socio *)r2;
    T_Fecha *fecha1 = &(psocio1->fecha_ultima_cuota_paga);
    T_Fecha *fecha2 = &(psocio2->fecha_ultima_cuota_paga);
    int anio, mes;
    anio = fecha1->anio - fecha2->anio;
    if (anio != 0)
    {
        return anio;
    }
    mes = fecha1->mes - fecha2->mes;
    if (mes != 0)
    {
        return mes;
    }
    return fecha1->dia - fecha2->dia;
}

void ordenar_socios_atrasados(const void *p, unsigned nro_reg, void *params)
{
    params_atrasados *parametros = (params_atrasados*)params;
    tLista *p_lista = parametros->p_lista;
    int *cant = &parametros->cant;
    FILE *pf = parametros->fp;
    T_Reg_Socio *new_socio = malloc(sizeof(T_Reg_Socio));
    fseek(pf, nro_reg * sizeof(T_Reg_Socio), SEEK_SET);
    fread(new_socio, sizeof(T_Reg_Socio), 1, pf);
    insertarOrdenadoConDuplicado(p_lista, new_socio, sizeof(T_Reg_Socio), cmp_socio_fecha_baja);
    *cant = (*cant) + 1;
    if((*cant) > 10)
    {
        sacarUltimo(p_lista, new_socio, sizeof(T_Reg_Socio));
        *cant = (*cant) - 1;
    }
    free(new_socio);
}

void mostrar_socio2(void *p_reg_socio, void *params)
{
    mostrar_socio((T_Reg_Socio*)p_reg_socio);
}

void presioneParaContinuar()
{
    printf("Presione Enter para continuar...\n");
    fflush(stdin);
    getchar();
}
