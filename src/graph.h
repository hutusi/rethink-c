/**
 * @file graph.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Adjacency Matrix.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_GRAPH_H
#define RETHINK_C_GRAPH_H

typedef struct _AdjacencyMatrix {
    int **edges;
    int num_vertexes;
    /** private data store */
    int *_data;
} AdjacencyMatrix, WeightedGraph;

AdjacencyMatrix *adjacency_matrix_new(int num_vertexes);
void adjacency_matrix_free(AdjacencyMatrix *graph);
void adjacency_matrix_reset(AdjacencyMatrix *graph, int weight);
void adjacency_matrix_set(AdjacencyMatrix *graph,
                          int vertex1,
                          int vertex2,
                          int edge);
int adjacency_matrix_get(const AdjacencyMatrix *graph,
                         int vertex1,
                         int vertex2);

#endif /* #ifndef RETHINK_C_GRAPH_H */
