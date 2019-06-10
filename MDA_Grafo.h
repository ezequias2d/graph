/**
 * @file MDA_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Matriz de adjacencias para grafos(adjacency matrix for graphs)
 * @version 0.1
 * @date 2019-06-10
 * 
 * @copyright Copyright (c) 2019
 */

#ifndef MDA_GRAFO_H
#define MDA_GRAFO_H
#include <stdbool.h>
#include <stdio.h>
typedef unsigned int size32_t;

struct MDA_Grafo{
    size32_t vertices;
    size32_t edges;
    FILE* file;
    bool** matrix;
    char* linkList;
};
typedef struct MDA_Grafo MDA_Grafo;

MDA_Grafo* MDA_Grafo_load(const char* uri);

bool MDA_Grafo_request(MDA_Grafo* grafo, char v1, char v2);

void MDA_Grafo_print(MDA_Grafo* grafo);

#endif