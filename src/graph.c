/**
 * @file graph.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to graph.h
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "graph.h"
#include <stdlib.h>

AdjacencyMatrix *adjacency_matrix_new(int num_vertexes)
{
    AdjacencyMatrix *graph = (AdjacencyMatrix *)malloc(sizeof(AdjacencyMatrix));
    graph->num_vertexes = num_vertexes;
    graph->edges = (int **)malloc(sizeof(int *) * num_vertexes);
    graph->_data = (int *)malloc(sizeof(int) * num_vertexes * num_vertexes);
    for (int i = 0; i < num_vertexes; ++i) {
        graph->edges[i] = &(graph->_data[num_vertexes * i]);
    }
    return graph;
}

void adjacency_matrix_free(AdjacencyMatrix *graph)
{
    free(graph->_data);
    free(graph->edges);
    free(graph);
}

void adjacency_matrix_reset(AdjacencyMatrix *graph, int weight)
{
    for (int i = 0; i < graph->num_vertexes; ++i) {
        for (int j = 0; j < graph->num_vertexes; ++j) {
            graph->edges[i][j] = weight;
        }
    }
}

void adjacency_matrix_set(AdjacencyMatrix *graph,
                          int vertex1,
                          int vertex2,
                          int edge)
{
    graph->edges[vertex1][vertex2] = edge;
}

int adjacency_matrix_get(const AdjacencyMatrix *graph, int vertex1, int vertex2)
{
    return graph->edges[vertex1][vertex2];
}