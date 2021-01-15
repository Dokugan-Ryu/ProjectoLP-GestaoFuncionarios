/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   salarios.h
 * Author: Alpha
 *
 * Created on January 15, 2021, 1:32 AM
 */

#ifndef SALARIOS_H
#define SALARIOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "funcionarios.h"
#include "tabelas.h"
    
    
#define NUM_HORAS_TRABALHO_DIA 8    

typedef struct {
    int mes, ano;
    int codigo;
    int dias, meios_dias, fds, faltas;
    float salario_bruto, salario_liquido, subs_alim;
    float b_idade, b_antiguidade, b_assiduidade;
    float taxa_ss_empresa, taxa_ss_funcionario, taxa_irs;
} Salario;

void expandirSalarios(Salario *salarios, int *tam_salarios);
int lerFicheiroMes(Salario *salarios, int *tam_salarios, int *cont_salarios);
void processarSalarios(Funcionario *funcionarios, int cont_funcionarios, Irs *irs, Ss *seg_soc, Salario *salarios, int *cont_salarios, int *tam_salarios, int *salarios_processados);



#ifdef __cplusplus
}
#endif

#endif /* SALARIOS_H */

