/**
 * @file DFS_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Busca em profundidade(Depth-First Search)
 * @version 0.1
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef DFS_GRAFO_H
#define DFS_GRAFO_H

#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
#include <limits.h>

#define UNVERTEX (char)'\0'
#define UNDEFINED INT_MAX

typedef enum {DWHITE, DGRAY, DBLACK} dcolor_t;
typedef enum {DMDA, DLDA} dconf_t;

struct DFS_QNode{
    char vertex;
    struct DFS_QNode* next;
};
typedef struct DFS_QNode DFS_QNode;

struct DFS_QHead{
    DFS_QNode* first;
    DFS_QNode* last;
};
typedef struct DFS_QHead DFS_QHead;

struct DFS_Table{
    dcolor_t* colors;        /**< Color array*/
    char* father;           /**< Father array*/
    size32_t* foundTime;     /**< Distance array*/
    size32_t* finishedTime;     /**< Distance array*/
    size32_t vertices;      /**< Number of vertices*/
    union{                  
        MDA_Grafo* mGrafo;  
        LDA_Grafo* lGrafo;
    };                      /**< Graph*/
    dconf_t conf;            /**< Type of graph struct*/
    size32_t time;
};
typedef struct DFS_Table DFS_Table;

/**
 * @brief Create a Breadth-First Search Table
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return DFS_Table* Breadth-First Search Table
 */
DFS_Table* DFS_Table_create(char* grafoUri, dconf_t conf, bool directional);

/**
 * @brief Clean the Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void DFS_Table_clean(DFS_Table* table);

/**
 * @brief Runs the Breadth-First Search algorithm(executa o algoritimo de busca em largura)
 * 
 * @param table Breadth-First Search Table
 * @param rootVertex Root Vertex
 */
void DFS_Table_run(DFS_Table* table);

void DFS_Table_visit(DFS_Table* table, size32_t pos);

/**
 * @brief Print Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void DFS_Table_print(DFS_Table* table);

void DFS_Table_printPath(DFS_Table* table, char rootVertex, char vertex);


#endif