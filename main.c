#include <stdio.h>
#include <locale.h>
#include "aeroporto.h"
#include "grafo.h"

void menu();

int main() {
    setlocale(LC_ALL, "Portuguese");

    GrafoVoos grafo;
    
    if (!grafo_inicializar(&grafo)) {
        printf("Erro ao inicializar grafo\n");
        return 1;
    }

    printf("=== Inicializando aeroportos padrao ===\n");
    grafo_cadastrar_aeroporto(&grafo, "GRU", "Sao Paulo");
    grafo_cadastrar_aeroporto(&grafo, "BSB", "Brasilia");
    grafo_cadastrar_aeroporto(&grafo, "CNF", "Belo Horizonte");
    grafo_cadastrar_aeroporto(&grafo, "GIG", "Rio de Janeiro");
    grafo_cadastrar_aeroporto(&grafo, "SSA", "Salvador");
    grafo_cadastrar_aeroporto(&grafo, "FOR", "Fortaleza");
    printf("%u aeroportos inicializados!\n\n", grafo.num_aeroportos);

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
                printf("=== Exibindo voos cadastrados ===\n");
                exibir_voos(&grafo);
                break;
            }
            case 5:
                // Implementar exibição de trajetos possíveis
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

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
