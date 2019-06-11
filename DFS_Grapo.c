#include "DFS_Grafo.h"
#include <malloc.h>

DFS_Table* DFS_Table_create(char* grafoUri, conf_t conf){
    DFS_Table* table = (DFS_Table*)malloc(sizeof(DFS_Table));
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
    table->foundTime = (size32_t*)malloc(sizeof(size32_t) * table->vertices);
    table->finishedTime = (size32_t*)malloc(sizeof(size32_t) * table->vertices);

    DFS_Table_clean(table);
    return table;
}

void DFS_Table_clean(DFS_Table* table){
    for(size32_t i = 0; i < table->vertices; i++){
        table->colors[i] = WHITE;
        table->father[i] = UNVERTEX;
        table->foundTime[i] = UNDEFINED;
        table->finishedTime[i] = UNDEFINED;
    }
    table->time = 0;
}

size32_t DFS_Table_searchVertexPosition(DFS_Table* table, char vertex){
    switch (table->conf){
    case MDA:
        return MDA_Grafo_searchVertexPosition(table->mGrafo->linkList, table->mGrafo->vertices, vertex);
    case LDA:
        return LDA_Grafo_searchVertexPosition(table->lGrafo->linkList, table->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool DFS_Table_request(DFS_Table* table, char v1, char v2){
    switch(table->conf){
    case MDA:
        return MDA_Grafo_request(table->mGrafo, v1, v2);
    case LDA:
        return LDA_Grafo_request(table->lGrafo, v1, v2);
    default:
        return false;
    }
}

char DFS_Table_posToVertex(DFS_Table* table, size32_t pos){
    switch(table->conf){
    case MDA:
        return table->mGrafo->linkList[pos];
    case LDA:
        return table->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void DFS_Table_visit(DFS_Table* table, char vertex){
    size32_t posV = DFS_Table_searchVertexPosition(table, vertex);
    table->colors[posV] = GRAY;
    table->time++;
    table->foundTime[posV] = table->time;
    char vertex2;
    for(size32_t i = 0; i < table->vertices; i++){
        vertex2 = DFS_Table_posToVertex(table, i);
        if(DFS_Table_request(table, vertex, vertex2) 
          && table->colors[posV] == WHITE){
            table->father[i] = vertex;
            DFS_Table_visit(table, vertex2);
        }
    }
    table->colors[posV] = BLACK;
    table->finishedTime[posV] = table->time = table->time + 1;
}

void DFS_Table_run(DFS_Table* table){
    DFS_Table_clean(table);
    size32_t rootPos = DFS_Table_searchVertexPosition(table, rootPos);
    char vertex = UNVERTEX;
    for(size32_t i = 0; i < table->vertices; i++){
        vertex = DFS_Table_posToVertex(table, i);
        if(DFS_Table_request(table, i, vertex) == true){
            if(table->colors[i] == WHITE){
                DFS_Table_visit(table, vertex);
            }
        }
    }
}


void DFS_Table_print(DFS_Table* table){
    printf("Vertex\t|Found\t|Finished\t|Father\t|Color\n");
    for(size32_t i = 0; i < table->vertices; i++){
        char color;
        char vertex = DFS_Table_posToVertex(table, i);
        unsigned char father = table->father[i];
        size32_t found = table->foundTime[i];
        size32_t finished = table->finishedTime[i];
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
        printf("%c\t|%d\t|%d\t|%c\t|%c\n", vertex, found, finished, father, color);
    }
}

