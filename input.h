/**
 * 
 * 
 * @file input.h
 * @author Diogo Queiroz
 * @date 15 Jan 2021
 * 
 */

#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

    void cleanInputBuffer();

    int obterInt(int minValor, int maxValor, char *msg);
    float obterFloat(float minValor, float maxValor, char *msg);
    char obterChar(char *msg);
    void lerString(char *string, unsigned int tamanho, char *msg);


#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */

