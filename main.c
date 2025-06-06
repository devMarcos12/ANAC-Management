#include <stdio.h>
#include "aeroporto.h"
#include "grafo.h"

int main() {
    GrafoVoos grafo;
    
    if (!grafo_inicializar(&grafo)) {
        printf("Erro ao inicializar grafo\n");
        return 1;
    }
    
    printf("=== Testando cadastro de aeroportos ===\n");
    grafo_cadastrar_aeroporto(&grafo, "BSB", "Brasilia");
    grafo_cadastrar_aeroporto(&grafo, "CNF", "Belo Horizonte");
    grafo_cadastrar_aeroporto(&grafo, "GIG", "Rio de Janeiro");
    grafo_cadastrar_aeroporto(&grafo, "GRU", "Sao Paulo");
    grafo_cadastrar_aeroporto(&grafo, "SSA", "Salvador");
    
    printf("Total de aeroportos: %u\n", grafo.num_aeroportos);
    
    printf("=== Testando cadastro de voos ===\n");
    grafo_cadastrar_voo(&grafo, "GRU", "BSB", 50);
    grafo_cadastrar_voo(&grafo, "SSA", "CNF", 100);

    printf("=== Testando remoção de voo ===\n");
    remove_voo(&grafo, 50);

    grafo_destruir(&grafo);
    
    return 0;
}
