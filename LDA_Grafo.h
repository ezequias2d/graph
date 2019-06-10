#ifndef LDA_GRAFO_H
#define LDA_GRAFO_H
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t size32_t;

struct LDA_Node{
    char vertex;
    struct LDA_Node* next;
};
typedef struct LDA_Node LDA_Node;

struct LDA_Grafo{
    size32_t vertices; /**< number of vertices*/
    size32_t edges;
    LDA_Node** lists;     /**< Lists itself*/
    char* linkList;    /**< list that links a character to a position of a dimension in the list*/
};
typedef struct LDA_Grafo LDA_Grafo;

LDA_Grafo* LDA_Grafo_load(const char* uri);

void LDA_Grafo_print(LDA_Grafo* grafo);

bool LDA_Grafo_request(LDA_Grafo* grafo, char v1, char v2);

void LDA_Grafo_addEdge(LDA_Grafo* grafo, char v1, char v2);
void LDA_Grafo_removeEdge(LDA_Grafo* grafo, char v1, char v2);


#endif