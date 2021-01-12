#include <stdlib.h>
#include <stdio.h>
#include "funcionarios.h"
#include "input.h"

void expandirFuncionarios(){
    
}

void inserirFuncionarios(Funcionario *funcionario, int num_funcionarios, int *tam, int *contador) {
    if (*tam - *contador < num_funcionarios) {
        int novo_tam = *contador + num_funcionarios + (100 - ((*contador + num_funcionarios) % 100));
        funcionario = (Funcionario *) realloc(funcionario, novo_tam);
        *tam = novo_tam;
    }
    for(int i = 0; i < num_funcionarios; i++){
        printf("---- A adicionar funcionário %d de %d ----\n", i+1, num_funcionarios);
        funcionario[i].codigo = obterInt(1000, 32000, "Código: ");
        lerString(funcionario[i].nome, MAX_NOME, "Nome: ");
        lerString(funcionario[i].num_telefone, MAX_TELEFONE, "Nº telefone: ");
        funcionario[i].num_filhos = obterInt(0, 20, "Número de filhos: ");
        funcionario[i].cargo = obterInt(0, 2, "Cargo (0 - Funcionário   1 - Chefe   2 - Administrador): ");
        funcionario[i].estado_civil = obterInt(0, 3,
                "Estado Civil (0 - Solteiro   1 - Casado    2 - Divorciado   3 - Viuvo): ");
        
        printf("Data de nascimento\n");
        funcionario[i].nascimento.dia = obterInt(1, 31, "Dia: ");
        funcionario[i].nascimento.dia = obterInt(1, 12, "Mês: ");
        funcionario[i].nascimento.dia = obterInt(1900, 2021, "Ano: ");
    
        
        printf("Data de contratação\n");
        funcionario[i].contratado.dia = obterInt(1, 31, "Dia: ");
        funcionario[i].contratado.dia = obterInt(1, 12, "Mês: ");
        funcionario[i].contratado.dia = obterInt(1900, 2021, "Ano: ");
        
        
        printf("Data de despedimento\n");
        funcionario[i].despedido.dia = obterInt(0, 31, "Dia: ");
        funcionario[i].despedido.dia = obterInt(0, 12, "Mês: ");
        funcionario[i].despedido.dia = obterInt(0, 2021, "Ano: ");
    
        funcionario[i].salario_hora = obterFloat(0, 10000, "Valor salário/hora: ");
        funcionario[i].subs_alimentacao = obterFloat(0, 10000, "Valor subsídio de alimentação: ");
        
        funcionario[i].b_idade = obterFloat(0, 10000, "Bónus idade: ");
        funcionario[i].b_antiguidade = obterFloat(0, 10000, "Bónus antiguidade: ");
        funcionario[i].b_assiduidade = obterFloat(0, 10000, "Bónus assiduidade: ");
        funcionario[i].b_fds = obterFloat(0, 10000, "Bónus fim-de-semana: ");
        
        (*contador)++;
        
    }
    
    
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
    } else {
        printf("Ocorreu um erro ao gravar funcionários.");
    }
}

/**
 * 
 * @param funcionario
 * @param tam
 * @param contador
 */
void lerFuncionarios(Funcionario *funcionario, int *tam, int *contador) {
    FILE *fp = fopen("funcionarios.bin", "rb");
    if (fp == NULL) {
        perror("Não foi possível abrir o ficheiro.");
        exit(EXIT_FAILURE);
    }

    Funcionario *temporario = (Funcionario *) malloc(sizeof (Funcionario));
    int fim = 0;
    int num_func_lidos = 0;
    while (fim == 0) {
        //Funcionario temporario = fread(funcionario, sizeof(Funcionario), *contador, fp);
        if (fread(temporario, sizeof (Funcionario), 1, fp) != 1) {
            fim = 1;
        } else {
            num_func_lidos++;
            printf("Funcionario %d: %d %c\n", num_func_lidos, temporario->codigo, temporario->nome[0]);
            //inserirFuncionarios()
            
            funcionario[*contador + num_func_lidos] = *temporario;
        }
    }
    
    //int n_funcionarios_escritos = fread(funcionario, sizeof(Funcionario), *contador, fp);
    fclose(fp);
    free(temporario);
    temporario = NULL;
}

void listarFuncionarios(Funcionario *funcionarios, int contador) {
    printf("\n\n");
    if (contador == 0) {
        printf("Não há funcionarios registados.\n");
    } else {
        printf("Código\tNome\tNº telefone\t\n");
        for (int i = 0; i < contador; i++) {
            printf("%d\t%s\n", funcionarios[i].codigo, funcionarios[i].nome);
        }
    }
}
