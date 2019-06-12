/**
 * @file BFS_Grafo.h
 * @author Ezequias Silva (ezequiasmoises@gmail.com)
 * @brief Busca em largura(Breadth-First Search)
 * @version 0.1
 * @date 2019-06-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef BFS_GRAFO_H
#define BFS_GRAFO_H

#include "MDA_Grafo.h"
#include "LDA_Grafo.h"
#include <limits.h>

#define UNVERTEX (char)'\0'
#define UNDEFINED INT_MAX

typedef enum {BWHITE, BGRAY, BBLACK} bcolor_t;
typedef enum {BMDA, BLDA} bconf_t;

struct BFS_QNode{
    char vertex;
    struct BFS_QNode* next;
};
typedef struct BFS_QNode BFS_QNode;

struct BFS_QHead{
    BFS_QNode* first;
    BFS_QNode* last;
};
typedef struct BFS_QHead BFS_QHead;

struct BFS_Table{
    bcolor_t* colors;        /**< Color array*/
    char* father;           /**< Father array*/
    size32_t* distance;     /**< Distance array*/
    size32_t vertices;      /**< Number of vertices*/
    union{                  
        MDA_Grafo* mGrafo;  
        LDA_Grafo* lGrafo;
    };                      /**< Graph*/
    bconf_t conf;            /**< Type of graph struct*/
    BFS_QHead queue;        /**< Queue*/
};
typedef struct BFS_Table BFS_Table;

/**
 * @brief Start a Queue
 * 
 * @return BFS_QHead Queue Head
 */
BFS_QHead BFS_QHead_start();

/**
 * @brief Queue up
 * 
 * @param head Queue Head
 * @param vertex Vertex to queue
 */
void BFS_Q_put(BFS_QHead* head, char vertex);

/**
 * @brief Get and remove the first from the queue
 * 
 * @param head Queue Head
 * @return char Vertex
 */
char BFS_Q_pop(BFS_QHead* head);

/**
 * @brief Check if it is empty
 * 
 * @param head Queue Head
 * @return true The queue is empty
 * @return false The queue is not empty
 */
bool BFS_Q_empty(BFS_QHead head);

/**
 * @brief Create a Breadth-First Search Table
 * 
 * @param grafoUri Uri of Graph to load
 * @param conf Type of structure to load(MDA or LDA)
 * @return BFS_Table* Breadth-First Search Table
 */
BFS_Table* BFS_Table_create(char* grafoUri, bconf_t conf, bool directional);

/**
 * @brief Clean the Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void BFS_Table_clean(BFS_Table* table);

/**
 * @brief Runs the Breadth-First Search algorithm(executa o algoritimo de busca em largura)
 * 
 * @param table Breadth-First Search Table
 * @param rootVertex Root Vertex
 */
void BFS_Table_run(BFS_Table* table, char rootVertex);

/**
 * @brief Print Breadth-First Search Table
 * 
 * @param table Breadth-First Search Table
 */
void BFS_Table_print(BFS_Table* table);

void BFS_Table_printPath(BFS_Table* table, char rootVertex, char vertex);


#endif