#include "MDA_Grafo.h"
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>

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
    printf("MDA - ERROR 1 - Vertex '%c' not found\n", vertex);
    exit(EXIT_FAILURE);
}

MDA_Grafo* MDA_Grafo_loadWithWeight(const char* uri, bool directional){
    MDA_Grafo* grafo = (MDA_Grafo*)malloc(sizeof(MDA_Grafo));
    FILE* file;
    bool aux = false;
    char edge1 = ' ';
    char edge2 = ' ';

    size32_t edges;
    long verticesPos;

    file = fopen(uri, "r");
    fscanf(file, "%u", &grafo->vertices);
    fscanf(file, "%u", &edges);

    grafo->directional = directional;
    grafo->edges = 0;

    grafo->linkList = (char*) malloc(sizeof(char) * grafo->vertices);

    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->linkList[i] = ' ';
        while(grafo->linkList[i] == ' ' || grafo->linkList[i] == '\n'){
            fscanf(file, "%c", &grafo->linkList[i]);
        }
    }

    grafo->matrix = (bool**)malloc(sizeof(bool*) * (grafo->vertices));
    grafo->weight = (int**)malloc(sizeof(int*) * (grafo->vertices));
    
    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->matrix[i] = (bool*)malloc(sizeof(bool) * (grafo->vertices));
        grafo->weight[i] = (int*)malloc(sizeof(int) * (grafo->vertices));
        for(size32_t j = 0; j < grafo->vertices; j++){
            grafo->matrix[i][j] = (i == j);
            grafo->weight[i][j] = INT_MAX;
        }
    }

    for(size32_t i = 0; i < edges; i++){
        long oldPos = ftell(file);
        long newPos;

        int weight;
        
        do{
            fscanf(file, "%c", &edge1);
            newPos = ftell(file);
            if(newPos == oldPos){
                //nao consegue ler o arquivo(Can not read file)
                printf("ERROR 3 - Can not read file\nThe number of edges is wrong in the file header\nCorrect number: %u\nPlease fix\n", i);
                exit(EXIT_FAILURE);
            }
        } while(edge1 == ' ' || edge1 == '\n');

        fscanf(file, "%c", &edge2);

        fscanf(file, "%d", &weight);
        
        if(edge2 == '\n' || edge2 == ' '){
            printf("ERROR 6 - Wrong edges structure!\n Line: %d V1:'%c' V2:'%c'\n", i ,edge1, edge2);
            exit(EXIT_FAILURE);
        }

        MDA_Grafo_addEdgeWithWeight(grafo, edge1, edge2, weight);
    }
    if(edges != grafo->edges){
        printf("ERROR 4 - The number of edges is wrong.\nFix the file\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return grafo;
}

MDA_Grafo* MDA_Grafo_load(const char* uri, bool directional){
    MDA_Grafo* grafo = (MDA_Grafo*)malloc(sizeof(MDA_Grafo));
    FILE* file;
    bool aux = false;
    char edge1 = ' ';
    char edge2 = ' ';

    size32_t edges;
    long verticesPos;

    file = fopen(uri, "r");
    fscanf(file, "%u", &grafo->vertices);
    fscanf(file, "%u", &edges);

    grafo->directional = directional;
    grafo->edges = 0;

    grafo->linkList = (char*) malloc(sizeof(char) * grafo->vertices);

    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->linkList[i] = ' ';
        while(grafo->linkList[i] == ' ' || grafo->linkList[i] == '\n'){
            fscanf(file, "%c", &grafo->linkList[i]);
        }
    }

    grafo->matrix = (bool**)malloc(sizeof(bool*) * (grafo->vertices));
    grafo->weight = (int**)malloc(sizeof(int*) * (grafo->vertices));
    
    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->matrix[i] = (bool*)malloc(sizeof(bool) * (grafo->vertices));
        grafo->weight[i] = (int*)malloc(sizeof(int) * (grafo->vertices));
        for(size32_t j = 0; j < grafo->vertices; j++){
            grafo->matrix[i][j] = (i == j);
            grafo->weight[i][j] = INT_MAX / grafo->vertices;
        }
    }

    for(size32_t i = 0; i < edges; i++){
        long oldPos = ftell(file);
        long newPos;
        
        do{
            fscanf(file, "%c", &edge1);
            newPos = ftell(file);
            if(newPos == oldPos){
                //nao consegue ler o arquivo(Can not read file)
                printf("ERROR 3 - Can not read file\nThe number of edges is wrong in the file header\nCorrect number: %u\nPlease fix\n", i);
                exit(EXIT_FAILURE);
            }
        } while(edge1 == ' ' || edge1 == '\n');
        fscanf(file, "%c", &edge2);
        
        if(edge2 == '\n' || edge2 == ' '){
            printf("ERROR 6 - Wrong edges structure!\n Line: %d V1:'%c' V2:'%c'\n", i ,edge1, edge2);
            exit(EXIT_FAILURE);
        }

        MDA_Grafo_addEdge(grafo, edge1, edge2);
    }
    if(edges != grafo->edges){
        printf("ERROR 4 - The number of edges is wrong.\nFix the file\n");
        exit(EXIT_FAILURE);
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

void MDA_Grafo_printWithWeight(MDA_Grafo* grafo){
    printf("  ");
    for(size32_t i = 0; i < grafo->vertices; i++){
        printf("\t%c ", grafo->linkList[i]);
    }
    printf("\n");
    for(size32_t i = 0; i < grafo->vertices; i++){
        printf("%c", grafo->linkList[i]);
        for(size32_t j = 0; j < grafo->vertices; j++){
            printf("\t%d", grafo->matrix[i][j]);
            if(grafo->matrix[i][j]){
                if(grafo->weight[i][j] == INT_MAX){
                    printf("|I");
                }else{
                    printf("|%d", grafo->weight[i][j]);
                }
            }
            printf(" ");
        }
        printf("\n");
    }
}

bool MDA_Grafo_request(MDA_Grafo* grafo, char v1, char v2){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    return grafo->matrix[v1index][v2index];
}

int MDA_Grafo_requestWeight(MDA_Grafo* grafo, char v1, char v2){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    return grafo->weight[v1index][v2index];
}

void MDA_Grafo_addEdge(MDA_Grafo* grafo, char v1, char v2){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    if(v1index >= grafo->vertices || v2index >= grafo->vertices){
        printf("ERROR 2 - Something wrong is not right.\nThe return of the position of the vertex in the matrix exceeds the limits of the same.\nEdge1Index: %u | Edge2Index: %u | Vertices: %u\n", v1index, v2index, grafo->vertices);
        exit(EXIT_FAILURE);
    }

    if(grafo->matrix[v1index][v2index] == false){
        grafo->edges++;
    }

    grafo->matrix[v1index][v2index] = true;
    grafo->weight[v1index][v2index] = INT_MAX / grafo->vertices;

    if(!grafo->directional){
        grafo->matrix[v2index][v1index] = true;
        grafo->weight[v2index][v1index] = INT_MAX / grafo->vertices;
    }
}

void MDA_Grafo_addEdgeWithWeight(MDA_Grafo* grafo, char v1, char v2, int weight){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    if(v1index >= grafo->vertices || v2index >= grafo->vertices){
        printf("ERROR 2 - Something wrong is not right.\nThe return of the position of the vertex in the matrix exceeds the limits of the same.\nEdge1Index: %u | Edge2Index: %u | Vertices: %u\n", v1index, v2index, grafo->vertices);
        exit(EXIT_FAILURE);
    }

    if(grafo->matrix[v1index][v2index] == false){
        grafo->edges++;
    }

    grafo->matrix[v1index][v2index] = true;
    grafo->weight[v1index][v2index] = weight;

    if(!grafo->directional){
        grafo->matrix[v2index][v1index] = true;
        grafo->weight[v2index][v1index] = weight;
    }
}


void MDA_Grafo_setEdgeWeight(MDA_Grafo* grafo, char v1, char v2, int weight){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    if(v1index >= grafo->vertices || v2index >= grafo->vertices){
        printf("ERROR 2 - Something wrong is not right.\nThe return of the position of the vertex in the matrix exceeds the limits of the same.\nEdge1Index: %u | Edge2Index: %u | Vertices: %u\n", v1index, v2index, grafo->vertices);
        exit(EXIT_FAILURE);
    }

    if(grafo->matrix[v1index][v2index] == true){
        grafo->weight[v1index][v2index] = weight;
        if(!grafo->directional){
            grafo->weight[v2index][v1index] = weight;
        }
    }   
}

void MDA_Grafo_removeEdge(MDA_Grafo* grafo, char v1, char v2){
    size32_t v1index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    size32_t v2index = MDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);

    if(grafo->matrix[v1index][v2index] == true){
        grafo->edges--;
    }

    grafo->matrix[v1index][v2index] = false;
    grafo->weight[v1index][v2index] = INT_MAX;
    if(!grafo->directional){
        grafo->matrix[v2index][v1index] = false;
        grafo->weight[v2index][v1index] = INT_MAX;
    }
}

