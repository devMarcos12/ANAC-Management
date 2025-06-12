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

    printf("=== Inicializando aeroportos conforme especificação ===\n");
    grafo_cadastrar_aeroporto(&grafo, "CNF", "Belo Horizonte");
    grafo_cadastrar_aeroporto(&grafo, "BSB", "Brasilia");
    grafo_cadastrar_aeroporto(&grafo, "GIG", "Rio de Janeiro");
    grafo_cadastrar_aeroporto(&grafo, "SSA", "Salvador");
    grafo_cadastrar_aeroporto(&grafo, "GRU", "Sao Paulo");
    printf("%u aeroportos inicializados!\n\n", grafo.num_aeroportos);

    printf("=== Inicializando voos por padrao ===\n");
    grafo_cadastrar_voo(&grafo, "GRU", "BSB", 50);
    grafo_cadastrar_voo(&grafo, "GIG", "CNF", 554);
    grafo_cadastrar_voo(&grafo, "GRU", "CNF", 102);
    grafo_cadastrar_voo(&grafo, "SSA", "CNF", 215);
    grafo_cadastrar_voo(&grafo, "CNF", "GIG", 555);
    grafo_cadastrar_voo(&grafo, "GRU", "GIG", 51);
    grafo_cadastrar_voo(&grafo, "CNF", "GRU", 101);
    grafo_cadastrar_voo(&grafo, "GIG", "GRU", 90);
    grafo_cadastrar_voo(&grafo, "BSB", "SSA", 107);
    grafo_cadastrar_voo(&grafo, "CNF", "SSA", 108);

    U8 opcao;

    do{
        menu();
        scanf("%hhu", &opcao);

        if (getchar() != '\n') {
            while (getchar() != '\n');
        }

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
                I8 codigo_aeroporto[MAX_CODIGO];
                printf("Digite o codigo do aeroporto: ");
                scanf("%s", codigo_aeroporto);
                exibir_voos_aeroporto(&grafo, codigo_aeroporto);
                break;
            }
            case 5: {
                I8 codigo_origem[MAX_CODIGO];
                I8 codigo_destino[MAX_CODIGO];
                printf("Digite o codigo do aeroporto de origem: ");
                scanf("%s", codigo_origem);
                printf("Digite o codigo do aeroporto de destino: ");
                scanf("%s", codigo_destino);
                grafo_listar_possiveis_trajetos(&grafo, codigo_origem, codigo_destino);
                break;
            }
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
