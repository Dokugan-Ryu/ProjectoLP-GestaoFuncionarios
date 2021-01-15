/**
 * 
 * 
 * @file funcionarios.h
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Declaração das estruturas Data e Funcionario
 * 
 */

#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NOME 100+1
#define MAX_FUNCIONARIOS 100
#define MAX_TELEFONE 14+1

    /**
     * Estrutura para armazenar datas
     */
    typedef struct {
        int dia, mes, ano;
    } Data;

    /**
     * Estrutura para armazenar informação dos funcionários
     */
    typedef struct {
        int codigo; ///< Código do funcionário
        char nome[MAX_NOME]; ///< Nome
        char num_telefone[MAX_TELEFONE]; ///< Número de telefone
        int num_filhos; ///< Número de filhos
        enum {funcionario, chefe, administrador} cargo; ///< Cargo
        enum {solteiro, casado, divorciado, viuvo} estado_civil; ///< Estado Civil
        Data nascimento; ///< Data de nascimento
        Data contratado; ///< Data de contratação
        Data despedido; ///< Data de despedimento
        float salario_hora; ///< Salário/hora
        float subs_alimentacao;///< Subsídio de alimentação
        float b_idade; ///< Multiplicador do bónus de idade
        float b_antiguidade; ///< Multiplicador do bónus de antiguidade
        float b_assiduidade; ///< Multiplicador do bónus de assiduidade
        float b_fds; ///< Multiplicador do bónus de idade
    } Funcionario;

    void lerFuncionarios(Funcionario *funcionario, int *tam, int *contador);
    void gravarFuncionarios(Funcionario *funcionario, int *contador);
    void inserirFuncionarios(Funcionario *funcionario, int num_funcionarios,
            int *tam, int *contador);
    void listarFuncionarios(Funcionario *funcionarios, int contador);
    int procurarFuncionario(Funcionario *funcionario, int codigo, int contador);
    void removerFuncionario(Funcionario *funcionario, int *contador);
    void editarFuncionario(Funcionario *funcionario, int contador);
    void gerirFuncionarios(Funcionario *funcionario, int *tam_funcionario, int *contador_funcionario);
    
#ifdef __cplusplus
}
#endif

#endif /* FUNCIONARIOS_H */

