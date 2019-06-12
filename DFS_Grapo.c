#include "DFS_Grafo.h"
#include <malloc.h>

DFS_Table* DFS_Table_create(char* grafoUri, dconf_t conf, bool directional){
    DFS_Table* table = (DFS_Table*)malloc(sizeof(DFS_Table));
    table->conf = conf;
    if(conf == DMDA){
        table->mGrafo = MDA_Grafo_load(grafoUri, directional);
        table->vertices = table->mGrafo->vertices;
    } else if(conf == DLDA) {
        table->lGrafo = LDA_Grafo_load(grafoUri, directional);
        table->vertices = table->lGrafo->vertices;
    }
    table->colors = (dcolor_t*)malloc(sizeof(dcolor_t) * table->vertices);
    table->father = (char*)malloc(sizeof(char) * table->vertices);
    table->foundTime = (size32_t*)malloc(sizeof(size32_t) * table->vertices);
    table->finishedTime = (size32_t*)malloc(sizeof(size32_t) * table->vertices);

    DFS_Table_clean(table);
    return table;
}

void DFS_Table_clean(DFS_Table* table){
    for(size32_t i = 0; i < table->vertices; i++){
        table->colors[i] = DWHITE;
        table->father[i] = UNVERTEX;
        table->foundTime[i] = UNDEFINED;
        table->finishedTime[i] = UNDEFINED;
    }
    table->time = 0;
}

size32_t DFS_Table_searchVertexPosition(DFS_Table* table, char vertex){
    switch (table->conf){
    case DMDA:
        return MDA_Grafo_searchVertexPosition(table->mGrafo->linkList, table->mGrafo->vertices, vertex);
    case DLDA:
        return LDA_Grafo_searchVertexPosition(table->lGrafo->linkList, table->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool DFS_Table_request(DFS_Table* table, char v1, char v2){
    switch(table->conf){
    case DMDA:
        return MDA_Grafo_request(table->mGrafo, v1, v2);
    case DLDA:
        return LDA_Grafo_request(table->lGrafo, v1, v2);
    default:
        return false;
    }
}

char DFS_Table_posToVertex(DFS_Table* table, size32_t pos){
    switch(table->conf){
    case DMDA:
        return table->mGrafo->linkList[pos];
    case DLDA:
        return table->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void DFS_Table_visit(DFS_Table* table, size32_t pos){
    char vertex = DFS_Table_posToVertex(table, pos);
    char vertex2;
    table->colors[pos] = DGRAY;
    table->time++;
    table->foundTime[pos] = table->time;
    for(size32_t i = 0; i < table->vertices; i++){
        vertex2 = DFS_Table_posToVertex(table, i);
        if(DFS_Table_request(table, vertex, vertex2) && table->colors[i] == DWHITE){
            table->father[i] = vertex;
            DFS_Table_visit(table, i);
        }
    }
    table->colors[pos] = DBLACK;
    table->finishedTime[pos] = table->time = table->time + 1;
}

void DFS_Table_run(DFS_Table* table){
    DFS_Table_clean(table);
    char vertex = UNVERTEX;
    for(size32_t i = 0; i < table->vertices; i++){
        if(table->colors[i] == DWHITE){
            DFS_Table_visit(table, i);
        }
    }
}

void DFS_Table_print(DFS_Table* table){
    printf("Vertex\t|d[u]\t|f[u]\t|pi[u]\t|cor[u]\t|t[u]:\n");
    for(size32_t i = 0; i < table->vertices; i++){
        char color;
        char vertex = DFS_Table_posToVertex(table, i);
        char father = table->father[i];
        size32_t found = table->foundTime[i];
        size32_t finished = table->finishedTime[i];
        switch (table->colors[i])
        {
        case DWHITE:
            color = 'W';
            break;
        case DGRAY:
            color = 'G';
            break;
        case DBLACK:
            color = 'B';
            break;
        default:
            color = 'U';
            break;
        }
        printf("%c\t|%d\t|%d\t|%c\t|%c\t|%d\n", vertex, found, finished, father, color, finished - found);
    }
}

