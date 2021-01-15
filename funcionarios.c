#include <stdlib.h>
#include <stdio.h>
#include "funcionarios.h"
#include "input.h"

void expandirFuncionarios(Funcionario *funcionario, int *tam, int acrescimo) {
    funcionario = (Funcionario *) realloc(funcionario, (*tam) + acrescimo);
    *tam += acrescimo;
}

void inserirFuncionarios(Funcionario *funcionario, int num_funcionarios, int *tam, int *contador) {
    if (*tam - *contador < num_funcionarios) {
        int novo_tam = *contador + num_funcionarios + (100 - ((*contador + num_funcionarios) % 100));
        funcionario = (Funcionario *) realloc(funcionario, novo_tam);
        (*tam) = novo_tam;
    }
    for (int i = 0; i < num_funcionarios; i++) {
        printf("---- A adicionar funcionário %d de %d ----\n", i + 1, num_funcionarios);
        //funcionario[i].codigo = obterInt(1000, 32000, "Código: ");
        int funcionario_existe;
        do{
            int novo_codigo = obterInt(1000, 32000, "Código: ");
            funcionario_existe = procurarFuncionario(funcionario, novo_codigo, *contador);
            if (funcionario_existe != -1){
                printf("Já existe um funcionário com o código %d. "
                        "Por favor insira um código diferente. \n", novo_codigo);
                printf("Prima [Enter] para continuar...\n");
                cleanInputBuffer();
            } else {
                funcionario[(*contador)+i].codigo = novo_codigo;
            }
        }while(funcionario_existe != -1);
        /*if (procurarFuncionario(funcionario, funcionario[i].codigo, *contador) != -1){
            printf("Já existe um funcionário com o código %d."
                    "Por favor insira um código diferente", funcionario[i].codigo);
        }*/
        lerString(funcionario[(*contador)+i].nome, MAX_NOME, "Nome: ");
        lerString(funcionario[(*contador)+i].num_telefone, MAX_TELEFONE, "Nº telefone: ");
        funcionario[(*contador)+i].num_filhos = obterInt(0, 20, "Número de filhos: ");
        funcionario[(*contador)+i].cargo = obterInt(0, 2, "Cargo (0 - Funcionário   1 - Chefe   2 - Administrador): ");
        funcionario[(*contador)+i].estado_civil = obterInt(0, 3,
                "Estado Civil (0 - Solteiro   1 - Casado    2 - Divorciado   3 - Viuvo): ");

        printf("Data de nascimento\n");
        funcionario[(*contador)+i].nascimento.dia = obterInt(1, 31, "Dia: ");
        int mes = 0, fail = 0;
        do {
            mes = obterInt(1, 12, "Mês: ");
            if (funcionario[(*contador)+i].nascimento.dia > 28 && mes == 2){
                printf("Mês inválido, por favor tente novamente.");
                fail = 1;
            } else {
                if (funcionario[(*contador)+i].nascimento.dia > 30 &&
                        (mes == 4 || mes == 6 || mes == 9 || mes == 11) ){
                     printf("Mês inválido, por favor tente novamente.");
                fail = 1;
                } else {
                    fail = 0;
                }
            }
        } while (fail == 1);
        funcionario[(*contador)+i].nascimento.mes = mes;
        funcionario[(*contador)+i].nascimento.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de contratação\n");
        funcionario[(*contador)+i].contratado.dia = obterInt(1, 31, "Dia: ");
        do {
            mes = obterInt(1, 12, "Mês: ");
            if (funcionario[(*contador)+i].contratado.dia > 28 && mes == 2){
                printf("Mês inválido, por favor tente novamente.");
                fail = 1;
            } else {
                if (funcionario[(*contador)+i].contratado.dia > 30 &&
                        (mes == 4 || mes == 6 || mes == 9 || mes == 11) ){
                     printf("Mês inválido, por favor tente novamente.");
                fail = 1;
                } else {
                    fail = 0;
                }
            }
        } while (fail == 1);
        funcionario[(*contador)+i].contratado.mes = mes;
        funcionario[(*contador)+i].contratado.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de despedimento\n");
        funcionario[(*contador)+i].despedido.dia = obterInt(0, 31, "Dia: ");
        do {
            mes = obterInt(0, 12, "Mês: ");
            if (( funcionario[(*contador)+i].despedido.dia > 28 && mes == 2) &&  funcionario[(*contador)+i].despedido.dia != 0){
                printf("Mês inválido, por favor tente novamente.");
                fail = 1;
            } else {
                if ( (funcionario[(*contador)+i].despedido.dia > 30 &&
                        (mes == 4 || mes == 6 || mes == 9 || mes == 11) ) &&  funcionario[(*contador)+i].despedido.dia != 0){
                     printf("Mês inválido, por favor tente novamente.");
                fail = 1;
                } else {
                    fail = 0;
                }
            }
        } while (fail == 1);
        funcionario[(*contador)+i].despedido.mes = mes;
        funcionario[(*contador)+i].despedido.ano = obterInt(0, 2021, "Ano: ");

        funcionario[(*contador)+i].salario_hora = obterFloat(0, 10000, "Valor salário/hora: ");
        funcionario[(*contador)+i].subs_alimentacao = obterFloat(0, 10000, "Valor subsídio de alimentação: ");

        funcionario[(*contador)+i].b_idade = obterFloat(0, 10000, "Bónus idade: ");
        funcionario[(*contador)+i].b_antiguidade = obterFloat(0, 10000, "Bónus antiguidade: ");
        funcionario[(*contador)+i].b_assiduidade = obterFloat(0, 10000, "Bónus assiduidade: ");
        funcionario[(*contador)+i].b_fds = 0.5;

        (*contador)++;
    }
    printf("\nForam adicionados %d funcionário.\nPrima [Enter] para continuar...", num_funcionarios);
    cleanInputBuffer();
    system("clear");
}

void gravarFuncionarios(Funcionario *funcionario, int *contador) {
    FILE *fp = fopen("funcionarios.bin", "wb");
    if (fp == NULL) {
        perror("Não foi possível abrir o ficheiro.");
        exit(EXIT_FAILURE);
    }
    int n_funcionarios_escritos = fwrite(funcionario, sizeof (Funcionario), *contador, fp);
    fclose(fp);
    if (n_funcionarios_escritos == *contador) {
        printf("Foram gravados %d funcionários.", n_funcionarios_escritos);
        printf("\nPrima [Enter] para continuar...");
        cleanInputBuffer();
        system("clear");
    } else {
        printf("Ocorreu um erro ao gravar funcionários.");
    }
}

void lerFuncionarios(Funcionario *funcionario, int *tam, int *contador) {
    FILE *fp = fopen("funcionarios.bin", "rb");
    if (fp == NULL) {
        perror("Não foi possível abrir o ficheiro.");
        exit(EXIT_FAILURE);
    }

    int tam_temp = 100;
    Funcionario *temporario = (Funcionario *) malloc(sizeof (Funcionario) * tam_temp);

    int fim = 0;
    int contador_temp = 0;
    while (fim == 0) {
        if (contador_temp == tam_temp) {
            expandirFuncionarios(temporario, &tam_temp, 100);
        }
        if (fread((temporario + contador_temp), sizeof (Funcionario), 1, fp) == 1) {
            contador_temp++;
        } else {
            fim = 1;
        }
    }
    for (int i = 0; i < contador_temp; i++) {
        funcionario[(*contador) + i] = temporario[i];
    }
    (*contador) += contador_temp;
    
    free(temporario);
    temporario=NULL;
    
    printf("Foram lidos %d funcionários.\nPrima [Enter] para continuar...", contador_temp);
    cleanInputBuffer();
    system("clear");
}

void listarFuncionarios(Funcionario *funcionarios, int contador) {
    printf("\n");
    if (contador == 0) {
        printf("Não há funcionarios registados.\n\n");
    } else {
        printf("Código\tNome\t\tNº telefone\tNº filhos\tCargo\tEstado Civil\
                \nData nascimento\tData contratação\tData despedimento\
\tSalário/hora\tSubsídio alimentação\n\n\n");
        for (int i = 0; i < contador; i++) {
            printf("%d\t%s\t%s\t%d\t",
                    funcionarios[i].codigo,
                    funcionarios[i].nome,
                    funcionarios[i].num_telefone,
                    funcionarios[i].num_filhos);
            switch (funcionarios[i].estado_civil){
                case 0:
                    printf("Solteiro");
                    break;
                case 1:
                    printf("Casado");
                    break;
                case 2:
                    printf("Divorciado");
                    break;
                case 3:
                    printf("Viúvo");
                    break;
            }
            printf("\t");
            switch (funcionarios[i].cargo){
                case 0:
                    printf("Funcionário");
                    break;
                case 1:
                    printf("Chefe");
                    break;
                case 2:
                    printf("Administrador");
                    break;
            }
            printf("\n%d-%d-%d\t%d-%d-%d\t%d-%d-%d\t%.2f\t%.2f\
                    \n\n",
                    funcionarios[i].nascimento.dia,
                    funcionarios[i].nascimento.mes,
                    funcionarios[i].nascimento.ano,
                    funcionarios[i].contratado.dia,
                    funcionarios[i].contratado.mes,
                    funcionarios[i].contratado.ano,
                    funcionarios[i].despedido.dia,
                    funcionarios[i].despedido.mes,
                    funcionarios[i].despedido.ano,
                    funcionarios[i].salario_hora,
                    funcionarios[i].subs_alimentacao);
        }
    }
    printf("Prima [Enter] para continuar...");
    cleanInputBuffer();
    system("clear");
}

int procurarFuncionario(Funcionario *funcionario, int codigo, int contador){
    if (codigo == -1){
        codigo = obterInt(1000, 32000, "Código: ");
    }    
    printf("A procurar funcionário com o código %d...\n", codigo);
    for (int i = 0; i<contador; i++){
        if (funcionario[i].codigo == codigo){
            printf ("Funcionario encontrado\n");
            listarFuncionarios((funcionario+i), 1);
            return i;
        }
    }
    return -1;
}

void removerFuncionario(Funcionario *funcionario, int *contador){
    printf("-------- Remover Funcionário --------\n");
    int codigo = obterInt(1000, 32000, "Codigo: ");
    int indice_funcionario = procurarFuncionario(funcionario, codigo, *contador);
    if (indice_funcionario == -1){
        printf("Funcionário não encontrado. Por favor tente novamente.\n");
    } else {
        for (indice_funcionario; indice_funcionario < (*contador); indice_funcionario++){
            funcionario[indice_funcionario] = funcionario[indice_funcionario+1];
        }
        (*contador)--;
        printf("O funcionário com o código %d foi removido.\n", codigo);
    }
    printf("Prima [Enter] para continuar...");
    cleanInputBuffer();
    system("clear");
}

void editarFuncionario(Funcionario *funcionario, int contador){
    printf("-------- Editar Funcionário --------\n");
    int codigo = obterInt(1000, 32000, "Codigo: ");
    int indice_funcionario = procurarFuncionario(funcionario, codigo, contador);
    if (indice_funcionario == -1){
        printf("Funcionário não encontrado. Por favor tente novamente.\n");
    } else {
        
        lerString(funcionario[indice_funcionario].nome, MAX_NOME, "Nome: ");
        lerString(funcionario[indice_funcionario].num_telefone, MAX_TELEFONE, "Nº telefone: ");
        funcionario[indice_funcionario].num_filhos = obterInt(0, 20, "Número de filhos: ");
        funcionario[indice_funcionario].cargo = obterInt(0, 2, "Cargo (0 - Funcionário   1 - Chefe   2 - Administrador): ");
        funcionario[indice_funcionario].estado_civil = obterInt(0, 3,
                "Estado Civil (0 - Solteiro   1 - Casado    2 - Divorciado   3 - Viuvo): ");

        printf("Data de nascimento\n");
        funcionario[indice_funcionario].nascimento.dia = obterInt(1, 31, "Dia: ");
        funcionario[indice_funcionario].nascimento.mes = obterInt(1, 12, "Mês: ");
        funcionario[indice_funcionario].nascimento.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de contratação\n");
        funcionario[indice_funcionario].contratado.dia = obterInt(1, 31, "Dia: ");
        funcionario[indice_funcionario].contratado.mes = obterInt(1, 12, "Mês: ");
        funcionario[indice_funcionario].contratado.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de despedimento\n");
        funcionario[indice_funcionario].despedido.dia = obterInt(0, 31, "Dia: ");
        funcionario[indice_funcionario].despedido.mes = obterInt(0, 12, "Mês: ");
        funcionario[indice_funcionario].despedido.ano = obterInt(0, 2021, "Ano: ");

        funcionario[indice_funcionario].salario_hora = obterFloat(0, 10000, "Valor salário/hora: ");
        funcionario[indice_funcionario].subs_alimentacao = obterFloat(0, 10000, "Valor subsídio de alimentação: ");

        funcionario[indice_funcionario].b_idade = obterFloat(0, 10000, "Bónus idade: ");
        funcionario[indice_funcionario].b_antiguidade = obterFloat(0, 10000, "Bónus antiguidade: ");
        funcionario[indice_funcionario].b_assiduidade = obterFloat(0, 10000, "Bónus assiduidade: ");
        funcionario[indice_funcionario].b_fds = obterFloat(0, 10000, "Bónus fim-de-semana: ");

        
        printf("O funcionário com o código %d foi editado.\n", codigo);
    }
    printf("Prima [Enter] para continuar...");
    cleanInputBuffer();
}

void gerirFuncionarios(Funcionario *funcionario, int *tam_funcionario, int *contador_funcionario){
    char selecao = 0;
    do {
        printf("\n");
        printf("-----------------------\n");
        printf("  Gestão Funcionários\n");
        printf("-----------------------\n");
        printf("1-Inserir funcionários\n");
        printf("2-Editar funcionário\n");
        printf("3-Remover funcionário\n");
        printf("4-Procurar funcionário\n");
        printf("5-Listar funcionários\n");
        printf("6-Carregar funcionários\n");
        printf("7-Gravar funcionários\n");
        printf("0-Sair\n");

        printf("\nEscolha: ");
        selecao = getchar();
        cleanInputBuffer();
        system("clear");

        switch (selecao) {
            case '1':
                inserirFuncionarios(
                        funcionario,
                        obterInt(1, 1000, "Número de funcionários a adicionar: "),
                        tam_funcionario,
                        contador_funcionario);
                break;
            case '2':
                editarFuncionario(funcionario, *contador_funcionario);
                break;
            case '3':
                removerFuncionario(funcionario, contador_funcionario);
                break;
            case '4':
                printf("%d", procurarFuncionario(funcionario, -1, *contador_funcionario));
                break;
            case '5':
                listarFuncionarios(funcionario, *contador_funcionario);
                break;
            case '6':
                lerFuncionarios(funcionario, tam_funcionario, contador_funcionario);
                break;
            case '7':
                gravarFuncionarios(funcionario, contador_funcionario);
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