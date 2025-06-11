#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aeroporto.h"
#include "grafo.h"

static U8 contador_de_trajetos = 0;

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

        for (U32 i = 0; i < grafo->capacidade; i++) {
            Voo* nova_linha = realloc(grafo->matriz_adjacencia[i], nova_capacidade * sizeof(Voo));
            if (nova_linha == NULL) {
                return false;
            }
            grafo->matriz_adjacencia[i] = nova_linha;
            
            for (U32 j = grafo->capacidade; j < nova_capacidade; j++) {
                grafo->matriz_adjacencia[i][j].existe = false;
                grafo->matriz_adjacencia[i][j].numero_voo = 0;
            }
        }

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

I32 grafo_buscar_aeroporto(const GrafoVoos* grafo, const I8* codigo){
    if (grafo == NULL || codigo == NULL) {
        return -1;
    }

    for (U32 i = 0; i < grafo->num_aeroportos; i++) {
        if (aeroporto_comparar_codigo(&grafo->aeroportos[i], codigo)) {
            return i; // Retorna o índice do aeroporto encontrado
        }
    }

    return -1; // Retorna -1 se o aeroporto não for encontrado
}

boolean grafo_cadastrar_voo(GrafoVoos* grafo, const I8* codigo_origem, const I8* codigo_destino, U32 numero_voo){
    if (grafo == NULL || codigo_origem == NULL || codigo_destino == NULL){
        return false;
    }

    if (numero_voo == 0){
        printf("Erro: Numero do voo deve ser maior que zero.\n");
        return false;
    }

    if (grafo->num_aeroportos == 0) {
        printf("Erro: Nenhum aeroporto cadastrado.\n");
        return false;
    }

    I32 idx_origem = grafo_buscar_aeroporto(grafo, codigo_origem);
    I32 idx_destino = grafo_buscar_aeroporto(grafo, codigo_destino);
    
    if (idx_origem == -1 || idx_destino == -1) {
        printf("Erro: Aeroporto de origem ou destino nao encontrado.\n");
        return false;
    }

    if (idx_destino == idx_origem){
        printf("Erro: Aeroporto de origem e destino nao podem ser iguais.\n");
        return false;
    }
    
    //verificar se já existe um voo nessa rota
    if (grafo->matriz_adjacencia[idx_origem][idx_destino].existe) {
        printf("Erro: Ja existe um voo cadastrado de %s para %s.\n", codigo_origem, codigo_destino);
        return false;
    }

    //verificar se o numero de voo já existe
    for (U32 i = 0; i < grafo->num_aeroportos; i++) {
        for(U32 j = 0; j < grafo->num_aeroportos; j++) {
            if (grafo->matriz_adjacencia[i][j].existe && 
                grafo->matriz_adjacencia[i][j].numero_voo == numero_voo) {
                printf("Erro: Numero do voo %u ja cadastrado.\n", numero_voo);
                return false;
            }
        }
    }

    //cadastrando o voo
    grafo->matriz_adjacencia[idx_origem][idx_destino].numero_voo = numero_voo;
    grafo->matriz_adjacencia[idx_origem][idx_destino].existe = true;
    printf("Voo %u cadastrado de %s para %s com sucesso!\n", 
           numero_voo, codigo_origem, codigo_destino);

    return true;
}

boolean remove_voo(GrafoVoos* grafo, U32 numero_voo){
    if (grafo == NULL || numero_voo == 0 || grafo->num_aeroportos == 0) {
        return false;
    }

    for (U32 i=0; i < grafo->num_aeroportos; i++){
        for (U32 j=0; j < grafo->num_aeroportos; j++){
            if (grafo->matriz_adjacencia[i][j].existe && 
                grafo->matriz_adjacencia[i][j].numero_voo == numero_voo) {
                    
                    grafo->matriz_adjacencia[i][j].existe = false;
                    grafo->matriz_adjacencia[i][j].numero_voo = 0;
                    printf("Voo %u removido: %s -> %s\n", 
                           numero_voo, 
                           grafo->aeroportos[i].codigo, 
                           grafo->aeroportos[j].codigo);

                    return true;
            }

        }
    }

    printf("Erro: Voo %u nao encontrado.\n", numero_voo);
    return false;

}

void exibir_voos(const GrafoVoos* grafo) {
    if (grafo == NULL || grafo->num_aeroportos == 0) {
        printf("Nenhum voo cadastrado.\n");
        return;
    }

    for (U32 i = 0; i < grafo->num_aeroportos; i++) {
        for (U32 j = 0; j < grafo->num_aeroportos; j++) {
            if (grafo->matriz_adjacencia[i][j].existe) {
                printf("Voo %u: %s -> %s\n", 
                       grafo->matriz_adjacencia[i][j].numero_voo, 
                       grafo->aeroportos[i].codigo, 
                       grafo->aeroportos[j].codigo);
            }
        }
    }
}

void grafo_listar_possiveis_trajetos(const GrafoVoos* grafo, 
    const I8* codigo_origem, const I8* codigo_destino){
    if (grafo == NULL || codigo_origem == NULL || codigo_destino == NULL) {
        printf("Erro: Grafo ou codigos invalidos.\n");
        return;
    }

    I32 idx_origem = grafo_buscar_aeroporto(grafo, codigo_origem);
    I32 idx_destino = grafo_buscar_aeroporto(grafo, codigo_destino);

    if (idx_origem == -1 || idx_destino == -1) {
        printf("\nErro: Aeroporto de origem ou destino nao encontrado.\n");
        return;
    }

    if (idx_destino == idx_origem){
        printf("\nErro: Aeroporto de origem e destino nao podem ser iguais.\n");
        return;   
    }

    boolean *visitados = calloc(grafo->num_aeroportos, sizeof(boolean));
    U32 *caminho = malloc (grafo->num_aeroportos * sizeof(U32));

    if (visitados == NULL || caminho == NULL){
        printf("\nErro: Falha na alocação de memoria.\n");
        return;
    }

    printf("\n=== Possiveis trajetos de %s para %s ===\n\n", codigo_origem, codigo_destino);

    dfs_trajetos(grafo, idx_origem, idx_destino, visitados, caminho, 0);

    if (contador_de_trajetos == 0) {
        printf("Nenhum trajeto encontrado de %s para %s.\n", 
               codigo_origem, codigo_destino);
        return;
    } else {
        printf("\nTotal de trajetos encontrados: %u\n", contador_de_trajetos);
    }

    free(visitados);
    free(caminho);
        
}

void dfs_trajetos(const GrafoVoos* grafo, 
    const U32 atual, const U32 destino, 
    boolean* visitados, U32* caminho, U32 profundidade){

    visitados[atual] = true;
    caminho[profundidade] = atual;

    if (atual == destino){
        contador_de_trajetos++;
        //imprimir o caminho encontrado
        printf("Trajeto %u: ", contador_de_trajetos);
        for (U32 i = 0; i <= profundidade; i++) {
            printf("%s ", grafo->aeroportos[caminho[i]].codigo);

            if(i < profundidade){
                U32 voo_numero = grafo->matriz_adjacencia[caminho[i]][caminho[i+1]].numero_voo;
                printf(" --(voo: %u)--> ", voo_numero);
            }

        }
        printf(" (%u escala%s)\n", profundidade, 
            (profundidade) == 1 ? "" : "s");
    }else {
        for (U32 i = 0; i < grafo->num_aeroportos; i++) {
            if (grafo->matriz_adjacencia[atual][i].existe && !visitados[i]) {
                dfs_trajetos(grafo, i, destino, visitados, caminho, profundidade + 1);
            }
        }
    }
    visitados[atual] = false;

}
