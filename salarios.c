/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "salarios.h"
#include "funcionarios.h"
#include "tabelas.h"
#include "input.h"

void expandirSalarios(Salario *salarios, int *tam_salarios) {
    salarios = (Salario *) realloc(salarios, (*tam_salarios) + 50);
    (*tam_salarios) += 50;
}

int lerFicheiroMes(Salario *salarios, int *tam_salarios, int *cont_salarios) {
    int num_entradas_lidas = 0;

    char nome_ficheiro[50];
    lerString(nome_ficheiro, 50, "Nome do ficheiro a ler: ");

    FILE *fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        perror("Ficheiro não encontrado");
    } else {
        int mes, ano;
        obterInt(1, 12, "Mês: ");
        obterInt(1900, 2021, "Ano: ");

        char c = 0;
        char token[10];
        int coluna = 0;
        int contador = 0;
        do {
            if (tam_salarios == cont_salarios) {
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

                    //printf("\na %s %d", token, atoi(token));
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
                //printf("\nb %s %d", token, atoi(token));
                for (int i = 0; i < 10; i++) {
                    token[i] = 0;
                }

                contador = 0;
                coluna = 0;

                fgetc(fp);
            }
        } while (c != -1);
        //printf("entradas lidas %d", num_entradas_lidas);
        fclose(fp);
    }
    return num_entradas_lidas;
}

void processarSalarios(
        Funcionario *funcionarios, int cont_funcionarios,
        Irs *irs, Ss *seg_soc,
        Salario *salarios, int *cont_salarios, int *tam_salarios) {

}



