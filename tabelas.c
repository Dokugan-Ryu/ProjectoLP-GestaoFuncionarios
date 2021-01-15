/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabelas.h"

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
                                strcpy(tabela_ss[linha].cargo, token);
                                break;
                            case 2:
                                tabela_ss[linha].taxa_empresa = strtof(token, NULL);
                                break;
                            case 3:
                                tabela_ss[linha].taxa_trabalhador = strtof(token, NULL);
                                break;

                        }

                        //printf("\na %s %f", token, strtof(token, NULL));
                        for (int i = 0; i < 10; i++) {
                            token[i] = 0;
                        }

                        contador = 0;
                    }
                } else {

                    token[contador + 1] = '\0';

                    tabela_ss[linha].taxa_trabalhador = strtof(token, NULL);
                    linha++;
                    //printf("\nb %s %f", token, strtof(token, NULL));
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

                        //printf("\na %s %f", token, strtof(token, NULL));
                        for (int i = 0; i < 10; i++) {
                            token[i] = 0;
                        }

                        contador = 0;
                    }
                } else {

                    token[contador + 1] = '\0';

                    tabela_irs[linha].cincomais_filhos[ficheiros] = strtof(token, NULL);
                    linha++;
                    //printf("\nb %s %f", token, strtof(token, NULL));
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
}