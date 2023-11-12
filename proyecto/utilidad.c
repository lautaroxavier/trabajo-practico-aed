#include "utilidad.h"


int Compare_Long(const void* N1,const void* N2)
{
    return (int)(*(long*)N1 - *(long*)N2);
}


void* Binary_Search(const void* Vec_Key, const void* Vec, unsigned N, unsigned Tam, unsigned Cmp_N, unsigned Cmp_Tam)
{

    int Med = N / 2;

    void* Elemento_Med = Vec + (Med*Tam);

    int CMP = Compare_Vector(Vec_Key, Elemento_Med,Cmp_N,Cmp_Tam);

    if(CMP == 0)
        return Elemento_Med;

    else if(Med == 0)
        return NULL;

    else if(CMP < 0)
        return Binary_Search(Vec_Key,Vec,Med,Tam,Cmp_N,Cmp_Tam);

    else
        return Binary_Search(Vec_Key,(char*)Vec+(Tam*(Med+1)), N-Med-1,Tam,Cmp_N,Cmp_Tam);
}

int Compare_Vector(void* N1,void* N2,unsigned N,unsigned Tam)
{
    int I;

    for(I=0; I<N; I++)
    {
        if(*(unsigned*)N1>*(unsigned*)N2)
            return 1;
        if(*(unsigned*)N1<*(unsigned*)N2)
            return -1;
        N1+=Tam;
        N2+=Tam;
    }

    return 0;
}

