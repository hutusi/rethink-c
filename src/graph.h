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

typedef enum _GraphType {
    UndirectedUnweighted = 0,
    UndirectedWeighted = 1,
    DirectedUnweighted = 2,
    DirectedWeighted = 3
} GraphType;

/**
 * @brief Definition of a @ref AdjacencyMatrix.
 * WeightedGraph is alias.
 */
typedef struct _AdjacencyMatrix {
    GraphType type;
    int num_vertexes;
    /** edges pointer point to _data */
    int **edges;
} AdjacencyMatrix, Graph;

/**
 * @brief Allcate a new AdjacencyMatrix.
 *
 * @param num_vertexes          The initiate number of vertexes.
 * @return AdjacencyMatrix*     The new AdjacencyMatrix if success, otherwise
 * NULL.
 */
AdjacencyMatrix *adjacency_matrix_new(GraphType type, int num_vertexes);

/**
 * @brief Delete an AdjacencyMatrix and free back memory.
 *
 * @param graph     The AdjacencyMatrix to delete.
 */
void adjacency_matrix_free(AdjacencyMatrix *graph);

/**
 * @brief Reset all edges of an AdjacencyMatrix to a weight.
 *
 * @param graph     The AdjacencyMatrix Graph.
 * @param weight    The weight.
 */
void adjacency_matrix_reset(AdjacencyMatrix *graph, int weight);

/**
 * @brief Set an edge from a vertex to another vertex of an AdjacencyMatrix
 *        to a weight.
 *
 * @param graph     The AdjacencyMatrix Graph.
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
 * @param graph     The AdjacencyMatrix Graph.
 * @param vertex1   From vertex.
 * @param vertex2   To vertex.
 * @return int      The weight.
 */
int adjacency_matrix_get(const AdjacencyMatrix *graph,
                         int vertex1,
                         int vertex2);

/**
 * @brief Linke two vertex in a graph.
 * 
 * @param graph     Vertex 1.
 * @param vertex1   Vertex 2.
 * @param vertex2   The AdjacencyMatrix Graph.
 * @return int 
 */
int adjacency_matrix_link(AdjacencyMatrix *graph, int vertex1, int vertex2);

/**
 * @brief Breadth first searching in a graph.
 * 
 * @param graph     The AdjacencyMatrix Graph.
 * @param start     The start vertex.
 * @param end       The end vertex.
 * @return int      0 if reach the end vertex, -1 if not.
 */
int adjacency_matrix_bfs(const AdjacencyMatrix *graph, int start, int end);

/**
 * @brief Depth first searching in a graph.
 * 
 * @param graph     The AdjacencyMatrix Graph.
 * @param start     The start vertex.
 * @param end       The end vertex.
 * @return int      0 if reach the end vertex, -1 if not.
 */
int adjacency_matrix_dfs(const AdjacencyMatrix *graph, int start, int end);

#endif /* #ifndef RETHINK_C_GRAPH_H */
