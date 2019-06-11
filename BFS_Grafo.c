#include "BFS_Grafo.h"
#include <stdio.h>
#include <malloc.h>

BFS_QHead BFS_QHead_start(){
    BFS_QHead q;
    q.first = NULL;
    q.last = NULL;
    return q;
}

void BFS_Q_put(BFS_QHead* head, char vertex){
    BFS_QNode* node = (BFS_QNode*)malloc(sizeof(BFS_QNode));
    node->vertex = vertex;
    node->next = NULL;
    if(head->first == NULL && head->last == NULL){
        head->first = node;
        head->last = node;
    } else {
        head->last->next = node;
        head->last = node;
    }
}

char BFS_Q_pop(BFS_QHead* head){
    char vout = UNVERTEX;
    char next = '&';
    BFS_QNode* aux;
    if(head->first != NULL){
        vout = head->first->vertex;
        aux = head->first;
        if(head->first == head->last){
            head->first = NULL;
            head->last = NULL;
        } else {
            head->first = head->first->next;
        }
        if(head->first != NULL){
            next = head->first->vertex;
        }
        free(aux);
    }
    printf("DEQUEUE %c, next: %c\n", vout, next);
    return vout;
}

bool BFS_Q_empty(BFS_QHead head){
    return head.first == head.last && head.first == NULL;
}

BFS_Table* BFS_Table_create(char* grafoUri, conf_t conf){
    BFS_Table* table = (BFS_Table*)malloc(sizeof(BFS_Table));
    table->conf = conf;
    if(conf == MDA){
        table->mGrafo = MDA_Grafo_load(grafoUri, false);
        table->vertices = table->mGrafo->vertices;
    } else if(conf == LDA) {
        table->lGrafo = LDA_Grafo_load(grafoUri);
        table->vertices = table->lGrafo->vertices;
    }
    table->colors = (color_t*)malloc(sizeof(color_t) * table->vertices);
    table->father = (char*)malloc(sizeof(char) * table->vertices);
    table->distance = (size32_t*)malloc(sizeof(size32_t) * table->vertices);
    table->queue = BFS_QHead_start();

    BFS_Table_clean(table);
    return table;
}

void BFS_Table_clean(BFS_Table* table){
    for(size32_t i = 0; i < table->vertices; i++){
        table->colors[i] = WHITE;
        table->father[i] = UNVERTEX;
        table->distance[i] = UNDEFINED;
    }
    while(!BFS_Q_empty(table->queue)){
        BFS_Q_pop(&table->queue);
    }
}

size32_t BFS_Table_searchVertexPosition(BFS_Table* table, char vertex){
    switch (table->conf){
    case MDA:
        return MDA_Grafo_searchVertexPosition(table->mGrafo->linkList, table->mGrafo->vertices, vertex);
    case LDA:
        return LDA_Grafo_searchVertexPosition(table->lGrafo->linkList, table->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool BFS_Table_request(BFS_Table* table, char v1, char v2){
    switch(table->conf){
    case MDA:
        return MDA_Grafo_request(table->mGrafo, v1, v2);
    case LDA:
        return LDA_Grafo_request(table->lGrafo, v1, v2);
    default:
        return false;
    }
}

char BFS_Table_posToVertex(BFS_Table* table, size32_t pos){
    switch(table->conf){
    case MDA:
        return table->mGrafo->linkList[pos];
    case LDA:
        return table->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void BFS_Table_run(BFS_Table* table, char rootVertex){
    char vertexU;
    char vertexV;
    size32_t posU;
    size32_t posRoot = BFS_Table_searchVertexPosition(table, rootVertex);
    BFS_Table_clean(table);

    table->distance[posRoot] = 0;
    table->father[posRoot] = UNVERTEX;
    table->colors[posRoot] = GRAY;

    BFS_Q_put(&table->queue, rootVertex);

    while(!BFS_Q_empty(table->queue)){
        vertexU = BFS_Q_pop(&table->queue);
        printf("U: %c\n", vertexU);
        posU = BFS_Table_searchVertexPosition(table, vertexU);
        for(size32_t i = 0; i < table->vertices; i++){
            vertexV = BFS_Table_posToVertex(table, i);
            if(BFS_Table_request(table, vertexU, vertexV)) {
                if(table->colors[i] == WHITE){
                    printf("V: %c\n", vertexV);
                    table->colors[i] = GRAY;
                    table->distance[i] = table->distance[posU] + 1;
                    table->father[i] = vertexU;
                    BFS_Q_put(&table->queue, vertexV);
                }
            }   
        }
        table->colors[posU] = BLACK;
    }
}

void BFS_Table_print(BFS_Table* table){
    printf("Vertex\t|Distance\t|Father\t|Color\n");
    for(size32_t i = 0; i < table->vertices; i++){
        char color;
        char vertex = BFS_Table_posToVertex(table, i);
        unsigned char father = table->father[i];
        size32_t distance = table->distance[i];
        switch (table->colors[i])
        {
        case WHITE:
            color = 'W';
            break;
        case GRAY:
            color = 'G';
            break;
        case BLACK:
            color = 'B';
            break;
        default:
            color = 'U';
            break;
        }
        printf("%c\t|%d\t\t|%c\t|%c\n", vertex, distance, father, color);
    }
}

void BFS_Table_printPath(BFS_Table* table, char rootVertex, char vertex){
    size32_t posV = BFS_Table_searchVertexPosition(table, vertex);
    if(vertex == rootVertex){
        printf("S");
    } else if(table->father[posV] == UNVERTEX){
        printf("Without path from '%c' to '%c'\n", rootVertex, vertex);
    } else {
        BFS_Table_printPath(table, rootVertex, table->father[posV]);
        printf("-%c", vertex);
    }
}