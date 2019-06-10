#include "MDA_Grafo.h"

int main(){
    MDA_Grafo* grafo = MDA_Grafo_load("grafo.data");
    MDA_Grafo_print(grafo);

    char v1;
    char v2;
    for(size32_t i = 0; i < grafo->vertices; i++){
        for(size32_t j = 0; j < grafo->vertices; j++){
            v1 = grafo->linkList[i];
            v2 = grafo->linkList[j];
            printf("%c x %c: %d\n", v1, v2, MDA_Grafo_request(grafo, v1, v2));
        }
    }
}