#include "Kruskal_Grafo.h"
#include <malloc.h>

Kruskal_Grafo* Kruskal_Grafo_create(char* grafoUri, kconf_t conf){
    Kruskal_Grafo* kGrafo = (Kruskal_Grafo*)malloc(sizeof(Kruskal_Grafo*));
    if(conf == KMDA){
        kGrafo->mGrafo = MDA_Grafo_loadWithWeight(grafoUri, false);
        kGrafo->size = kGrafo->mGrafo->vertices;
    } else if(conf == KLDA){
        kGrafo->lGrafo = LDA_Grafo_loadWithWeight(grafoUri, false);
        kGrafo->size = kGrafo->lGrafo->vertices;
    }
    kGrafo->conf = conf;
    kGrafo->fatherTree = (char*)malloc(sizeof(char) * kGrafo->size);
    Kruskal_Grafo_clean(kGrafo);
    return kGrafo;
}

int Kruskal_Grafo_run(Kruskal_Grafo* kGrafo){
    Kruskal_Grafo_clean(kGrafo);
    char* boss = (char*)malloc(sizeof(char) * kGrafo->size);
    for(size32_t i = 0; i < kGrafo->size; i++){
        boss[i] = Kruskal_Grafo_posToVertex(kGrafo, i);
    }
    int min = 0;
    int totalWeight = 0;
    size32_t v1;
    size32_t v2;

    while(min != INT_MAX){
        min = INT_MAX;
        for(size32_t i = 0; i < kGrafo->size; i++){
            char vi = Kruskal_Grafo_posToVertex(kGrafo, i);
            for(size32_t j = 0; j < kGrafo->size; j++){
                char vj = Kruskal_Grafo_posToVertex(kGrafo, j);
                int weight = Kruskal_Grafo_requestWeight(kGrafo, vi, vj);
                if(Kruskal_Grafo_request(kGrafo, vi, vj) && (i != j)){
                    if(i < j && boss[i] != boss[j]  && weight < min){
                        v1 = i;
                        v2 = j;
                        min = weight;
                        printf("%c - %c - %d\n", vi, vj, min);
                    }
                }
            }
        }
        if(min != INT_MAX){
            kGrafo->fatherTree[v2] = Kruskal_Grafo_posToVertex(kGrafo, v1);
            char b0 = boss[v1];
            char b1 = boss[v2];
            for(size32_t i = 0; i < kGrafo->size; i++){
                if(boss[i] == b1){
                    boss[i] = b0;
                }
            }
            totalWeight += min;
        }
    }
    printf("totalAlgorithm: %d\n", totalWeight);
    return totalWeight;
}


void Kruskal_Grafo_clean(Kruskal_Grafo* kGrafo){
    for(size32_t i = 0; i < kGrafo->size; i++){
        kGrafo->fatherTree[i] = UNVERTEX;
    }
}

size32_t Kruskal_Grafo_searchVertexPosition(Kruskal_Grafo* kGrafo, char vertex){
    switch (kGrafo->conf){
    case KMDA:
        return MDA_Grafo_searchVertexPosition(kGrafo->mGrafo->linkList, kGrafo->mGrafo->vertices, vertex);
    case KLDA:
        return LDA_Grafo_searchVertexPosition(kGrafo->lGrafo->linkList, kGrafo->lGrafo->vertices, vertex);
    default:
        return UNDEFINED;
    }
}

bool Kruskal_Grafo_request(Kruskal_Grafo* kGrafo, char v1, char v2){
    switch(kGrafo->conf){
    case KMDA:
        return MDA_Grafo_request(kGrafo->mGrafo, v1, v2);
    case KLDA:
        return LDA_Grafo_request(kGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

int Kruskal_Grafo_requestWeight(Kruskal_Grafo* kGrafo, char v1, char v2){
    switch(kGrafo->conf){
    case KMDA:
        return MDA_Grafo_requestWeight(kGrafo->mGrafo, v1, v2);
    case KLDA:
        return LDA_Grafo_requestWeight(kGrafo->lGrafo, v1, v2);
    default:
        return false;
    }
}

char Kruskal_Grafo_posToVertex(Kruskal_Grafo* kGrafo, size32_t pos){
    switch(kGrafo->conf){
    case KMDA:
        return kGrafo->mGrafo->linkList[pos];
    case KLDA:
        return kGrafo->lGrafo->linkList[pos];
    default:
        return UNVERTEX;
    }
}

void Kruskal_Grafo_print(Kruskal_Grafo* kGrafo){
    char father;
    char son;
    size32_t size;
    size32_t totalSize = 0;

    switch (kGrafo->conf){
    case KMDA:
        MDA_Grafo_print(kGrafo->mGrafo);
        break;
    case KLDA:
        LDA_Grafo_print(kGrafo->lGrafo);
        break;
    default:
        break;
    }

    for(size32_t i = 0; i < kGrafo->size; i++){
        if(kGrafo->fatherTree[i] != UNVERTEX && kGrafo->fatherTree[i] != UNVERTEX2){
            father = kGrafo->fatherTree[i];
            son = Kruskal_Grafo_posToVertex(kGrafo, i);
            size = Kruskal_Grafo_requestWeight(kGrafo, father, son);
            if(size != INT_MAX){
                totalSize += size;
            }
            printf("%c <- %c\n", son, father);
        } else {
            son = Kruskal_Grafo_posToVertex(kGrafo, i);
            printf("%c <- ROOT\n", son);
        }
        
    }
    printf("TotalSize: %d\n", totalSize);
}
