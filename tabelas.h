/**
 * 
 * 
 * @file tabelas.h
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Declaração das estruturas Irs e Ss
 * 
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
    float taxa_empresa;
    float taxa_trabalhador;
} Ss;


void lerIrs(Irs *tabela_irs);
void lerSegSoc(Ss *tabela_ss);

#ifdef __cplusplus
}
#endif

#endif /* TABELAS_H */

