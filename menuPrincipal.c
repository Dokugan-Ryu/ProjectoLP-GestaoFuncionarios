#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menuPrincipal.h"
#include "funcionarios.h"
#include "input.h"

void menuPrincipal() {

    Funcionario *funcionario = (Funcionario*) malloc(sizeof (Funcionario) * MAX_FUNCIONARIOS);
    int tam_funcionario = MAX_FUNCIONARIOS;
    int contador_funcionario = 0;


    char selecao = 0;
    do {
        printf("\n");
        printf("------------------\n");
        printf("  MENU PRINCIPAL\n");
        printf("------------------\n");
        printf("1-Gerir funcionários\n");
        printf("2-Gerir tabelas\n");
        printf("3-Processar Salários\n");
        printf("4-Importar/Exportar dados\n");
        printf("5-Gerir funcionários\n");
        printf("0-Sair\n");

        printf("\nEscolha: ");
        selecao = getchar();
        cleanInputBuffer();
        system("clear");

        switch (selecao) {
            case '1':
                gerirFuncionarios(funcionario, &tam_funcionario, &contador_funcionario);
                break;
            case '2':
                gravarFuncionarios(funcionario, &contador_funcionario);
                break;
            case '3':
                lerFuncionarios(funcionario, &tam_funcionario, &contador_funcionario);
                break;
            case '4':
                listarFuncionarios(funcionario, contador_funcionario);
                break;
            case '5':
                printf("%d", procurarFuncionario(funcionario, -1, contador_funcionario));
                break;
            case '6':
                removerFuncionario(funcionario, &contador_funcionario);
                break;
            case '7':
                editarFuncionario(funcionario, contador_funcionario);
                break;
            case '0':
                break;
            default:
                printf("\nSeleção inválida. Por favor tente novamente.\n"
                        "Prima [Enter] para continuar...");
                cleanInputBuffer();
                system("clear");
        }
    } while (selecao != '0');
}