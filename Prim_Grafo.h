/**
 * @file Prim_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Algoritimo de Prim para grafo
 * @version 0.1
 * @date 2019-06-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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
 * @brief Create a Prim struct
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return Prim_Grafo* Prim struct
 */
Prim_Grafo* Prim_Grafo_create(char* grafoUri, pconf_t conf);

/**
 * @brief Clean the Prim Struct
 * 
 * @param pGrafo Prim struct to clean
 */
void Prim_Grafo_clean(Prim_Grafo* pGrafo);

/**
 * @brief Runs the Prim MST algorithm
 * 
 * @param pGrafo Prim struct
 */
int Prim_Grafo_run(Prim_Grafo* pGrafo);

size32_t Prim_Grafo_searchVertexPosition(Prim_Grafo* pGrafo, char vertex);
bool Prim_Grafo_request(Prim_Grafo* pGrafo, char v1, char v2);
int Prim_Grafo_requestWeight(Prim_Grafo* pGrafo, char v1, char v2);
char Prim_Grafo_posToVertex(Prim_Grafo* pGrafo, size32_t pos);

/**
 * @brief Print Prim struct
 * 
 * @param pGrafo Prim struct
 */
void Prim_Grafo_print(Prim_Grafo* pGrafo);




#endif