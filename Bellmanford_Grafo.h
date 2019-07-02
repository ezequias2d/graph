/**
 * @file BellmanFord_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Algoritimo de BellmanFord para grafo
 * @version 0.1
 * @date 2019-06-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef BellmanFord_Grafo_H
#include <limits.h>
#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
typedef enum {MMDA, MLDA} mconf_t;

#define UNVERTEX2 (char)'\1'
#define UNVERTEX (char)'\0'
#define UNDEFINED INT_MAX

struct BellmanFord_Grafo{
    size32_t size;
    mconf_t conf;
    char* fatherTree;
    int* cost;
    union{
        MDA_Grafo* mGrafo;  
        LDA_Grafo* lGrafo;
    };
};
typedef struct BellmanFord_Grafo BellmanFord_Grafo;

/**
 * @brief Create a BellmanFord Struct
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return DFS_kGrafo* Breadth-First Search kGrafo
 */
BellmanFord_Grafo* BellmanFord_Grafo_create(char* grafoUri, mconf_t conf);

/**
 * @brief Clean the BellmanFord struct
 * 
 * @param kGrafo BellmanFord struct to clean
 */
void BellmanFord_Grafo_clean(BellmanFord_Grafo* kGrafo);

/**
 * @brief Runs the BellmanFord MST algorithm
 * 
 * @param kGrafo BellmanFord struct
 */
int BellmanFord_Grafo_run(BellmanFord_Grafo* kGrafo, char initial);

size32_t BellmanFord_Grafo_searchVertexPosition(BellmanFord_Grafo* kGrafo, char vertex);
bool BellmanFord_Grafo_request(BellmanFord_Grafo* kGrafo, char v1, char v2);
int BellmanFord_Grafo_requestWeight(BellmanFord_Grafo* kGrafo, char v1, char v2);
char BellmanFord_Grafo_posToVertex(BellmanFord_Grafo* kGrafo, size32_t pos);

/**
 * @brief Print BellmanFord struct
 * 
 * @param kGrafo BellmanFord struct
 */
void BellmanFord_Grafo_print(BellmanFord_Grafo* kGrafo);




#endif