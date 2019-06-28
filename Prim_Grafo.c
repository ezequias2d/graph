#include "Prim_Grafo.h"
#include <malloc.h>

Prim_Grafo* Prim_Grafo_create(char* grafoUri, pconf_t conf){
    Prim_Grafo* pGrafo = (Prim_Grafo*)malloc(sizeof(Prim_Grafo*));
    if(conf == PMDA){
        pGrafo->mGrafo = MDA_Grafo_loadWithWeight(grafoUri, false);
        pGrafo->size = pGrafo->mGrafo->vertices;
    } else if(conf == PLDA){
        pGrafo->lGrafo = LDA_Grafo_loadWithWeight(grafoUri, false);
        pGrafo->size = pGrafo->lGrafo->vertices;
    }
    pGrafo->conf = conf;
    pGrafo->fatherTree = (char*)malloc(sizeof(char) * pGrafo->size);
    Prim_Grafo_clean(pGrafo);
    return pGrafo;
}

int Prim_Grafo_run(Prim_Grafo* pGrafo){
    Prim_Grafo_clean(pGrafo);
    pGrafo->fatherTree[0] = UNVERTEX2;
    int min = 0;
    int totalWeight = 0;
    char v1 = UNVERTEX;
    size32_t v2;
    while(min != INT_MAX){
        min = INT_MAX;
        for(size32_t i = 0; i < pGrafo->size; i++){
            if(pGrafo->fatherTree[i] == UNVERTEX){
                char vi = Prim_Grafo_posToVertex(pGrafo, i);
                for(size32_t j = 0; j < pGrafo->size; j++){
                    char vj = Prim_Grafo_posToVertex(pGrafo, j);
                    int weight =  Prim_Grafo_requestWeight(pGrafo, vi, vj);
                    if(pGrafo->fatherTree[j] != UNVERTEX && min > weight){
                        min = weight;
                        v1 = vj;
                        v2 = i;
                    }
                }
            }
        }
        if(min != INT_MAX){
            totalWeight += min;
            pGrafo->fatherTree[v2] = v1;
        }
    }
    return totalWeight;
}


void Prim_Grafo_clean(Prim_Grafo* pGrafo){
    for(size32_t i = 0; i < pGrafo->size; i++){
        pGrafo->fatherTree[i] = UNVERTEX;
    }
}

size32_t Prim_Grafo_searchVertexPosition(Prim_Grafo* pGrafo, char vertex){
    switch (pGrafo->conf){
    case PMDA:
        return MDA_Grafo_searchVertexPosition(pGrafo->mGrafo->linkList, pGrafo->mGrafo->vertices, vertex);
    case PLDA:
        return LDA_Grafo_searchVertexPosition(pGrafo->lGrafo->linkList, pGrafo->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool Prim_Grafo_request(Prim_Grafo* pGrafo, char v1, char v2){
    switch(pGrafo->conf){
    case PMDA:
        return MDA_Grafo_request(pGrafo->mGrafo, v1, v2);
    case PLDA:
        return LDA_Grafo_request(pGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

int Prim_Grafo_requestWeight(Prim_Grafo* pGrafo, char v1, char v2){
    switch(pGrafo->conf){
    case PMDA:
        return MDA_Grafo_requestWeight(pGrafo->mGrafo, v1, v2);
    case PLDA:
        return LDA_Grafo_requestWeight(pGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

char Prim_Grafo_posToVertex(Prim_Grafo* pGrafo, size32_t pos){
    switch(pGrafo->conf){
    case PMDA:
        return pGrafo->mGrafo->linkList[pos];
    case PLDA:
        return pGrafo->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void Prim_Grafo_print(Prim_Grafo* pGrafo){
    char father;
    char son;
    size32_t size;
    size32_t totalSize = 0;

    switch (pGrafo->conf){
    case PMDA:
        MDA_Grafo_print(pGrafo->mGrafo);
        break;
    case PLDA:
        LDA_Grafo_print(pGrafo->lGrafo);
        break;
    default:
        break;
    }

    for(size32_t i = 0; i < pGrafo->size; i++){
        if(pGrafo->fatherTree[i] == UNVERTEX || pGrafo->fatherTree[i] == UNVERTEX2) continue;
        father = pGrafo->fatherTree[i];
        son = Prim_Grafo_posToVertex(pGrafo, i);
        size = Prim_Grafo_requestWeight(pGrafo, father, son);
        if(size != INT_MAX){
            totalSize += size;
        }
        printf("%c <- %c\n", son, father);
    }
    printf("TotalSize: %d\n", totalSize);
}
