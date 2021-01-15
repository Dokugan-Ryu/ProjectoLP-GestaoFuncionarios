/**
 * 
 * 
 * @file salarios.h
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Declaração da estrutura Salario
 * 
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
    int mes; ///> Mês relativo aos dados inseridos
    int ano; ///> Ano relativo aos dados inseridos
    
    int codigo; ///> Código do funcionario
    
    int dias; ///> Número de dias trabalhados
    int meios_dias; ///> Número de meios dias trabalhados
    int fds; ///> Número de dias de fim-de-semana trabalhados
    int faltas; ///> Número de faltas
    
    float salario_bruto; ///> Valor do salário bruto
    float salario_liquido; ///> Valor do salário líquido
    float subs_alim; ///> Valor do subsídio de alimentação
    
    float b_idade;  ///> Valor do bónus de idade
    float b_antiguidade;  ///> Valor do bónus de antiguidade
    float b_assiduidade;  ///> Valor do bónus de assiduidade
    
    float taxa_ss_empresa; ///> Valor da contribuição da SS pago pela empresa
    float taxa_ss_funcionario; ///> Valor da contribuição da SS descontado do salário bruto
    float taxa_irs; ///> Valor da contribuição de IRS descontado do salário bruto
} Salario;


void expandirSalarios(Salario *salarios, int *tam_salarios);
int lerFicheiroMes(Salario *salarios, int *tam_salarios, int *cont_salarios);
void processarSalarios(Funcionario *funcionarios, int cont_funcionarios, Irs *irs, Ss *seg_soc, Salario *salarios, int *cont_salarios, int *tam_salarios, int *salarios_processados);



#ifdef __cplusplus
}
#endif

#endif /* SALARIOS_H */

