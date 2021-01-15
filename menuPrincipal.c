#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menuPrincipal.h"
#include "input.h"
#include "funcionarios.h"
#include "tabelas.h"
#include "salarios.h"

void menuPrincipal() {

    Funcionario *funcionario = (Funcionario*) malloc(sizeof (Funcionario) * MAX_FUNCIONARIOS);
    int tam_funcionario = MAX_FUNCIONARIOS;
    int contador_funcionario = 0;

    Irs *tabela_irs = (Irs *) (malloc(sizeof(Irs) * 60));
    Ss *tabela_ss = (Ss *) (malloc(sizeof(Ss) * 10));
    
    
    Salario *salarios = (Salario *) malloc(sizeof(Salario));
    int tam_salarios = 1;
    int cont_salarios = 0;
    int salarios_processados = 0;
    
    lerIrs(tabela_irs);
    lerSegSoc(tabela_ss);
    
    //processarSalarios(funcionario, tabela_irs, tabela_ss);
    //lerFicheiroMes(salarios, &tam_salarios, &cont_salarios);
    lerFicheiroMes(salarios, &tam_salarios, &cont_salarios);
    
    
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
                //gerirTabelas();
                break;
            case '3':
               // lerFicheiroMes(salarios, &tam_salarios, &cont_salarios);
                processarSalarios(funcionario, contador_funcionario, tabela_irs, tabela_ss, salarios, &cont_salarios, &tam_salarios, &salarios_processados);
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
    
    free(funcionario);
    free(tabela_irs);
    free(tabela_ss);
    free(salarios);
    funcionario=NULL;
    tabela_irs=NULL;
    tabela_ss=NULL;
    salarios=NULL;
}

