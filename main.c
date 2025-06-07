#include <stdio.h>
#include "aeroporto.h"
#include "grafo.h"


void menu();


int main() {
    GrafoVoos grafo;
    
    if (!grafo_inicializar(&grafo)) {
        printf("Erro ao inicializar grafo\n");
        return 1;
    }

    U8 opcao;

    do{
        menu();
        scanf("%hhu", &opcao);

        switch(opcao) {
            case 1: {
                I8 codigo[MAX_CODIGO];
                I8 cidade[MAX_CIDADE];
                printf("Digite o codigo do aeroporto (3 letras): ");
                scanf("%s", codigo);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", cidade);
                
                if (grafo_cadastrar_aeroporto(&grafo, codigo, cidade)) {
                    printf("Aeroporto cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar aeroporto.\n");
                }
                break;
            }
            case 2: {
                I8 codigo_origem[MAX_CODIGO];
                I8 codigo_destino[MAX_CODIGO];
                U32 numero_voo;
                
                printf("Digite o codigo do aeroporto de origem: ");
                scanf("%s", codigo_origem);
                printf("Digite o codigo do aeroporto de destino: ");
                scanf("%s", codigo_destino);
                printf("Digite o numero do voo: ");
                scanf("%u", &numero_voo);
                
                if (grafo_cadastrar_voo(&grafo, codigo_origem, codigo_destino, numero_voo)) {
                    printf("Voo cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar voo.\n");
                }
                break;
            }
            case 3: {
                U32 numero_voo;
                printf("Digite o numero do voo a ser removido: ");
                scanf("%u", &numero_voo);
                
                if (remove_voo(&grafo, numero_voo)) {
                    printf("Voo removido com sucesso!\n");
                } else {
                    printf("Erro ao remover voo.\n");
                }
                break;
            }
            case 4: {
                 // Implementar exibição de voos
                break;
            }
            case 5:
                // Implementar exibição de trajetos possíveis
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);
    
    // printf("=== Testando cadastro de aeroportos ===\n");
    // grafo_cadastrar_aeroporto(&grafo, "BSB", "Brasilia");
    // grafo_cadastrar_aeroporto(&grafo, "CNF", "Belo Horizonte");
    // grafo_cadastrar_aeroporto(&grafo, "GIG", "Rio de Janeiro");
    // grafo_cadastrar_aeroporto(&grafo, "GRU", "Sao Paulo");
    // grafo_cadastrar_aeroporto(&grafo, "SSA", "Salvador");
    
    // printf("Total de aeroportos: %u\n", grafo.num_aeroportos);
    
    // printf("=== Testando cadastro de voos ===\n");
    // grafo_cadastrar_voo(&grafo, "GRU", "BSB", 50);
    // grafo_cadastrar_voo(&grafo, "SSA", "CNF", 100);

    // printf("=== Testando remocao de voo ===\n");
    // remove_voo(&grafo, 50);

    grafo_destruir(&grafo);
    
    return 0;
}

void menu(){
    printf("\n=== Menu ===\n");
    printf("1. Cadastrar Aeroporto\n");
    printf("2. Cadastrar Voo\n");
    printf("3. Remover Voo\n");
    printf("4. Exibir Voos\n");
    printf("5. Exibir Possiveis trajetos entre aeroportos\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}
