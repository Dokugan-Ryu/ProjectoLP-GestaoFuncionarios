/**
 * 
 * 
 * @file input.c
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * @brief Gestão de input do utilizador
 * 
 */

#include <stdio.h>
#include <string.h>

#define VALOR_INVALIDO "O valor inserido é inválido."
/**
 * Limpa o buffer de entrada
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


/**
 * Pede um valor inteiro ao utilizador e valida o seu input
 * 
 * @param minValor
 * @param maxValor
 * @param msg mensagem a apresentar ao utilizador
 * @return número inteiro lido
 */
int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


/**
 * Pede um valor decimal ao utilizador e valida o seu input
 * 
 * @param minValor
 * @param maxValor
 * @param msg mensagem a apresentar ao utilizador
 * @return número decimal lido
 */
float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Pede um caractere ao utilizador
 * 
 * @param msg mensagem a apresentar ao utilizador
 * @return Caractere lido
 */
char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

/**
 * Pede uma string ao utilizador
 * 
 * @param apontador para string destino
 * @param tamanho número máximo de caracteres a ler
 * @param msg mensagem a apresentar ao utilizador
 */
void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}