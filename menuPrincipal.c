#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menuPrincipal.h"
#include "funcionarios.h"
#include "input.h"



void menuPrincipal() {

    char nome[] = "eraumavezumgatomaltesquequeriasermaisalto";
    Funcionario *funcionario = (Funcionario*) malloc(sizeof (Funcionario) * MAX_FUNCIONARIOS);
    int tam_funcionario = MAX_FUNCIONARIOS;
    int contador_funcionario = 0;


/*
    inserirFuncionarios(funcionario, 20, &tam_funcionario, &contador_funcionario);
    getchar();

    gravarFuncionarios(funcionario, &contador_funcionario);
    getchar();

    lerFuncionarios(funcionario, &tam_funcionario, &contador_funcionario);
    getchar();
*/
    
    char selecao = 0;
    do {
        printf("\n");
        printf("--------------\n");
        printf("MAIN MENU\n");
        printf("--------------\n");
        printf("1-Gerir funcionários\n");
        printf("2-Gerir tabelas\n");
        printf("3-Processar Salários\n");
        printf("4-Importar/Exportar dados\n");
        printf("5-Gerir funcionários\n");
        printf("0-Sair\n");

        printf("\nEscolha: ");
        selecao = getchar();
        cleanInputBuffer();

        switch (selecao) {
            case '1':
                inserirFuncionarios(funcionario, obterInt(1, 1000, "Número de funcionários a adicionar: "), &tam_funcionario, &contador_funcionario);
                break;
            case '2':
                gravarFuncionarios(funcionario, &contador_funcionario);
                break;
            case '3':
                lerFuncionarios(funcionario, &tam_funcionario, &contador_funcionario);
                break;
            case '4':
                listarFuncionarios(funcionario, contador_funcionario);
                //obterChar("Prima [Enter] para continuar...");
                printf("Prima [Enter] para continuar...");
                cleanInputBuffer();
                
                break;
            case '5':
                break;
            case '0':
                break;
            default:
                printf("\nSeleção inválida. Por favor tente novamente.\n"
                        "Prima [Enter] para continuar...");
                cleanInputBuffer();
        }

    } while (selecao != '0');
}