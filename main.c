#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void vetorizaocao(int *vetor, FILE *arq_caminho)
{
    char *token;
    char linha[100];
    int i = 0;

    while(!feof(arq_caminho)){
            int contador = 1;
            fgets(linha, 100, arq_caminho);
            token = strtok(linha, ",");
            while (token != NULL)
                {
                token = strtok (NULL, ",");
                contador++;

                if(contador == 3){
                    if(atoi(token) == 0){

                    }else{
                        vetor[i] = atoi(token);
                        i++;
                }
            }
        }
    }
}

void ascidades(int x, char *cidade, FILE *arquivo)
{
    int linha = 1;
    fseek(arquivo, 0, SEEK_SET);
    while(fgets(cidade, 50, arquivo) != NULL){
        if(linha == (x + 1)){
            break;
        }
        linha++;
    }
}

void trimString(char *str)
{
    char *token = strtok(str, "\t\n\r");
    if (token)
        strcpy(str, token);
}

int caminho_existe(int i, int j, FILE *arq_cidades)
{
    char cidade_i[50];
    char cidade_j[50];
    char virgula[2] = ",";

    ascidades(i, cidade_i, arq_cidades);
    ascidades(j, cidade_j, arq_cidades);

    trimString(cidade_i);
    trimString(cidade_j);

    char juntos[100] = "";
    strcat(juntos, cidade_i);
    strcat(juntos, virgula);
    strcat(juntos, cidade_j);

    char linha_caminho[50];

    FILE *arquivo;
    arquivo = fopen("Caminho.txt", "r");

    do{
        fgets(linha_caminho, 50, arquivo);
        if(strstr(linha_caminho, juntos) != NULL){
            return true;
            break;
        }
    }while(!feof(arquivo));

    return false;
}

int contar_linhas(FILE *arq)
{
    int linhas = 1;

    do{
        char caractere_no_momento = fgetc(arq);
        if(caractere_no_momento == '\n'){
            linhas++;
        }

    }while(!feof(arq));

    return linhas;
}

int main()
{

    FILE *arq_cidades;
    arq_cidades = fopen("Cidades.txt", "r");
    FILE *arq_caminho;
    arq_caminho = fopen("Caminho.txt", "r");

    int tamanho_da_matriz = contar_linhas(arq_cidades);
    int matriz[tamanho_da_matriz][tamanho_da_matriz];
    int vetor[200];
    int d = 0;

    vetorizaocao(vetor, arq_caminho);

    for(int i = 0; i < tamanho_da_matriz; i++){
        for(int j = 0; j < tamanho_da_matriz; j++){
            if(i == j){
                matriz[i][j] = 0;
            }else{
               if(caminho_existe(i, j, arq_cidades) == true){
                    matriz[i][j] = vetor[d];
                    d++;
                }else{
                    matriz[i][j] = 0;
                }
            }
        }
    }

    for(int i = 0; i < tamanho_da_matriz; i++){
        for(int j = 0; j < tamanho_da_matriz; j++){
            printf("|%*d|",4, matriz[i][j]);
        }
        printf("\n");
    }


    fclose(arq_caminho);
    fclose(arq_cidades);
    return 0;
}
