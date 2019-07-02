#include "Bellmanford_Grafo.h"
#include <malloc.h>

BellmanFord_Grafo* BellmanFord_Grafo_create(char* grafoUri, mconf_t conf){
    BellmanFord_Grafo* kGrafo = (BellmanFord_Grafo*)malloc(sizeof(BellmanFord_Grafo*));
    if(conf == MMDA){
        kGrafo->mGrafo = MDA_Grafo_loadWithWeight(grafoUri, false);
        kGrafo->size = kGrafo->mGrafo->vertices;
    } else if(conf == MLDA){
        kGrafo->lGrafo = LDA_Grafo_loadWithWeight(grafoUri, false);
        kGrafo->size = kGrafo->lGrafo->vertices;
    }
    kGrafo->conf = conf;
    kGrafo->fatherTree = (char*)malloc(sizeof(char) * kGrafo->size);
    kGrafo->cost = (int*)malloc(sizeof(int) * kGrafo->size);
    BellmanFord_Grafo_clean(kGrafo);
    return kGrafo;
}

int BellmanFord_Grafo_run(BellmanFord_Grafo* kGrafo, char initial){
    BellmanFord_Grafo_clean(kGrafo);
    size32_t initialPos = BellmanFord_Grafo_searchVertexPosition(kGrafo, initial);
    kGrafo->cost[initialPos] = 0;
    for(size32_t i = 1; i < kGrafo->size; i++){
        for(size32_t j = 0; j < kGrafo->size; j++){
            char vj = BellmanFord_Grafo_posToVertex(kGrafo, j);
            for(size32_t k = 0; k < kGrafo->size; k++){
                char vk = BellmanFord_Grafo_posToVertex(kGrafo, k);
                if(BellmanFord_Grafo_request(kGrafo, vj, vk) && vj != vk){
                    int weight = BellmanFord_Grafo_requestWeight(kGrafo, vj, vk);
                    if(kGrafo->cost[j] != INT_MAX && kGrafo->cost[j] + weight < kGrafo->cost[k]){
                        kGrafo->cost[k] = kGrafo->cost[j] + weight;
                        kGrafo->fatherTree[k] = vj;
                    }
                }
            }
        }
    }

    for(size32_t i = 0; i < kGrafo->size; i++){
        for(size32_t j = 0; j < kGrafo->size; j++){
            char vi = BellmanFord_Grafo_posToVertex(kGrafo, i);
            char vj = BellmanFord_Grafo_posToVertex(kGrafo, j);
            int weight = BellmanFord_Grafo_requestWeight(kGrafo, vi, vj);
            bool e = BellmanFord_Grafo_request(kGrafo, vi, vj) && vi != vj;
            if(kGrafo->cost[i] != INT_MAX && e && kGrafo->cost[i] + weight < kGrafo->cost[j]){
                printf("Negative weight cycle\n");
            }
        }
    }

    return 0;
}


void BellmanFord_Grafo_clean(BellmanFord_Grafo* kGrafo){
    for(size32_t i = 0; i < kGrafo->size; i++){
        kGrafo->fatherTree[i] = UNVERTEX;
        kGrafo->cost[i] = INT_MAX;
    }
}

size32_t BellmanFord_Grafo_searchVertexPosition(BellmanFord_Grafo* kGrafo, char vertex){
    switch (kGrafo->conf){
    case MMDA:
        return MDA_Grafo_searchVertexPosition(kGrafo->mGrafo->linkList, kGrafo->mGrafo->vertices, vertex);
    case MLDA:
        return LDA_Grafo_searchVertexPosition(kGrafo->lGrafo->linkList, kGrafo->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool BellmanFord_Grafo_request(BellmanFord_Grafo* kGrafo, char v1, char v2){
    switch(kGrafo->conf){
    case MMDA:
        return MDA_Grafo_request(kGrafo->mGrafo, v1, v2);
    case MLDA:
        return LDA_Grafo_request(kGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

int BellmanFord_Grafo_requestWeight(BellmanFord_Grafo* kGrafo, char v1, char v2){
    switch(kGrafo->conf){
    case MMDA:
        return MDA_Grafo_requestWeight(kGrafo->mGrafo, v1, v2);
    case MLDA:
        return LDA_Grafo_requestWeight(kGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

char BellmanFord_Grafo_posToVertex(BellmanFord_Grafo* kGrafo, size32_t pos){
    switch(kGrafo->conf){
    case MMDA:
        return kGrafo->mGrafo->linkList[pos];
    case MLDA:
        return kGrafo->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void BellmanFord_Grafo_print(BellmanFord_Grafo* kGrafo){
    char father;
    char son;

    switch (kGrafo->conf){
    case MMDA:
        MDA_Grafo_print(kGrafo->mGrafo);
        break;
    case MLDA:
        LDA_Grafo_print(kGrafo->lGrafo);
        break;
    default:
        break;
    }

    for(size32_t i = 0; i < kGrafo->size; i++){
        if(kGrafo->fatherTree[i] != UNVERTEX){
            father = kGrafo->fatherTree[i];
            son = BellmanFord_Grafo_posToVertex(kGrafo, i);
            printf("%c <- %c [cost to ROOT: %d]\n", son, father, kGrafo->cost[i]);
        } else {
            son = BellmanFord_Grafo_posToVertex(kGrafo, i);
            printf("%c <- ROOT\n", son);
        }
        
    }
}
