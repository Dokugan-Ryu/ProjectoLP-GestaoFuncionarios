#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NOME 100+1
#define MAX_FUNCIONARIOS 100
#define MAX_TELEFONE 14+1
    
    typedef struct {
        int dia, mes, ano;
    } Data;

    typedef struct {
        int codigo;
        char nome[MAX_NOME];
        char num_telefone[MAX_TELEFONE];
        int num_filhos;
        enum {funcionario, chefe, administrador} cargo;
        enum {solteiro, casado, divorciado, viuvo} estado_civil;
        Data nascimento, contratado, despedido;
        float salario_hora, subs_alimentacao;
        float b_idade, b_antiguidade, b_assiduidade, b_fds;      
    } Funcionario;

    void lerFuncionarios(Funcionario *funcionario, int *tam, int *contador);
    void gravarFuncionarios(Funcionario *funcionario, int *contador);
    void inserirFuncionarios(Funcionario *funcionario, int num_funcionarios,
            int *tam, int *contador);
    void listarFuncionarios(Funcionario *funcionarios, int contador);
    int procurarFuncionario(Funcionario *funcionario, int codigo, int contador);
    void removerFuncionario(Funcionario *funcionario, int *contador);
    void editarFuncionario(Funcionario *funcionario, int contador);
    
#ifdef __cplusplus
}
#endif

#endif /* FUNCIONARIOS_H */

