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
    grafo_cadastrar_aeroporto(&grafo, "CNF", "Belo Horizonte");
    grafo_cadastrar_aeroporto(&grafo, "BSB", "Brasilia");
    grafo_cadastrar_aeroporto(&grafo, "cnf", "Belo Horizonte");
    
    printf("Total de aeroportos: %u\n", grafo.num_aeroportos);
    
    grafo_destruir(&grafo);
    
    return 0;
}