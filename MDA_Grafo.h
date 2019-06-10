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
#include <stdint.h>

/**
 * @brief 32-bit size variable
 */
typedef uint32_t size32_t;

/**
 * @brief Graph using adjacency matrix
 */
struct MDA_Grafo{
    size32_t vertices; /**< number of vertices*/
    size32_t edges;    /**< number of edges*/
    bool** matrix;     /**< matrix itself*/
    char* linkList;    /**< list that links a character to a position of a dimension in the list*/
};
typedef struct MDA_Grafo MDA_Grafo;

/**
 * @brief Loads a graph file
 * 
 * @param uri Uri of file
 * @return MDA_Grafo* Graph
 */
MDA_Grafo* MDA_Grafo_load(const char* uri);

/**
 * @brief Request if the vertices are connected
 * 
 * @param grafo Graph
 * @param v1 first vertex
 * @param v2 second vertex
 * @return true The vertices are connected
 * @return false The vertices are disconnected
 */
bool MDA_Grafo_request(MDA_Grafo* grafo, char v1, char v2);

/**
 * @brief Prints the graph table
 * 
 * @param grafo Graph
 */
void MDA_Grafo_print(MDA_Grafo* grafo);

void MDA_Grafo_addEdge(MDA_Grafo* grafo, char v1, char v2);
void MDA_Grafo_removeEdge(MDA_Grafo* grafo, char v1, char v2);
#endif