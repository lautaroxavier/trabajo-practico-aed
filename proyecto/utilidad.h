#ifndef UTILIDAD_H_INCLUDED
#define UTILIDAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int Compare_Long(const void* N1,const void* N2);

void* Binary_Search(const void* Vec_Key, const void* Vec, unsigned N, unsigned Tam, unsigned Cmp_N, unsigned Cmp_Tam);
int Compare_Vector(void* N1,void* N2,unsigned N,unsigned Tam);

#endif // UTILIDAD_H_INCLUDED
