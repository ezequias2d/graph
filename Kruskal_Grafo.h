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
 * @brief Create a Breadth-First Search Table
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return DFS_Table* Breadth-First Search Table
 */
Kruskal_Grafo* Kruskal_Grafo_create(char* grafoUri, kconf_t conf);

/**
 * @brief Clean the Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void Kruskal_Grafo_clean(Kruskal_Grafo* table);

/**
 * @brief Runs the Breadth-First Search algorithm(executa o algoritimo de busca em largura)
 * 
 * @param table Breadth-First Search Table
 * @param rootVertex Root Vertex
 */
int Kruskal_Grafo_run(Kruskal_Grafo* pGrafo);

void Kruskal_Grafo_visit(Kruskal_Grafo* table, size32_t pos);

size32_t Kruskal_Grafo_searchVertexPosition(Kruskal_Grafo* pGrafo, char vertex);
bool Kruskal_Grafo_request(Kruskal_Grafo* pGrafo, char v1, char v2);
int Kruskal_Grafo_requestWeight(Kruskal_Grafo* pGrafo, char v1, char v2);
char Kruskal_Grafo_posToVertex(Kruskal_Grafo* pGrafo, size32_t pos);

/**
 * @brief Print Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void Kruskal_Grafo_print(Kruskal_Grafo* table);




#endif