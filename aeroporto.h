#ifndef AEROPORTO_H
#define AEROPORTO_H

#include "meustipos.h"

#define MAX_CODIGO 4    // 3 chars + \0
#define MAX_CIDADE 50

typedef struct aeroporto {
    U8 codigo[4];
    U8 cidade[50];
} Aeroporto;

boolean criar_aeroporto(Aeroporto *aeroporto, const I8* codigo, const I8* cidade);
void exibir_aeroporto(const Aeroporto* aeroporto);
boolean aeroporto_comparar_codigo(const Aeroporto* aeroporto, const char* codigo);

#endif
