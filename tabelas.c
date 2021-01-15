/**
 * 
 * 
 * @file tabelas.c
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Tabelas IRS e SS
 * 
 * Leitura dos ficheiros relativos às tabelas contributivas de IRS e Segurança Social
 * 
 * @todo: incluir suporte para gestão das tabelas contributivas
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabelas.h"

/**
 * Lê o ficheiro "ss_taxas_contributivas.txt" e grava a informação nele contida na estrutura Ss
 * 
 * @param tabela_ss apontador para estrutura Ss
 */
void lerSegSoc(Ss *tabela_ss){
    FILE *fp = fopen("ss_taxas_contributivas.txt", "rb");
        if (fp == NULL) {
            perror("Não foi possível ler o ficheiro de tabelas de taxas contributivas da SS");
        } else {
            char c;
            char token[10];
            int linha = 0, coluna = 0;
            int contador = 0;
            do {
                c = fgetc(fp);
                if (c != '\r') {
                    if (c != ',') {
                        token[contador] = c;
                        contador++;
                    } else {
                        token[contador + 1] = '\0';

                        coluna++;
                        switch (coluna) {
                            case 1:
                                tabela_ss[linha].taxa_empresa = strtof(token, NULL);
                                break;
                            case 2:
                                tabela_ss[linha].taxa_trabalhador = strtof(token, NULL);
                                break;
                        }

                        for (int i = 0; i < 10; i++) {
                            token[i] = 0;
                        }

                        contador = 0;
                    }
                } else {

                    token[contador + 1] = '\0';

                    tabela_ss[linha].taxa_trabalhador = strtof(token, NULL);
                    linha++;

                    for (int i = 0; i < 10; i++) {
                        token[i] = 0;
                    }

                    contador = 0;
                    coluna = 0;

                    fgetc(fp);
                }
            } while (c != -1);
        }
}

/**
 * Lê os ficheiros "irs_nao_casado.txt", "irs_casado_um_titular.txt" e "irs_casado_dois_titulares.txt" e grava a informação neles contidas na estrutura Irs
 * 
 * @param tabela_ss apontador para estrutura Irs
 */
void lerIrs(Irs *tabela_irs) {
    char lista_ficheiros_irs[3][50] = {"irs_nao_casado.txt", "irs_casado_um_titular.txt", "irs_casado_dois_titulares.txt"};
    for (int ficheiros = 0; ficheiros < 3; ficheiros++) {
        FILE *fp = fopen(lista_ficheiros_irs[ficheiros], "rb");
        if (fp == NULL) {
            perror("Não foi possível ler o ficheiro de tabelas IRS");
        } else {
            char c;
            char token[10];
            int linha = 0, coluna = 0;
            int contador = 0;
            do {
                c = fgetc(fp);
                if (c != '\r') {
                    if (c != ',') {
                        token[contador] = c;
                        contador++;
                    } else {
                        token[contador + 1] = '\0';

                        coluna++;
                        switch (coluna) {
                            case 1:
                                tabela_irs[linha].salario = strtof(token, NULL);
                                break;
                            case 2:
                                tabela_irs[linha].zero_filhos[ficheiros] = strtof(token, NULL);
                                break;
                            case 3:
                                tabela_irs[linha].um_filhos[ficheiros] = strtof(token, NULL);
                                break;
                            case 4:
                                tabela_irs[linha].dois_filhos[ficheiros] = strtof(token, NULL);
                                break;
                            case 5:
                                tabela_irs[linha].tres_filhos[ficheiros] = strtof(token, NULL);
                                break;
                            case 6:
                                tabela_irs[linha].quatro_filhos[ficheiros] = strtof(token, NULL);
                                break;
                            case 7:
                                tabela_irs[linha].cincomais_filhos[ficheiros] = strtof(token, NULL);
                                break;
                        }


                        for (int i = 0; i < 10; i++) {
                            token[i] = 0;
                        }

                        contador = 0;
                    }
                } else {

                    token[contador + 1] = '\0';

                    tabela_irs[linha].cincomais_filhos[ficheiros] = strtof(token, NULL);
                    linha++;

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
    }
}

