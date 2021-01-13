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
        *tam = novo_tam;
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
                funcionario[i].codigo = novo_codigo;
            }
        }while(funcionario_existe != -1);
        /*if (procurarFuncionario(funcionario, funcionario[i].codigo, *contador) != -1){
            printf("Já existe um funcionário com o código %d."
                    "Por favor insira um código diferente", funcionario[i].codigo);
        }*/
        lerString(funcionario[i].nome, MAX_NOME, "Nome: ");
        lerString(funcionario[i].num_telefone, MAX_TELEFONE, "Nº telefone: ");
        funcionario[i].num_filhos = obterInt(0, 20, "Número de filhos: ");
        funcionario[i].cargo = obterInt(0, 2, "Cargo (0 - Funcionário   1 - Chefe   2 - Administrador): ");
        funcionario[i].estado_civil = obterInt(0, 3,
                "Estado Civil (0 - Solteiro   1 - Casado    2 - Divorciado   3 - Viuvo): ");

        printf("Data de nascimento\n");
        funcionario[i].nascimento.dia = obterInt(1, 31, "Dia: ");
        funcionario[i].nascimento.mes = obterInt(1, 12, "Mês: ");
        funcionario[i].nascimento.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de contratação\n");
        funcionario[i].contratado.dia = obterInt(1, 31, "Dia: ");
        funcionario[i].contratado.mes = obterInt(1, 12, "Mês: ");
        funcionario[i].contratado.ano = obterInt(1900, 2021, "Ano: ");


        printf("Data de despedimento\n");
        funcionario[i].despedido.dia = obterInt(0, 31, "Dia: ");
        funcionario[i].despedido.mes = obterInt(0, 12, "Mês: ");
        funcionario[i].despedido.ano = obterInt(0, 2021, "Ano: ");

        funcionario[i].salario_hora = obterFloat(0, 10000, "Valor salário/hora: ");
        funcionario[i].subs_alimentacao = obterFloat(0, 10000, "Valor subsídio de alimentação: ");

        funcionario[i].b_idade = obterFloat(0, 10000, "Bónus idade: ");
        funcionario[i].b_antiguidade = obterFloat(0, 10000, "Bónus antiguidade: ");
        funcionario[i].b_assiduidade = obterFloat(0, 10000, "Bónus assiduidade: ");
        funcionario[i].b_fds = obterFloat(0, 10000, "Bónus fim-de-semana: ");

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
                \nData nascimento\tData contratação\t Data despedimento\
                \nSalário/hora\tSubsídio alimentação\
                \n\n");
        for (int i = 0; i < contador; i++) {
            printf("%d\t%s\t%s\t%d\t%d\t%d\
                    \n%d-%d-%d\t%d-%d-%d\t%d-%d-%d\
                    \n%.2f\t%.2f\
                    \n\n",
                    funcionarios[i].codigo,
                    funcionarios[i].nome,
                    funcionarios[i].num_telefone,
                    funcionarios[i].num_filhos,
                    funcionarios[i].cargo,
                    funcionarios[i].estado_civil,
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
}

void editarFuncionario(Funcionario *funcionario, int contador){
    printf("-------- Remover Funcionário --------\n");
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