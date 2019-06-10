/**
 * @file BFS_Grafo.h
 * @author your name (you@domain.com)
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

#define UNVERTEX (char)('A' - 1)

typedef enum {WHITE, GRAY, BLACK} color_t;
typedef enum {MDA, LDA} conf_t;

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
    color_t* colors;
    size32_t vertices;
    
    union{
        MDA_Grafo* mGrafo;
        LDA_Grafo* lGrafo;
    };

    conf_t conf;

    BFS_QHead queue;

};
typedef struct BFS_Table BFS_Table;

BFS_QHead BFS_QHead_start();
void BFS_Q_put(BFS_QHead* head, char vertex);
char BFS_Q_pop(BFS_QHead* head);

BFS_Table* BFS_Table_create(char* grafoUri, conf_t conf);




#endif