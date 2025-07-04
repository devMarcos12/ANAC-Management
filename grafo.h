#ifndef GRAFO_H
#define GRAFO_H

#include "meustipos.h"
#include "aeroporto.h"

typedef struct {
    U32 numero_voo;
    boolean existe;
} Voo;

typedef struct {
    Aeroporto* aeroportos;      // Vetor dinâmico de aeroportos
    Voo** matriz_adjacencia;    // Matriz dinâmica de voos
    U32 num_aeroportos;         // Quantidade atual de aeroportos
    U32 capacidade;             // Capacidade máxima atual
} GrafoVoos;

boolean grafo_inicializar(GrafoVoos* grafo);
void grafo_destruir(GrafoVoos* grafo);
boolean grafo_cadastrar_aeroporto(GrafoVoos* grafo, const I8* codigo, const I8* cidade);
boolean grafo_cadastrar_voo(GrafoVoos* grafo, const I8* codigo_origem, 
    const I8* codigo_destino, U32 numero_voo);
I32 grafo_buscar_aeroporto(const GrafoVoos* grafo, const I8* codigo);
boolean remove_voo(GrafoVoos* grafo, U32 numero_voo);
void exibir_voos_aeroporto(const GrafoVoos* grafo, const I8* codigo_aeroporto);
void grafo_listar_possiveis_trajetos(const GrafoVoos* grafo, 
    const I8* codigo_origem, const I8* codigo_destino);
void dfs_trajetos(const GrafoVoos* grafo, 
    const U32 atual, const U32 destino, 
    boolean* visitados, U32* caminho, U32 profundidade);

#endif
