/**
 * 
 * 
 * @file salarios.c
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Processamento de salários
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "salarios.h"
#include "funcionarios.h"
#include "tabelas.h"
#include "input.h"


/**
 * Realocação da estrutura de salários
 * 
 * @param salarios apontador para a estrutura Salario
 * @param tam_salarios tamanho da estrutura Salario
 */
void expandirSalarios(Salario *salarios, int *tam_salarios) {
    salarios = (Salario *) realloc(salarios, (*tam_salarios) + 50);
    (*tam_salarios) += 50;
}


/**
 * Pede ao utilizador um nome de ficheiro, lê um ficheiro que contém dados relativos às horas trabalhadas num determinado mês, e armazena os valores lidos em Salarios
 * Chama expandirSalarios() quando a estrutura Salarios não suporta mais entradas
 * 
 * @param salarios apontador para a estrutura Salarios
 * @param tam_salarios tamanho da estrutura Salarios
 * @param cont_salarios número de entradas presentes na estrutura Salarios
 * @return número de entradas lidas e registadas
 */
int lerFicheiroMes(Salario *salarios, int *tam_salarios, int *cont_salarios) {
    int num_entradas_lidas = 0;

    char nome_ficheiro[50];
    lerString(nome_ficheiro, 50, "Nome do ficheiro a ler: ");

    FILE *fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        perror("Ficheiro não encontrado");
    } else {
        //        int mes, ano;
        //        obterInt(1, 12, "Mês: ");
        //        obterInt(1900, 2021, "Ano: ");

        char c = 0;
        char token[10]="";
        int coluna = 0;
        int contador = 0;
        do {
            printf("\n-------%d %d-------\n", *tam_salarios, *cont_salarios);
            printf("token %s\n", token);
            if (*tam_salarios == *cont_salarios) {
                expandirSalarios(salarios, tam_salarios);
            }

            c = fgetc(fp);
            //printf("%c", c);
            if (c != '\r') {
                if (c != ',') {
                    token[contador] = c;
                    contador++;
                } else {
                    token[contador] = '\0';

                    coluna++;
                    switch (coluna) {
                        case 1:
                            salarios[(*cont_salarios)].codigo = atoi(token);
                            break;
                        case 2:
                            salarios[(*cont_salarios)].dias = atoi(token);
                            break;
                        case 3:
                            salarios[(*cont_salarios)].meios_dias = atoi(token);
                            break;
                        case 4:
                            salarios[(*cont_salarios)].fds = atoi(token);
                            break;
                        case 5:
                            salarios[(*cont_salarios)].faltas = atoi(token);
                            break;
                    }

                    for (int i = 0; i < 10; i++) {
                        token[i] = 0;
                    }

                    contador = 0;
                }
            } else {

                token[contador + 1] = '\0';
                salarios[(*cont_salarios)].faltas = atoi(token);
                (*cont_salarios)++;
                num_entradas_lidas++;
                for (int i = 0; i < 10; i++) {
                    token[i] = 0;
                }

                contador = 0;
                coluna = 0;

                fgetc(fp);
            }
        } while (c != -1);
        
    }
    fclose(fp);
    return num_entradas_lidas;
}


/**
 * Faz o processamento de salários. Chama lerFicheiroMes e posteriormente calcula os valores salariais referentes a cada entrada
 * 
 * @param funcionarios apontador para estrutura Funcionario
 * @param cont_funcionarios número de entradas presentes na estrutura Funcionario
 * @param irs apontador para estrutura Irs
 * @param seg_soc apontador para estrutura Ss
 * @param salarios apontador para estrutura Salario
 * @param cont_salarios número de entradas presentes na estrutura Salario
 * @param tam_salarios tamanho da estrutura Salario
 * @param salarios_processados número de entradas da estrutura Salario que já foram processadas
 */
void processarSalarios(
        Funcionario *funcionarios, int cont_funcionarios,
        Irs *irs, Ss *seg_soc,
        Salario *salarios, int *cont_salarios, int *tam_salarios, int *salarios_processados) {

    int mes, ano;
    printf("Informação referente a\n");
    mes = obterInt(1, 12, "Mês (1-12): ");
    ano = obterInt(1900, 2021, "Ano (1900-2021): ");

    int entradas_lidas = lerFicheiroMes(salarios, tam_salarios, cont_salarios);
    if (entradas_lidas != 0) {
        for (int i = 0; i < entradas_lidas; i++) {

            int codigo = procurarFuncionario(
                    funcionarios,
                    salarios[(*salarios_processados) + i].codigo,
                    cont_funcionarios);
            if (codigo != -1) {
                float idade = (((12 - funcionarios[codigo].nascimento.mes) + mes) / 12) + ano - (funcionarios[codigo].nascimento.ano + 1);
                printf("\nnasc dia ano %d %d\n",funcionarios[codigo].nascimento.mes, funcionarios[codigo].nascimento.ano);
                printf("idade %f", idade);
                float antiguidade = (((12 - funcionarios[codigo].contratado.mes) + mes) / 12) + ano - (funcionarios[codigo].contratado.ano + 1);
                printf("antiguidade %f", antiguidade);


                salarios[(*salarios_processados) + i].b_idade = funcionarios[codigo].b_idade * idade;
                printf("b_idade %f", salarios[(*salarios_processados) + i].b_idade);
                salarios[(*salarios_processados) + i].b_antiguidade = funcionarios[codigo].b_antiguidade * antiguidade;
                printf("b_ant %f", salarios[(*salarios_processados) + i].b_antiguidade);
                if (salarios[(*salarios_processados) + i].faltas == 0) {
                    salarios[(*salarios_processados) + i].b_assiduidade = funcionarios[codigo].b_assiduidade;
                printf("bass %f", salarios[(*salarios_processados) + i].b_assiduidade);
                } else {
                    salarios[(*salarios_processados) + i].b_assiduidade = 0;
                }


                float salario_base = funcionarios[codigo].salario_hora * (
                        NUM_HORAS_TRABALHO_DIA * salarios[(*salarios_processados) + i].dias +
                        NUM_HORAS_TRABALHO_DIA * 0.5 * salarios[(*salarios_processados) + i].meios_dias +
                        NUM_HORAS_TRABALHO_DIA * 1.5 * salarios[(*salarios_processados) + i].fds);
                printf("\nSalario base %f\n", salario_base);

                salarios[(*salarios_processados) + i].salario_bruto =
                        salario_base +
                        salarios[(*salarios_processados) + i].b_idade +
                        salarios[(*salarios_processados) + i].b_antiguidade +
                        salarios[(*salarios_processados) + i].b_assiduidade;
                

                int taxa_irs;
                int categoria_irs;
                switch (funcionarios[codigo].estado_civil) {
                    case 0:
                        categoria_irs = 0;
                        break;
                    case 1:
                        categoria_irs = 1;
                        break;
                    default:
                        categoria_irs = 2;
                }

                for (int i = 0; i < 36; i++) {
                    if (salarios[(*salarios_processados) + i].salario_bruto <= irs[i].salario) {
                        switch (funcionarios[codigo].num_filhos) {
                            case 0:
                                taxa_irs = irs[i].zero_filhos[categoria_irs];
                                break;
                            case 1:
                                taxa_irs = irs[i].um_filhos[categoria_irs];
                                break;
                            case 2:
                                taxa_irs = irs[i].dois_filhos[categoria_irs];
                                break;
                            case 3:
                                taxa_irs = irs[i].tres_filhos[categoria_irs];
                                break;
                            case 4:
                                taxa_irs = irs[i].quatro_filhos[categoria_irs];
                                break;
                            default:
                                taxa_irs = irs[i].cincomais_filhos[categoria_irs];
                        }
                    } else {
                        taxa_irs = irs[36].zero_filhos[categoria_irs];
                    }
                }

                salarios[(*salarios_processados) + i].taxa_irs =
                        salarios[(*salarios_processados) + i].salario_bruto * taxa_irs;
                printf("\n irs %f\n", salarios[(*salarios_processados) + i].taxa_irs);

                /*float taxa_ss_func, taxa_ss_empresa;
                switch (funcionarios[codigo].cargo) {
                    case 0:
                        taxa_ss_empresa = seg_soc[0].taxa_empresa;
                        break;
                    case 1:
                        int categoria_irs = 1;
                        break;
                    default:
                        int categoria_irs = 2;
                }*/

                float taxa_ss_empresa = seg_soc[funcionarios[codigo].cargo].taxa_empresa;
                printf("\n ssempresa %f\n", taxa_ss_empresa);
                float taxa_ss_func = seg_soc[funcionarios[codigo].cargo].taxa_trabalhador;
                printf("\n ssfunc %f\n", taxa_ss_func);

                salarios[(*salarios_processados) + i].taxa_ss_empresa =
                        salarios[(*salarios_processados) + i].salario_bruto * (1 - taxa_ss_empresa);

                salarios[(*salarios_processados) + i].taxa_ss_funcionario =
                        salarios[(*salarios_processados) + i].salario_bruto * taxa_ss_func;

                salarios[(*salarios_processados) + i].salario_liquido =
                        salarios[(*salarios_processados) + i].salario_bruto -
                        salarios[(*salarios_processados) + i].taxa_irs -
                        salarios[(*salarios_processados) + i].taxa_ss_funcionario +
                        funcionarios[codigo].subs_alimentacao * (
                        salarios[(*salarios_processados) + i].dias + salarios[(*salarios_processados) + i].fds);

                
                printf("\n----- Salário do funcionário código %d processado -----\n", funcionarios[codigo].codigo);
                printf("Salário bruto: €%f\n", salarios[(*salarios_processados) + i].salario_bruto);
                printf("Subsídio alimentação: €%f\n", funcionarios[codigo].subs_alimentacao * (
                        salarios[(*salarios_processados) + i].dias + salarios[(*salarios_processados) + i].fds));
                printf("Salário líquido: €%f\n", salarios[(*salarios_processados) + i].salario_liquido);
                printf("Retenção IRS: €%f\n", salarios[(*salarios_processados) + i].taxa_irs);
                printf("Contribuição SegSoc do trabalhador: €%f\n", salarios[(*salarios_processados) + i].taxa_ss_funcionario);
                printf("Contribuição SegSoc da entidade empregadora: €%f\n", salarios[(*salarios_processados) + i].taxa_ss_empresa);


            } else {
                printf("\nFuncionário nao encontrado, ignorando entrada...\n");
            }
        }
    }

}



