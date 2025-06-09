#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include "aeroporto.h"

boolean criar_aeroporto(Aeroporto *aeroporto, const I8* codigo, const I8* cidade) {
    if (aeroporto == NULL || codigo == NULL || cidade == NULL) {
        return false;
    }
    
    if (strlen(codigo) != 3) {
        printf("Erro: Codigo deve ter exatamente 3 caracteres.\n");
        return false;
    }
    
    if (strlen(cidade) >= MAX_CIDADE) {
        printf("Erro: Nome da cidade muito longo.\n");
        return false;
    }
    
    for (int i = 0; i < 3; i++) {
        if (!isalpha(codigo[i])) {
            printf("Erro: Codigo deve conter apenas letras.\n");
            return false;
        }
        aeroporto->codigo[i] = toupper(codigo[i]);
    }
    aeroporto->codigo[3] = '\0';
    
    strcpy(aeroporto->cidade, cidade);
    
    return true;
}

void exibir_aeroporto(const Aeroporto* aeroporto) {
    if (aeroporto != NULL) {
        printf("%s - %s", aeroporto->codigo, aeroporto->cidade);
    }
}

boolean aeroporto_comparar_codigo(const Aeroporto* aeroporto, const I8* codigo) {
    if (aeroporto == NULL || codigo == NULL) {
        return false;
    }
    
    I8 codigo_upper[MAX_CODIGO];
    for (int i = 0; i < 3 && codigo[i]; i++) {
        codigo_upper[i] = toupper(codigo[i]);
    }
    codigo_upper[3] = '\0';
    
    return strcmp(aeroporto->codigo, codigo_upper) == 0;
}