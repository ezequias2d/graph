#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
#include "BFS_Grafo.h"
#include "DFS_Grafo.h"

void testMDA(){
    MDA_Grafo* grafo = MDA_Grafo_load("grafo.data", false);
    MDA_Grafo_print(grafo);
    MDA_Grafo_removeEdge(grafo, 'D', 'E');
    MDA_Grafo_print(grafo);

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
    LDA_Grafo* grafo = LDA_Grafo_load("grafo.data");
    LDA_Grafo_print(grafo);
    LDA_Grafo_removeEdge(grafo, 'D', 'E');
    LDA_Grafo_print(grafo);
    
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
    BFS_Table* table = BFS_Table_create("grafo2.data", MDA);
    BFS_Table_run(table, 'S');
    BFS_Table_print(table);
    BFS_Table_printPath(table, 'S', 'Y');
    printf("\n");
}

void testDFS_MDA(){
    DFS_Table* table = DFS_Table_create("grafo2.data", MDA);
    DFS_Table_run(table);
    DFS_Table_print(table);
    printf("\n");
}
int main(){
    // testMDA();
    // printf("---------------\n");
    // testLDA();
    //testBFS_MDA();
    testDFS_MDA();
}