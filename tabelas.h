/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tabelas.h
 * Author: Alpha
 *
 * Created on January 14, 2021, 5:33 PM
 */

#ifndef TABELAS_H
#define TABELAS_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
    float salario;
    float zero_filhos[3];
    float um_filhos[3];
    float dois_filhos[3];
    float tres_filhos[3];
    float quatro_filhos[3];
    float cincomais_filhos[3];
} Irs;

typedef struct {
    char cargo[20];
    float taxa_empresa;
    float taxa_trabalhador;
} Ss;

void lerIrs(Irs *tabela_irs);
void lerSegSoc(Ss *tabela_ss);

#ifdef __cplusplus
}
#endif

#endif /* TABELAS_H */

