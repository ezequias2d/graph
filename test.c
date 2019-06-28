#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
#include "BFS_Grafo.h"
#include "DFS_Grafo.h"
#include "Prim_Grafo.h"
#include "Kruskal_Grafo.h"

void testMDA(){
    MDA_Grafo* grafo = MDA_Grafo_loadWithWeight("grafo-weight.data", false);
    MDA_Grafo_print(grafo);
    //MDA_Grafo_removeEdge(grafo, 'D', 'E');
    MDA_Grafo_printWithWeight(grafo);

    // char v1;
    // char v2;
    // for(size32_t i = 0; i < grafo->vertices; i++){
    //     for(size32_t j = 0; j < grafo->vertices; j++){
    //         v1 = grafo->linkList[i];
    //         v2 = grafo->linkList[j];
    //         printf("%c x %c: %d\n", v1, v2, MDA_Grafo_request(grafo, v1, v2));
    //     }
    // }
}
void testLDA(){
    LDA_Grafo* grafo = LDA_Grafo_loadWithWeight("grafo-weight.data", false);
    LDA_Grafo_print(grafo);
    //LDA_Grafo_removeEdge(grafo, 'D', 'E');
    LDA_Grafo_printWithWeight(grafo);
    
    // char v1;
    // char v2;
    // for(size32_t i = 0; i < grafo->vertices; i++){
    //     for(size32_t j = 0; j < grafo->vertices; j++){
    //         v1 = grafo->linkList[i];
    //         v2 = grafo->linkList[j];
    //         printf("%c x %c: %d\n", v1, v2, LDA_Grafo_request(grafo, v1, v2));
    //     }
    // }
}
void testBFS_MDA(){
    BFS_Table* table = BFS_Table_create("grafo2.data", BMDA, false);
    BFS_Table_run(table, 'S');
    BFS_Table_print(table);
    BFS_Table_printPath(table, 'S', 'Y');
    printf("\n");
}

void testDFS_MDA(){
    DFS_Table* table = DFS_Table_create("grafo2.data", DLDA, true);
    DFS_Table_run(table);
    DFS_Table_print(table);
    printf("\n");
}

void testPrim_Grafo(){
    Prim_Grafo* pGrafoM = Prim_Grafo_create("grafo-weight.data", PMDA);
    Prim_Grafo* pGrafoL = Prim_Grafo_create("grafo-weight.data", PLDA);

    Prim_Grafo_run(pGrafoM);
    Prim_Grafo_run(pGrafoL);

    Prim_Grafo_print(pGrafoM);
    Prim_Grafo_print(pGrafoL);
}

void testKruskal_Grafo(){
    Kruskal_Grafo* pGrafoM = Kruskal_Grafo_create("grafo-weight.data", KMDA);
    Kruskal_Grafo* pGrafoL = Kruskal_Grafo_create("grafo-weight.data", KLDA);

    Kruskal_Grafo_run(pGrafoM);
    Kruskal_Grafo_run(pGrafoL);

    Kruskal_Grafo_print(pGrafoM);
    Kruskal_Grafo_print(pGrafoL);
}

int main(){
    //testMDA();
    // printf("---------------\n");
    //testLDA();
    //testBFS_MDA();
    //testDFS_MDA();
    //testPrim_Grafo();
    testKruskal_Grafo();
}
