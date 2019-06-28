/**
 * @file LDA_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Lista de adjacencia para grafos
 * @version 0.1
 * @date 2019-06-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef LDA_GRAFO_H
#define LDA_GRAFO_H
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t size32_t;

struct LDA_Node{
    char vertex;
    int weight;
    struct LDA_Node* next;
};
typedef struct LDA_Node LDA_Node;

struct LDA_Grafo{
    size32_t vertices; /**< number of vertices*/
    size32_t edges;
    LDA_Node** lists;     /**< Lists itself*/
    char* linkList;    /**< list that links a character to a position of a dimension in the list*/
    bool directional;
};
typedef struct LDA_Grafo LDA_Grafo;

LDA_Grafo* LDA_Grafo_load(const char* uri, bool directional);
LDA_Grafo* LDA_Grafo_loadWithWeight(const char* uri, bool directional);

void LDA_Grafo_print(LDA_Grafo* grafo);
void LDA_Grafo_printWithWeight(LDA_Grafo* grafo);

bool LDA_Grafo_request(LDA_Grafo* grafo, char v1, char v2);
int LDA_Grafo_requestWeight(LDA_Grafo* grafo, char v1, char v2);

void LDA_Grafo_addEdge(LDA_Grafo* grafo, char v1, char v2);
void LDA_Grafo_addEdgeWithWeight(LDA_Grafo* grafo, char v1, char v2, int weight);
void LDA_Grafo_setEdgeWeight(LDA_Grafo* grafo, char v1, char v2, int weight);
void LDA_Grafo_removeEdge(LDA_Grafo* grafo, char v1, char v2);

size32_t LDA_Grafo_searchVertexPosition(char* linkList, size32_t size, char vertex);



#endif