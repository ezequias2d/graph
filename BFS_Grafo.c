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
    BFS_QNode* aux;
    if(head->first != NULL){
        vout = head->first->vertex;
        aux = head->first;
        head->first = head->first->next;
        if(head->first == NULL){
            head->first = NULL;
            head->last = NULL;
        }
        free(aux);
    }
    return vout;
}

BFS_Table* BFS_Table_create(char* grafoUri, conf_t conf){
    BFS_Table* table = (BFS_Table*)malloc(sizeof(BFS_Table));
    table->conf = conf;
    if(conf == MDA){
        table->mGrafo = MDA_Grafo_load(grafoUri);
        table->vertices = table->mGrafo->vertices;
    } else if(conf == LDA) {
        table->lGrafo = LDA_Grafo_load(grafoUri);
        table->vertices = table->lGrafo->vertices;
    }
    table->colors = (color_t*)malloc(sizeof(color_t) * table->vertices);
    for(size32_t i = 0; i < table->vertices; i++){
        table->colors = WHITE;
    }

    table->queue = BFS_QHead_start();
    return table;
}
void BFS_Table_run(BFS_Table* table, char rootVertex){
    BFS_Q_put(&table->queue, rootVertex);

}