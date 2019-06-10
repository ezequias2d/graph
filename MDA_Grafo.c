#include "MDA_Grafo.h"
#include <malloc.h>
#include <stdlib.h>

/**
 * @brief Search for the position of the vertex, in the matrix, of the list of links
 * 
 * @param linkList LinkList
 * @param size Size of LinkList
 * @param vertex Vertex to search
 * @return size32_t Position
 */
size32_t MDA_Grafo_searchVertexPosition(char* linkList, size32_t size, char vertex){
    for(size32_t i = 0; i < size; i++){
        if(linkList[i] == vertex){
            return i;
        }
    }
    printf("ERROR 1 - Vertex '%c' not found\n", vertex);
    exit(EXIT_FAILURE);
}

MDA_Grafo* MDA_Grafo_load(const char* uri){
    MDA_Grafo* grafo = (MDA_Grafo*)malloc(sizeof(MDA_Grafo));
    FILE* file;
    bool aux = false;
    char edge1 = ' ';
    char edge2 = ' ';
    size32_t edge1index;
    size32_t edge2index;
    long verticesPos;
    
    file = fopen(uri, "r");
    fscanf(file, "%u", &grafo->vertices);
    fscanf(file, "%u", &grafo->edges);

    grafo->linkList = (char*) malloc(sizeof(char) * grafo->vertices);

    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->linkList[i] = ' ';
        while(grafo->linkList[i] == ' ' || grafo->linkList[i] == '\n'){
            fscanf(file, "%c", &grafo->linkList[i]);
        }
    }

    grafo->matrix = (bool**)malloc(sizeof(bool*) * (grafo->vertices));
    
    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->matrix[i] = (bool*)malloc(sizeof(bool) * (grafo->vertices));
        for(size32_t j = 0; j < grafo->vertices; j++){
            if(i == j){
                aux = true;
            } else {
                aux = false;
            }
            grafo->matrix[i][j] = aux;
        }
    }

    for(size32_t i = 0; i < grafo->edges; i++){
        long oldPos = ftell(file);
        long newPos;
        while(edge1 == ' ' || edge1 == '\n'){
            fscanf(file, "%c", &edge1);
            newPos = ftell(file);
            if(newPos == oldPos){
                //nao consegue ler mais o arquivo(Can not read file)
                printf("ERROR 3 - Can not read file\nThe number of edges is wrong in the file header\nCorrect number: %u\nPlease fix\n", i);
                exit(EXIT_FAILURE);
            }
        }
        fscanf(file, "%c", &edge2);

        edge1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, edge1);
        edge2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, edge2);

        edge1 = ' ';
        edge2 = ' ';

        if(edge1index >= grafo->vertices || edge2index >= grafo->vertices){
            printf("ERROR 2 - Something wrong is not right.\nThe return of the position of the vertex in the matrix exceeds the limits of the same.\nEdge1Index: %u | Edge2Index: %u | Vertices: %u\n", edge1index, edge2index, grafo->vertices);
            exit(EXIT_FAILURE);
        }

        grafo->matrix[edge1index][edge2index] = true;
        grafo->matrix[edge2index][edge1index] = true;
    }
    fclose(file);
    return grafo;
}

void MDA_Grafo_print(MDA_Grafo* grafo){
    printf("  ");
    for(size32_t i = 0; i < grafo->vertices; i++){
        printf("%c ", grafo->linkList[i]);
    }
    printf("\n");
    for(size32_t i = 0; i < grafo->vertices; i++){
        printf("%c ", grafo->linkList[i]);
        for(size32_t j = 0; j < grafo->vertices; j++){
            printf("%d ", grafo->matrix[i][j]);
        }
        printf("\n");
    }
}

bool MDA_Grafo_request(MDA_Grafo* grafo, char v1, char v2){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    return grafo->matrix[v1index][v2index] || grafo->matrix[v2index][v1index];
}