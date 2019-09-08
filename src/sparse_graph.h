/**
 * @file graph.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Adjacency Matrix.
 *
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_SPARSE_GRAPH_H
#define RETHINK_C_SPARSE_GRAPH_H

#include "arraylist.h"

typedef struct _AdjacencyArc AdjacencyArc;
typedef struct _AdjacencyList AdjacencyList;
typedef ArrayList SparseGraph;

/**
 * @brief Malloc a new Sparse Graph.
 * 
 * @param num_vertex        The number of vertexes.
 * @return SparseGraph*     The new Sparse Graph.
 */
SparseGraph *sparse_graph_new(unsigned int num_vertex);

/**
 * @brief Delete a Sparse Graph.
 * 
 * @param graph     The Sparse Graph.
 */
void sparse_graph_free(SparseGraph *graph);

/**
 * @brief Link two vertexes in a Sparse Graph.
 * 
 * @param graph         The Sparse Graph.
 * @param vertex1 
 * @param vertex2 
 * @return int 
 */
int sparse_graph_link(SparseGraph *graph, int vertex1, int vertex2);

/**
 * @brief Topological sorting by Khan algorithm.
 * 
 * @param graph 
 * @return Queue* 
 */
int *sparse_graph_topo_sort(SparseGraph *graph);

#endif /* #ifndef RETHINK_C_SPARSE_GRAPH_H */