/**
 * @file Kruskal_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Algoritimo de Kruskal para grafo
 * @version 0.1
 * @date 2019-06-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef Kruskal_Grafo_H
#include <limits.h>
#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
typedef enum {KMDA, KLDA} kconf_t;

#define UNVERTEX2 (char)'\1'
#define UNVERTEX (char)'\0'
#define UNDEFINED INT_MAX

struct Kruskal_Grafo{
    size32_t size;
    kconf_t conf;
    char* fatherTree;
    union{
        MDA_Grafo* mGrafo;  
        LDA_Grafo* lGrafo;
    };
};
typedef struct Kruskal_Grafo Kruskal_Grafo;

/**
 * @brief Create a Kruskal Struct
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return DFS_kGrafo* Breadth-First Search kGrafo
 */
Kruskal_Grafo* Kruskal_Grafo_create(char* grafoUri, kconf_t conf);

/**
 * @brief Clean the Kruskal struct
 * 
 * @param kGrafo Kruskal struct to clean
 */
void Kruskal_Grafo_clean(Kruskal_Grafo* kGrafo);

/**
 * @brief Runs the Kruskal MST algorithm
 * 
 * @param kGrafo Kruskal struct
 */
int Kruskal_Grafo_run(Kruskal_Grafo* kGrafo);

size32_t Kruskal_Grafo_searchVertexPosition(Kruskal_Grafo* kGrafo, char vertex);
bool Kruskal_Grafo_request(Kruskal_Grafo* kGrafo, char v1, char v2);
int Kruskal_Grafo_requestWeight(Kruskal_Grafo* kGrafo, char v1, char v2);
char Kruskal_Grafo_posToVertex(Kruskal_Grafo* kGrafo, size32_t pos);

/**
 * @brief Print Kruskal struct
 * 
 * @param kGrafo Kruskal struct
 */
void Kruskal_Grafo_print(Kruskal_Grafo* kGrafo);




#endif