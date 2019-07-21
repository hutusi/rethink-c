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

#ifndef RETHINK_C_GRAPH_H
#define RETHINK_C_GRAPH_H

/**
 * @brief Definition of a @ref AdjacencyMatrix.
 * WeightedGraph is alias.
 */
typedef struct _AdjacencyMatrix {
    /** edges pointer point to _data */
    int **edges;
    int num_vertexes;
    /** private data store */
    int *_data;
} AdjacencyMatrix, WeightedGraph;

/**
 * @brief Allcate a new AdjacencyMatrix.
 *
 * @param num_vertexes          The initiate number of vertexes.
 * @return AdjacencyMatrix*     The new AdjacencyMatrix if success, otherwise
 * NULL.
 */
AdjacencyMatrix *adjacency_matrix_new(int num_vertexes);

/**
 * @brief Delete an AdjacencyMatrix and free back memory.
 *
 * @param graph     The AdjacencyMatrix to delete.
 */
void adjacency_matrix_free(AdjacencyMatrix *graph);

/**
 * @brief Reset all edges of an AdjacencyMatrix to a weight.
 *
 * @param graph     The AdjacencyMatrix.
 * @param weight    The weight.
 */
void adjacency_matrix_reset(AdjacencyMatrix *graph, int weight);

/**
 * @brief Set an edge from a vertex to another vertex of an AdjacencyMatrix
 *        to a weight.
 *
 * @param graph     The AdjacencyMatrix.
 * @param vertex1   From vertex.
 * @param vertex2   To vertex.
 * @param edge      The weight.
 */
void adjacency_matrix_set(AdjacencyMatrix *graph,
                          int vertex1,
                          int vertex2,
                          int edge);

/**
 * @brief Get weight of an edge from a vertex to another vertex of an
 * AdjacencyMatrix.
 *
 * @param graph     The AdjacencyMatrix.
 * @param vertex1   From vertex.
 * @param vertex2   To vertex.
 * @return int      The weight.
 */
int adjacency_matrix_get(const AdjacencyMatrix *graph,
                         int vertex1,
                         int vertex2);

#endif /* #ifndef RETHINK_C_GRAPH_H */
