#ifndef PRIM_GRAFO_H
#include <limits.h>
#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
typedef enum {PMDA, PLDA} pconf_t;

#define UNVERTEX2 (char)'\1'
#define UNVERTEX (char)'\0'
#define UNDEFINED INT_MAX

struct Prim_Grafo{
    size32_t size;
    char* fatherTree;
    pconf_t conf;
    union{
        MDA_Grafo* mGrafo;  
        LDA_Grafo* lGrafo;
    };
};
typedef struct Prim_Grafo Prim_Grafo;



/**
 * @brief Create a Breadth-First Search Table
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return DFS_Table* Breadth-First Search Table
 */
Prim_Grafo* Prim_Grafo_create(char* grafoUri, pconf_t conf);

/**
 * @brief Clean the Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void Prim_Grafo_clean(Prim_Grafo* table);

/**
 * @brief Runs the Breadth-First Search algorithm(executa o algoritimo de busca em largura)
 * 
 * @param table Breadth-First Search Table
 * @param rootVertex Root Vertex
 */
int Prim_Grafo_run(Prim_Grafo* pGrafo);

void Prim_Grafo_visit(Prim_Grafo* table, size32_t pos);

size32_t Prim_Grafo_searchVertexPosition(Prim_Grafo* pGrafo, char vertex);
bool Prim_Grafo_request(Prim_Grafo* pGrafo, char v1, char v2);
int Prim_Grafo_requestWeight(Prim_Grafo* pGrafo, char v1, char v2);
char Prim_Grafo_posToVertex(Prim_Grafo* pGrafo, size32_t pos);

/**
 * @brief Print Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void Prim_Grafo_print(Prim_Grafo* table);




#endif