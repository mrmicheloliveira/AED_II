#include "buscaLargura.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gerarMatriz(int m, grafo *graf){
    int **mat;

    mat = (int**) malloc(m * sizeof(int*)); // alocando colunas
    for(int i = 0; i < m; i++){
        mat[i] = (int*) malloc(m * sizeof(int)); //alocando linhas
    }
    graf->matriz = mat;

    for(int i = 0; i < m; i++){ //inicializando matriz com 0
        for(int j = 0; j < m; j++){
            if(i == j){ // 1 sse i == j
                graf->matriz[i][j] = 1; 
            }
            else{
                graf->matriz[i][j] = 0;
            }
        }
    }
    return;
}
void imprimeMatriz(int m, grafo *graf){
    printf("----------MATRIZ----------\n ");
    printf(" ");
    for(int k = 0; k <  m; k++){ 
        printf("%c ",graf->map[k]);
    }
    printf("\n");
    for(int i = 0; i < m; i++){
        printf("%c ",graf->map[i]);
        for(int j = 0; j < m; j++){
            printf("%d ", graf->matriz[i][j]);
        }
        printf("\n");
    }
}
void lerArq(grafo *graf, char* nome_arq){

    FILE *arq;
    arq = fopen(nome_arq, "r");
    if(arq != NULL){
        char buffer[20];
        fgets(buffer, 19, arq);
        char *vertices = strtok(buffer," "); 
        char *arestas = strtok(NULL, "\n"); 

        char lista[atoi(vertices)];
        for(int i = 0; i < sizeof(lista); i++){ // add vertices
            fscanf(arq,"%c",&lista[i]);
            if(lista[i] == '\n'){
                i--;
            } 
        }
        graf->vertices = atoi(vertices);
        graf->arestas = atoi(arestas);
        strcpy(graf->map , lista);
        gerarMatriz(atoi(vertices), graf);
        char aux[20];

        while(fgets(aux, 19, arq) != NULL){
            int aux1, aux2;

            for(int i = 0; i < sizeof(lista); i++){ 
                if(aux[0] == lista[i]){
                    aux1 = i; 
                }
                if(aux[1] == lista[i]){
                    aux2 = i;
                }            
            }
            insereMatriz(aux1, aux2, graf);     
        }
        fclose(arq);
        imprimeMatriz(graf->vertices, graf);
    }
    else{
        printf("Arquivo de leitura inexistente!\n");
        exit(0);
    }
}
void insereMatriz(int aux1, int aux2, grafo *graf){

    for(int i = 0; i < graf->vertices; i++){
        for(int j = 0; j < graf->vertices; j++){
            if(i == aux1 && j == aux2){ 
                graf->matriz[i][j] = 1;
            }
            if(j == aux1 && i == aux2){ 
                graf->matriz[i][j] = 1;
            }
        }
    }
    return;
}

fila* push(fila *fila,char v){
    struct fila *aux = fila;
    if(aux == NULL){
        struct fila *novo = malloc(sizeof(fila));
        novo->v = v;
        novo->prox = NULL;
        return novo;
    }
    else{
        struct fila *novo = malloc(sizeof(fila));
        novo->v = v;
        novo->prox = fila;
        return novo;
    }
}
fila* pop(fila *fila){
    if(fila != NULL){
        char v = fila->v;
        if(fila->prox != NULL){
            fila = fila->prox;
        }
        else{
            fila = NULL;
        }
    return fila;
    }
}
void buscaLargura(grafo *graf, char origem){
    fila *f = NULL; //init filas
    fila *adjacentes = NULL;
    int tam = graf->vertices;
    int visitado[tam]; 
    for(int i = 0;i < graf->vertices; i++){ //inicializando lista de visitados
        visitado[i] = 0; 
    }

    for(int i = 0; i < graf->vertices; i++){ //Procurar início
        if(origem == graf->map[i]){
            f = push(f, graf->map[i]);
            visitado[i] = 1; //visitado[i] = 1; 
            break;            
        }
    }    


    while(f != NULL){  
        char nomeVertice = f->v;
        f = pop(f); 
        for(int i = 0; i < graf->vertices; i++){ //busca o caractere
            if(nomeVertice == graf->map[i]){ 
                // busca os adjacentes
                for(int j = 0; j < graf->vertices ; j++){
                    if(graf->matriz[i][j] == 1 && j != i ){                        

                        if(visitado[j] == 0){
                            adjacentes = push(adjacentes, graf->map[j]);
                        }                                                    
                    }
                }
            }
        }         
        while(adjacentes != NULL){ 
            char adjVertice = adjacentes->v;
            adjacentes = pop(adjacentes);
            for(int i = 0; i < graf->vertices; i++){ //busca vertice
                if(adjVertice == graf->map[i]){
                    if(visitado[i] == 0){
                        f = push(f,graf->map[i]);
                        printf(" -> %c", adjVertice);
                        visitado[i] = 1; //visitado[i] = 1;
                    }                    
                }
            }            
        }
    }
    printf("\n");
}