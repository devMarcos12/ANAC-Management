#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aeroporto.h"
#include "grafo.h"

boolean grafo_inicializar(GrafoVoos* grafo) {
    if (grafo == NULL) {
        return false;
    }
    
    grafo->aeroportos = NULL;
    grafo->matriz_adjacencia = NULL;
    grafo->num_aeroportos = 0;
    grafo->capacidade = 0;
    
    return true;
}

void grafo_destruir(GrafoVoos* grafo) {
    if (grafo == NULL) {
        return;
    }
    
    // Liberar memória dos aeroportos
    if (grafo->aeroportos != NULL) {
        free(grafo->aeroportos);
    }
    
    // Liberar memória da matriz de voos
    if (grafo->matriz_adjacencia != NULL) {
        for (U32 i = 0; i < grafo->num_aeroportos; i++) {
            free(grafo->matriz_adjacencia[i]);
        }
        free(grafo->matriz_adjacencia);
    }
    
    grafo->aeroportos = NULL;
    grafo->matriz_adjacencia = NULL;
    grafo->num_aeroportos = 0;
    grafo->capacidade = 0;
}

boolean grafo_cadastrar_aeroporto(GrafoVoos* grafo, const I8* codigo, const I8* cidade) {
    if (grafo == NULL || codigo == NULL || cidade == NULL) {
        return false;
    }

    // Verificar se o aeroporto já existe
    for (U32 i = 0; i < grafo->num_aeroportos; i++) {
        if (aeroporto_comparar_codigo(&grafo->aeroportos[i], codigo)) {
            return false;
        }
    }

    // Verificar se é necessário aumentar a capacidade
    if (grafo->num_aeroportos >= grafo->capacidade) {
        U32 nova_capacidade = (grafo->capacidade == 0) ? 1 : grafo->capacidade * 2;
        Aeroporto* novos_aeroportos = realloc(grafo->aeroportos, nova_capacidade * sizeof(Aeroporto));
        if (novos_aeroportos == NULL) {
            return false;
        }
        grafo->aeroportos = novos_aeroportos;
        
        Voo** nova_matriz = realloc(grafo->matriz_adjacencia, nova_capacidade * sizeof(Voo*));
        if (nova_matriz == NULL) {
            return false;
        }
        grafo->matriz_adjacencia = nova_matriz;

        for (U32 i = grafo->capacidade; i < nova_capacidade; i++) {
            grafo->matriz_adjacencia[i] = calloc(nova_capacidade, sizeof(Voo));
            if (grafo->matriz_adjacencia[i] == NULL) {
                return false;
            }
        }

        grafo->capacidade = nova_capacidade;
    }

    if (!criar_aeroporto(&grafo->aeroportos[grafo->num_aeroportos], codigo, cidade)) {
        return false;
    }
    
    grafo->num_aeroportos++;
    
    printf("Aeroporto %s - %s cadastrado com sucesso!\n", 
           grafo->aeroportos[grafo->num_aeroportos-1].codigo,
           grafo->aeroportos[grafo->num_aeroportos-1].cidade);
    
    return true;
}
