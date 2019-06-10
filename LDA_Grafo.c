#include "LDA_Grafo.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

LDA_Node* LDA_Node_add(LDA_Node* current, char vertex){
    LDA_Node* newNode = (LDA_Node*)malloc(sizeof(LDA_Node));
    newNode->next = current;
    newNode->vertex = vertex;
    return newNode;
}

/**
 * @brief Search for the position of the vertex, in the matrix, of the list of links
 * 
 * @param linkList LinkList
 * @param size Size of LinkList
 * @param vertex Vertex to search
 * @return size32_t Position
 */
size32_t LDA_Grafo_searchVertexPosition(char* linkList, size32_t size, char vertex){
    for(size32_t i = 0; i < size; i++){
        if(linkList[i] == vertex){
            return i;
        }
    }
    printf("ERROR 1 - Vertex '%c' not found\n", vertex);
    exit(EXIT_FAILURE);
}

LDA_Grafo* LDA_Grafo_load(const char* uri){
    LDA_Grafo* grafo = (LDA_Grafo*)malloc(sizeof(LDA_Grafo));
    FILE* file;
    
    char edge1 = ' ';
    char edge2 = ' ';
    
    size32_t edge1index;
    size32_t edge2index;
    
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

    grafo->lists = (LDA_Node**)malloc(sizeof(LDA_Node*) * grafo->vertices);

    for(size32_t i = 0; i < grafo->vertices; i++){
        grafo->lists[i] = NULL;
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

        edge1index = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, edge1);
        edge2index = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, edge2);


        if(edge1index >= grafo->vertices || edge2index >= grafo->vertices){
            printf("ERROR 2 - Something wrong is not right.\nThe return of the position of the vertex in the matrix exceeds the limits of the same.\nEdge1Index: %u | Edge2Index: %u | Vertices: %u\n", edge1index, edge2index, grafo->vertices);
            exit(EXIT_FAILURE);
        }

    
        grafo->lists[edge1index] = LDA_Node_add(grafo->lists[edge1index], edge2);
        grafo->lists[edge2index] = LDA_Node_add(grafo->lists[edge2index], edge1);

        edge1 = ' ';
        edge2 = ' ';
    }

    fclose(file);
    return grafo;
}

void LDA_Grafo_print(LDA_Grafo* grafo){
    for(size32_t i = 0; i < grafo->vertices; i++){
        printf("%c: ", grafo->linkList[i]);
        for(LDA_Node* aux = grafo->lists[i]; aux != NULL; aux = aux->next){
            printf("%c ", aux->vertex);
        }
        printf("\n");
    }
}

bool LDA_Grafo_request(LDA_Grafo* grafo, char v1, char v2){
    size32_t v1pos = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    for(LDA_Node* aux = grafo->lists[v1pos]; aux != NULL; aux = aux->next){
        if(aux->vertex == v2){
            return true;
        }
    }
    return false;
}

void LDA_Grafo_addEdge(LDA_Grafo* grafo, char v1, char v2){
    size32_t v1pos = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    for(LDA_Node* aux = grafo->lists[v1pos]; aux != NULL; aux = aux->next){
        if(aux->vertex == v2){
            return;
        }
    }
    size32_t v2pos = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);
    grafo->lists[v1pos] = LDA_Node_add(grafo->lists[v1pos], v2);
    grafo->lists[v2pos] = LDA_Node_add(grafo->lists[v1pos], v1);
    grafo->edges++;
}

void LDA_Grafo_removeEdge(LDA_Grafo* grafo, char v1, char v2){
    size32_t v1pos = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v1);
    LDA_Node* old = NULL;
    for(LDA_Node* aux = grafo->lists[v1pos]; aux != NULL; aux = aux->next){
        if(aux->vertex == v2){
            if(old == NULL){
                grafo->lists[v1pos] = aux->next;
            } else {
                old->next = aux->next;
            }
            grafo->edges--;
            free(aux);
            break;
        }
        old = aux;
    }
    
    size32_t v2pos = LDA_Grafo_searchVertexPosition(grafo->linkList, grafo->vertices, v2);
    old = NULL;
    for(LDA_Node* aux = grafo->lists[v2pos]; aux != NULL; aux = aux->next){
        if(aux->vertex == v1){
            if(old == NULL){
                grafo->lists[v1pos] = aux->next;
            } else {
                old->next = aux->next;
            }
            free(aux);
            break;
        }
        old = aux;
    }
}